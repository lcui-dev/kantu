#include <stdio.h>
#include <ui.h>
#include <LCUI/app.h>
#include "file-info-reader.h"
#include "utils.h"

struct file_info_reader {
        file_info_t file_info;
        ui_image_t *image;
        worker_task_t *task;
        void (*callback)(file_info_t *, void *);
        void *callback_arg;
};

file_info_reader_t *file_info_reader_create(void (*callback)(file_info_t *,
                                                             void *),
                                            void *callback_arg)
{
        file_info_reader_t *reader = malloc(sizeof(file_info_reader_t));

        reader->file_info.bits = 32;
        reader->file_info.file_size[0] = 0;
        reader->file_info.image_size[0] = 0;
        reader->file_info.name[0] = 0;
        reader->file_info.mtime = 0;
        reader->file_info.path = strdup2("");
        reader->task = NULL;
        reader->image = NULL;
        reader->callback = callback;
        reader->callback_arg = callback_arg;
        return reader;
}

void file_info_reader_destroy(file_info_reader_t *reader)
{
        if (reader->task) {
                lcui_cancel_async_task(reader->task);
        }
        if (reader->image) {
                ui_image_destroy(reader->image);
        }
        if (reader->file_info.path) {
                free(reader->file_info.path);
        }
        free(reader);
}

static void file_info_reader_on_load_file(void *data)
{
        struct stat st;
        file_info_reader_t *reader = data;

        reader->file_info.mtime = 0;
        strcpy(reader->file_info.file_size, u8"未知");
        if (stat(reader->image->path, &st) == 0) {
                reader->file_info.mtime = st.st_mtime;
                format_size(reader->file_info.file_size, st.st_size);
        }
        if (reader->callback) {
                reader->callback(&reader->file_info, reader->callback_arg);
        }
}

static void file_info_reader_on_load_image(ui_image_event_t *image_event)
{
        file_info_reader_t *reader = image_event->data;
        file_info_t *info = &reader->file_info;

        info->bits = 0;
        info->width = 0;
        info->height = 0;
        if (ui_image_valid(image_event->image)) {
                info->bits = image_event->image->data.bytes_per_pixel * 8;
                info->width = image_event->image->data.width;
                info->height = image_event->image->data.height;
        }
        snprintf(info->image_size, 31, "%u x %u", info->width, info->height);
        if (reader->callback) {
                reader->callback(&reader->file_info, reader->callback_arg);
        }
}

void file_info_reader_load_file(file_info_reader_t *reader, const char *path)
{
        const char *ext;

        if (reader->task) {
                lcui_cancel_async_task(reader->task);
        }
        if (reader->image) {
                ui_image_destroy(reader->image);
        }
        if (reader->file_info.path) {
                free(reader->file_info.path);
        }
        reader->file_info.path = strdup2(path);
        strcpy(reader->file_info.name, path_basename(path));
        ext = str_last_char(reader->file_info.name, '.');
        if (ext) {
                *((char *)ext) = 0;
        }
        reader->image = ui_image_create(path);
        reader->task =
            lcui_post_async_task(reader, file_info_reader_on_load_file, NULL);
        ui_image_on_load(reader->image, file_info_reader_on_load_image, reader);
}

file_info_t *file_info_reader_get_info(file_info_reader_t *reader)
{
        return &reader->file_info;
}
