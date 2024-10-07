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
        void (*callback)(image_collector_event_type_t, void *);
        void *data;
} listener_t;

typedef struct {
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
} image_collector_t;

static image_collector_t image_collector;

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

void image_collector_notify(image_collector_event_type_t type)
{
        list_node_t *node;

        for (list_each(node, &image_collector.listeners)) {
                listener_t *listener = node->data;
                listener->callback(type, listener->data);
        }
}

void image_collector_listen(void (*callback)(image_collector_event_type_t,
                                             void *),
                            void *data)
{
        listener_t *listener = malloc(sizeof(listener_t));

        listener->callback = callback;
        listener->data = data;
        list_append(&image_collector.listeners, listener);
}

void image_collector_thread(void *unused)
{
        dir_t *dir;
        char *file;
        char *current_file = NULL;
        list_t files;
        dir_entry_t *entry;
        image_collector_t *c = &image_collector;

        dir = dir_create();
        list_create(&files);
        while (image_collector.state != IMAGE_COLLECTOR_STATE_EXITED) {
                thread_mutex_lock(&image_collector.mutex);
                while (image_collector.state != IMAGE_COLLECTOR_STATE_PENDING &&
                       image_collector.state != IMAGE_COLLECTOR_STATE_EXITED) {
                        thread_cond_wait(&image_collector.cond,
                                         &image_collector.mutex);
                }
                if (image_collector.state == IMAGE_COLLECTOR_STATE_EXITED) {
                        thread_mutex_unlock(&image_collector.mutex);
                        break;
                }
                if (dir_open_a(image_collector.dirname, dir) != 0) {
                        image_collector.state = IMAGE_COLLECTOR_STATE_ERROR;
                        logger_error(
                            "[image-collector] cannot open directory: %ls",
                            image_collector.dirname);
                        continue;
                }
                image_collector.index = 0;
                image_collector.state = IMAGE_COLLECTOR_STATE_LOADING;
                if (current_file) {
                        free(current_file);
                }
                current_file = strdup2(path_basename(image_collector.file));
                thread_mutex_unlock(&image_collector.mutex);
                while (image_collector.state != IMAGE_COLLECTOR_STATE_PENDING &&
                       image_collector.state != IMAGE_COLLECTOR_STATE_EXITED) {
                        entry = dir_read_a(dir);
                        if (entry == NULL) {
                                list_destroy(&image_collector.files, free);
                                list_concat(&image_collector.files, &files);
                                image_collector.state =
                                    IMAGE_COLLECTOR_STATE_FINISHED;
                                image_collector_notify(
                                    IMAGE_COLLECTOR_EVENT_FINISHED);
                                break;
                        }
                        file = dir_get_file_name_a(entry);
                        if (strcmp(file, current_file) == 0) {
                                image_collector.index = files.length;
                                image_collector_notify(
                                    IMAGE_COLLECTOR_EVENT_FOUND);
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

void image_collector_init(void)
{
        image_collector.file = NULL;
        image_collector.dirname = NULL;
        image_collector.state = IMAGE_COLLECTOR_STATE_READY;
        list_create(&image_collector.files);
        list_create(&image_collector.listeners);
        thread_cond_init(&image_collector.cond);
        thread_mutex_init(&image_collector.mutex);
        if (thread_create(&image_collector.tid, image_collector_thread, NULL) !=
            0) {
                image_collector.state = IMAGE_COLLECTOR_STATE_EXITED;
        }
}

void image_collector_destroy(void)
{
        thread_mutex_lock(&image_collector.mutex);
        image_collector.state = IMAGE_COLLECTOR_STATE_EXITED;
        thread_cond_signal(&image_collector.cond);
        thread_mutex_unlock(&image_collector.mutex);
        thread_join(image_collector.tid, NULL);
        if (image_collector.file) {
                free(image_collector.file);
        }
        if (image_collector.dirname) {
                free(image_collector.dirname);
        }
        list_destroy(&image_collector.files, free);
        list_destroy(&image_collector.listeners, free);
        image_collector.file = NULL;
        image_collector.dirname = NULL;
}

void image_collector_load_file(const char *file)
{
        size_t i = 0;
        list_node_t *node;
        char *dirname = path_dirname(file);

        thread_mutex_lock(&image_collector.mutex);
        if (image_collector.file) {
                free(image_collector.file);
        }
        image_collector.file = strdup2(file);
        image_collector_notify(IMAGE_COLLECTOR_EVENT_OPEN);
        if (!image_collector.dirname ||
            strcmp(image_collector.dirname, dirname) != 0) {
                if (image_collector.dirname) {
                        free(image_collector.dirname);
                }
                image_collector.dirname = dirname;
                image_collector.state = IMAGE_COLLECTOR_STATE_PENDING;
                thread_cond_signal(&image_collector.cond);
                thread_mutex_unlock(&image_collector.mutex);
                return;
        }
        for (list_each(node, &image_collector.files)) {
                if (strcmp(node->data, path_basename(file)) == 0) {
                        image_collector.index = i;
                        image_collector_notify(IMAGE_COLLECTOR_EVENT_FOUND);
                        break;
                }
                i++;
        }
        thread_mutex_unlock(&image_collector.mutex);
}

size_t image_collector_get_index(void)
{
        return image_collector.index;
}

void image_collector_get_files(list_t *files, size_t index)
{
        list_node_t *node;

        thread_mutex_lock(&image_collector.mutex);
        for (node = list_get_node(&image_collector.files, index); node;
             node = node->next) {
                list_append(files,
                            path_join(image_collector.dirname, node->data));
        }
        thread_mutex_unlock(&image_collector.mutex);
}

bool image_collector_has_next(void)
{
        return image_collector.state == IMAGE_COLLECTOR_STATE_FINISHED &&
               image_collector.index + 1 < image_collector.files.length;
}

bool image_collector_has_prev(void)
{
        return image_collector.state == IMAGE_COLLECTOR_STATE_FINISHED &&
               image_collector.index > 0;
}

const char *image_collector_get_file(void)
{
        return image_collector.file;
}

static void image_collector_goto(size_t index)
{
        char *file;
        char *name = list_get(&image_collector.files, index);

        if (!name || !image_collector.dirname) {
                return;
        }
        file = path_join(image_collector.dirname, name);
        image_collector.index = index;
        image_collector_load_file(file);
        free(file);
}

void image_collector_next(void)
{
        if (image_collector_has_next()) {
                image_collector_goto(image_collector.index + 1);
        }
}

void image_collector_prev(void)
{
        if (image_collector_has_prev()) {
                image_collector_goto(image_collector.index - 1);
        }
}
