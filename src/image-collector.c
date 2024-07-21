#include <stdbool.h>
#include "image-collector.h"
#include "utils.h"

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

void image_collector_thread(void *arg)
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
                                if (c->callback) {
                                        c->callback(c, c->callback_arg);
                                }
                                break;
                        }
                        file = dir_get_file_name_a(entry);
                        if (strcmp(file, current_file) == 0) {
                                c->index = files.length;
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

void image_collector_init(image_collector_t *c)
{
        c->file = NULL;
        c->callback = NULL;
        c->callback_arg = NULL;
        c->dirname = NULL;
        c->state = IMAGE_COLLECTOR_STATE_READY;
        list_create(&c->files);
        thread_cond_init(&c->cond);
        thread_mutex_init(&c->mutex);
        if (thread_create(&c->tid, image_collector_thread, c) != 0) {
                c->state = IMAGE_COLLECTOR_STATE_EXITED;
        }
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
        c->file = NULL;
        c->dirname = NULL;
}

void image_collector_load_file(image_collector_t *c, const char *file)
{
        char *dirname = path_dirname(file);

        thread_mutex_lock(&c->mutex);
        if (c->file) {
                free(c->file);
        }
        c->file = strdup2(file);
        if (c->dirname && strcmp(c->dirname, dirname) == 0) {
                thread_mutex_unlock(&c->mutex);
                return;
        }
        if (c->dirname) {
                free(c->dirname);
        }
        c->dirname = dirname;
        c->state = IMAGE_COLLECTOR_STATE_PENDING;
        thread_cond_signal(&c->cond);
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

char *image_collector_get_file(image_collector_t *c)
{
        const char *name = list_get(&c->files, c->index);

        if (!name || !c->dirname) {
                return c->file ? strdup2(c->file) : NULL;
        }
        return path_join(c->dirname, name);
}

char *image_collector_next(image_collector_t *c)
{
        if (image_collector_has_next(c)) {
                c->index++;
        }
        return image_collector_get_file(c);
}

char *image_collector_prev(image_collector_t *c)
{
        if (image_collector_has_prev(c)) {
                c->index--;
        }
        return image_collector_get_file(c);
}
