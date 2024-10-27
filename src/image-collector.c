#include <stdbool.h>
#include "image-collector.h"
#include "utils.h"

typedef enum {
        IMAGE_COLLECTOR_STATE_EXITED,
        IMAGE_COLLECTOR_STATE_READY,
        IMAGE_COLLECTOR_STATE_PENDING,
        IMAGE_COLLECTOR_STATE_LOADING,
        IMAGE_COLLECTOR_STATE_FINISHED,
        IMAGE_COLLECTOR_STATE_ERROR,
} image_collector_state_t;

typedef struct {
        void (*callback)(image_collector_t*, image_collector_event_type_t, void *);
        void *data;
} listener_t;

struct image_collector {
        char *file;
        image_collector_state_t state;
        list_t files;
        size_t index;
        char *dirname;
        thread_t tid;
        thread_mutex_t mutex;
        thread_cond_t cond;

        /** list_t<listener_t*> */
        list_t listeners;
};

bool is_image_file(const char *path)
{
        char *ext;
        const char *ext_src = str_last_char(path, '.');

        if (ext_src == NULL) {
                return false;
        }
        ext = strdup2(ext_src);
        strtolower(ext, ext);
        if (strstr(".jpg.jpeg.bmp.png", ext) != NULL) {
                free(ext);
                return true;
        }
        free(ext);
        return false;
}

void image_collector_notify(image_collector_t *c,
                            image_collector_event_type_t type)
{
        list_node_t *node;

        for (list_each(node, &c->listeners)) {
                listener_t *listener = node->data;
                listener->callback(c, type, listener->data);
        }
}

void image_collector_listen(image_collector_t *c,
                            void (*callback)(image_collector_t *,
                                             image_collector_event_type_t,
                                             void *),
                            void *data)
{
        listener_t *listener = malloc(sizeof(listener_t));

        listener->callback = callback;
        listener->data = data;
        list_append(&c->listeners, listener);
}

static void image_collector_thread(void *arg)
{
        dir_t *dir;
        char *file;
        char *current_file = NULL;
        list_t files;
        dir_entry_t *entry;
        image_collector_t *c = arg;

        dir = dir_create();
        list_create(&files);
        while (c->state != IMAGE_COLLECTOR_STATE_EXITED) {
                thread_mutex_lock(&c->mutex);
                while (c->state != IMAGE_COLLECTOR_STATE_PENDING &&
                       c->state != IMAGE_COLLECTOR_STATE_EXITED) {
                        thread_cond_wait(&c->cond, &c->mutex);
                }
                if (c->state == IMAGE_COLLECTOR_STATE_EXITED) {
                        thread_mutex_unlock(&c->mutex);
                        break;
                }
                if (dir_open_a(c->dirname, dir) != 0) {
                        c->state = IMAGE_COLLECTOR_STATE_ERROR;
                        logger_error(
                            "[image-collector] cannot open directory: %ls",
                            c->dirname);
                        continue;
                }
                c->index = 0;
                c->state = IMAGE_COLLECTOR_STATE_LOADING;
                if (current_file) {
                        free(current_file);
                }
                current_file = strdup2(path_basename(c->file));
                thread_mutex_unlock(&c->mutex);
                while (c->state != IMAGE_COLLECTOR_STATE_PENDING &&
                       c->state != IMAGE_COLLECTOR_STATE_EXITED) {
                        entry = dir_read_a(dir);
                        if (entry == NULL) {
                                list_destroy(&c->files, free);
                                list_concat(&c->files, &files);
                                c->state = IMAGE_COLLECTOR_STATE_FINISHED;
                                image_collector_notify(
                                    c, IMAGE_COLLECTOR_EVENT_FINISHED);
                                break;
                        }
                        file = dir_get_file_name_a(entry);
                        if (strcmp(file, current_file) == 0) {
                                c->index = files.length;
                                image_collector_notify(
                                    c, IMAGE_COLLECTOR_EVENT_FOUND);
                        }
                        if (dir_entry_is_regular(entry) &&
                            is_image_file(file)) {
                                list_append(&files, strdup2(file));
                        }
                }
                list_destroy(&files, free);
        }
        if (current_file) {
                free(current_file);
        }
        dir_destroy(dir);
        thread_exit(NULL);
}

image_collector_t *image_collector_create(void)
{
        image_collector_t *c = malloc(sizeof(image_collector_t));
        c->file = NULL;
        c->dirname = NULL;
        c->state = IMAGE_COLLECTOR_STATE_READY;
        list_create(&c->files);
        list_create(&c->listeners);
        thread_cond_init(&c->cond);
        thread_mutex_init(&c->mutex);
        if (thread_create(&c->tid, image_collector_thread, c) != 0) {
                c->state = IMAGE_COLLECTOR_STATE_EXITED;
        }
        return c;
}

void image_collector_destroy(image_collector_t *c)
{
        thread_mutex_lock(&c->mutex);
        c->state = IMAGE_COLLECTOR_STATE_EXITED;
        thread_cond_signal(&c->cond);
        thread_mutex_unlock(&c->mutex);
        thread_join(c->tid, NULL);
        if (c->file) {
                free(c->file);
        }
        if (c->dirname) {
                free(c->dirname);
        }
        list_destroy(&c->files, free);
        list_destroy(&c->listeners, free);
        c->file = NULL;
        c->dirname = NULL;
        free(c);
}

void image_collector_load_file(image_collector_t *c, const char *file)
{
        size_t i = 0;
        list_node_t *node;
        char *dirname = path_dirname(file);

        thread_mutex_lock(&c->mutex);
        if (c->file) {
                free(c->file);
        }
        c->file = strdup2(file);
        image_collector_notify(c, IMAGE_COLLECTOR_EVENT_OPEN);
        if (!c->dirname || strcmp(c->dirname, dirname) != 0) {
                if (c->dirname) {
                        free(c->dirname);
                }
                c->dirname = dirname;
                c->state = IMAGE_COLLECTOR_STATE_PENDING;
                thread_cond_signal(&c->cond);
                thread_mutex_unlock(&c->mutex);
                return;
        }
        for (list_each(node, &c->files)) {
                if (strcmp(node->data, path_basename(file)) == 0) {
                        c->index = i;
                        image_collector_notify(c, IMAGE_COLLECTOR_EVENT_FOUND);
                        break;
                }
                i++;
        }
        thread_mutex_unlock(&c->mutex);
}

size_t image_collector_get_index(image_collector_t *c)
{
        return c->index;
}

void image_collector_get_files(image_collector_t *c, list_t *files,
                               size_t index)
{
        list_node_t *node;

        thread_mutex_lock(&c->mutex);
        for (node = list_get_node(&c->files, index); node; node = node->next) {
                list_append(files, path_join(c->dirname, node->data));
        }
        thread_mutex_unlock(&c->mutex);
}

bool image_collector_has_next(image_collector_t *c)
{
        return c->state == IMAGE_COLLECTOR_STATE_FINISHED &&
               c->index + 1 < c->files.length;
}

bool image_collector_has_prev(image_collector_t *c)
{
        return c->state == IMAGE_COLLECTOR_STATE_FINISHED && c->index > 0;
}

const char *image_collector_get_file(image_collector_t *c)
{
        return c->file;
}

static void image_collector_goto(image_collector_t *c, size_t index)
{
        char *file;
        char *name = list_get(&c->files, index);

        if (!name || !c->dirname) {
                return;
        }
        file = path_join(c->dirname, name);
        c->index = index;
        image_collector_load_file(c, file);
        free(file);
}

void image_collector_next(image_collector_t *c)
{
        if (image_collector_has_next(c)) {
                image_collector_goto(c, c->index + 1);
        }
}

void image_collector_prev(image_collector_t *c)
{
        if (image_collector_has_prev(c)) {
                image_collector_goto(c, c->index - 1);
        }
}
