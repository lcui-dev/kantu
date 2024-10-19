#include <stdio.h>
#include <string.h>
#include <ui_widgets.h>
#include "file-info-panel.tsx.h"
#include "file-info-panel.h"
#include "utils.h"

#define TEXT_MAX_LEN 1024

typedef struct {
        file_info_panel_react_t base;
} file_info_panel_t;

static void file_info_panel_close(ui_widget_t *w, ui_event_t *e, void *data)
{
        ui_widget_add_class(e->data, "hidden");
}

static void file_info_panel_init(ui_widget_t *w)
{
        file_info_panel_t *panel = ui_widget_add_data(
            w, file_info_panel_proto, sizeof(file_info_panel_t));
        file_info_panel_react_init(w);
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

        file_info_panel_react_destroy(w);
}

void file_info_panel_set_info(ui_widget_t *w, file_info_t *info)
{
        size_t len;
        char *uri, *dir;
        char text[TEXT_MAX_LEN];
        wchar_t wtext[TEXT_MAX_LEN];
        file_info_panel_t *panel = file_info_panel_get(w);

        // Name
        file_info_panel_react_update(w);
        mbstowcs(wtext, info->name, TEXT_MAX_LEN);
        ui_text_set_content_w(panel->base.refs.name, wtext);

        // Size
        sprintf(text, u8"%u x %u   %s   %u 位", info->width, info->height,
                info->file_size, info->bits);
        ui_text_set_content(panel->base.refs.size, text);

        // Path
        len = mbstowcs(wtext, info->path, TEXT_MAX_LEN);
        if (len >= TEXT_MAX_LEN) {
                wtext[TEXT_MAX_LEN - 1] = 0;
        }
        uri = malloc((strlen(info->path) + 16) * sizeof(char));
        dir = path_dirname(info->path);
        sprintf(uri, "file:///%s", dir);
        ui_widget_set_attr(panel->base.refs.path, "href", uri);
        ui_text_set_content_w(panel->base.refs.path, wtext);
        free(uri);
        free(dir);

        // Datetime
        wcscpy(wtext, L"未知");
        if (info->mtime) {
                wcsftime(wtext, TEXT_MAX_LEN, L"%Y 年 %m 月 %d 日 %H:%M:%S",
                         localtime(&info->mtime));
        }
        ui_text_set_content_w(panel->base.refs.datetime, wtext);
}

void ui_register_file_info_panel(void)
{
        file_info_panel_init_prototype();
        file_info_panel_proto->init = file_info_panel_init;
        file_info_panel_proto->destroy = file_info_panel_destroy;
}
