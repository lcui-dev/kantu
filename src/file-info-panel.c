#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <LCUI/app.h>
#include <ui_widgets.h>
#include <time.h>
#include "file-info-panel.tsx.h"
#include "file-info-panel.h"
#include "utils.h"

#define TEXT_MAX_LEN 1024

typedef struct {
        file_info_panel_react_t base;
        file_info_t file_info;
        ui_image_t *image;
        worker_task_t *task;
} file_info_panel_t;

static void file_info_panel_close(ui_widget_t *w, ui_event_t *e, void *data)
{
        ui_widget_add_class(e->data, "hidden");
}

static void file_info_panel_init(ui_widget_t *w)
{
        file_info_panel_t *panel = ui_widget_add_data(
            w, file_info_panel_proto, sizeof(file_info_panel_t));
        panel->file_info.bits = 32;
        panel->file_info.file_size[0] = 0;
        panel->file_info.image_size[0] = 0;
        panel->file_info.name[0] = 0;
        panel->file_info.mtime = 0;
        panel->task = NULL;
        panel->image = NULL;
        file_info_panel_react_init(w);
        file_info_panel_update(w);
}

static file_info_panel_t *file_info_panel_get(ui_widget_t *w)
{
        return ui_widget_get_data(w, file_info_panel_proto);
}

ui_widget_t *ui_create_file_info_panel(void)
{
        return ui_create_widget_with_prototype(file_info_panel_proto);
}

static void file_info_panel_destroy(ui_widget_t *w)
{
        file_info_panel_t *panel = file_info_panel_get(w);

        if (panel->image) {
                ui_image_destroy(panel->image);
        }
        if (panel->task) {
                lcui_cancel_async_task(panel->task);
        }
        file_info_panel_react_destroy(w);
}

void file_info_panel_update(ui_widget_t *w)
{
        size_t len;
        char *uri, *dir;
        char text[TEXT_MAX_LEN];
        wchar_t wtext[TEXT_MAX_LEN];
        file_info_panel_t *panel = file_info_panel_get(w);

        file_info_panel_react_update(w);
        mbstowcs(wtext, panel->file_info.name, TEXT_MAX_LEN);
        ui_text_set_content_w(panel->base.refs.name, wtext);
        if (ui_image_valid(panel->image)) {
                len = mbstowcs(wtext, panel->image->path, TEXT_MAX_LEN);
                if (len >= TEXT_MAX_LEN) {
                        wtext[TEXT_MAX_LEN - 1] = 0;
                }
                uri = malloc((strlen(panel->image->path) + 8) * sizeof(char));
                dir = path_dirname(panel->image->path);
                sprintf(uri, "file:///%s", dir);
                ui_widget_set_attr(panel->base.refs.path, "href", uri);
                ui_text_set_content_w(panel->base.refs.path, wtext);
                free(uri);
                free(dir);

                sprintf(text, u8"%s   %s   %u 位", panel->file_info.image_size,
                        panel->file_info.file_size, panel->file_info.bits);
                ui_text_set_content(panel->base.refs.size, text);
        } else {
                ui_text_set_content(panel->base.refs.size, u8"未知");
        }

        wcscpy(wtext, L"未知");
        if (panel->file_info.mtime) {
                wcsftime(wtext, TEXT_MAX_LEN, L"%Y 年 %m 月 %d 日 %H:%M:%S",
                         localtime(&panel->file_info.mtime));
        }
        ui_text_set_content_w(panel->base.refs.datetime, wtext);
}

static void file_info_panel_on_load_file(void *data)
{
        struct stat st;
        ui_event_t e = { 0 };
        file_info_panel_t *panel = file_info_panel_get(data);

        panel->file_info.mtime = 0;
        strcpy(panel->file_info.file_size, u8"未知");
        if (stat(panel->image->path, &st) == 0) {
                panel->file_info.mtime = st.st_mtime;
                format_size(panel->file_info.file_size, st.st_size);
        }
        lcui_post_task(data, (worker_task_cb)file_info_panel_update, NULL);
        ui_event_init(&e, "load");
        ui_widget_emit_event(data, e, NULL);
}

static void file_info_panel_on_load_image(ui_image_event_t *image_event)
{
        ui_event_t e = { 0 };
        file_info_panel_t *panel = file_info_panel_get(image_event->data);

        if (ui_image_valid(image_event->image)) {
                snprintf(panel->file_info.image_size,
                         sizeof(panel->file_info.image_size), "%u x %u",
                         image_event->image->data.width,
                         image_event->image->data.height);
                panel->file_info.bits =
                    image_event->image->data.bytes_per_pixel * 8;
        } else {
                strcpy(panel->file_info.image_size, u8"未知");
                panel->file_info.bits = 0;
        }
        lcui_post_task(image_event->data,
                       (worker_task_cb)file_info_panel_update, NULL);
        ui_event_init(&e, "load");
        ui_widget_emit_event(image_event->data, e, NULL);
}

file_info_t *file_info_panel_load_file(ui_widget_t *w, const char *path)
{
        const char *ext;
        file_info_panel_t *panel = file_info_panel_get(w);

        if (panel->task) {
                lcui_cancel_async_task(panel->task);
        }
        if (panel->image) {
                ui_image_destroy(panel->image);
        }
        strcpy(panel->file_info.name, path_basename(path));
        ext = str_last_char(panel->file_info.name, '.');
        if (ext) {
                panel->file_info.name[ext - panel->file_info.name] = 0;
        }
        panel->image = ui_image_create(path);
        panel->task =
            lcui_post_async_task(w, file_info_panel_on_load_file, NULL);
        ui_image_on_load(panel->image, file_info_panel_on_load_image, w);
        return &panel->file_info;
}

void ui_register_file_info_panel(void)
{
        file_info_panel_init_prototype();
        file_info_panel_proto->init = file_info_panel_init;
        file_info_panel_proto->destroy = file_info_panel_destroy;
}
