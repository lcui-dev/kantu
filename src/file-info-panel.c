﻿#include <stdio.h>
#include <LCUI/widgets.h>
#include "file-info-panel.tsx.h"
#include "file-info-panel.h"
#include "utils.h"

#define TEXT_MAX_LEN 1024

typedef struct {
        file_info_panel_react_t base;
        // Add additional states to your component here
        // ...
} file_info_panel_t;

static void file_info_panel_init(ui_widget_t *w)
{
        ui_widget_add_data(w, file_info_panel_proto, sizeof(file_info_panel_t));
        file_info_panel_react_init(w);
        // Write the initialization code for your component here
        // such as state initialization, event binding, etc
        // ...

        file_info_panel_update(w);
}

static file_info_panel_t *file_info_panel_get(ui_widget_t *w)
{
        return ui_widget_get_data(w, file_info_panel_proto);
}

static void file_info_panel_destroy(ui_widget_t *w)
{
        // Write code here to destroy the relevant resources of the component
        // ...

        file_info_panel_react_destroy(w);
}

void file_info_panel_update(ui_widget_t *w)
{
        file_info_panel_react_update(w);
        // Write code here to update other content of your component
        // ...
}

static void file_info_panel_close(ui_widget_t *w, ui_event_t *e, void *data)
{
        ui_widget_add_class(e->data, "hidden");
}

void file_info_panel_set_info(ui_widget_t *w, file_info_t *info)
{
        file_info_panel_t *panel = file_info_panel_get(w);
        file_info_panel_refs_t *refs = &panel->base.refs;
        wchar_t wtext[TEXT_MAX_LEN];
        char text[TEXT_MAX_LEN];
        size_t len;
        char *uri, *dir;

        mbstowcs(wtext, info->name, TEXT_MAX_LEN);
        ui_text_set_content_w(refs->name, wtext);

        wcscpy(wtext, L"未知");
        if (info->mtime) {
                wcsftime(wtext, TEXT_MAX_LEN, L"%Y 年 %m 月 %d 日 %H:%M:%S",
                         localtime(&info->mtime));
        }
        ui_text_set_content_w(refs->datetime, wtext);
        
        sprintf(text, u8"%u x %u   %s   %u 位", info->width, info->height,
                info->file_size, info->bits);
        ui_text_set_content(refs->size, text);

        len = mbstowcs(wtext, info->path, TEXT_MAX_LEN);
        if (len >= TEXT_MAX_LEN) {
                wtext[TEXT_MAX_LEN - 1] = 0;
        }
        uri = malloc((strlen(info->path) + 16) * sizeof(char));
        dir = path_dirname(info->path);
        sprintf(uri, "file:///%s", dir);
        ui_widget_set_attr(refs->path, "href", uri);
        ui_text_set_content_w(refs->path, wtext);
        free(uri);
        free(dir);
}

ui_widget_t *ui_create_file_info_panel(void)
{
        return ui_create_widget_with_prototype(file_info_panel_proto);
}

void ui_register_file_info_panel(void)
{
        file_info_panel_init_prototype();
        file_info_panel_proto->init = file_info_panel_init;
        file_info_panel_proto->destroy = file_info_panel_destroy;
}
