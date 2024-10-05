/** This file is generated from file-info-panel.tsx */
#include <ui.h>
#include "file-info-panel.scss.h"

// UTF-8 encoded string from: %E4%BF%A1%E6%81%AF
static const unsigned char widget_text_0[] = {0xe4, 0xbf, 0xa1, 0xe6, 0x81, 0xaf, 0};
// UTF-8 encoded string from: %EF%8D%A9
static const unsigned char widget_text_1[] = {0xef, 0x8d, 0xa9, 0};
// UTF-8 encoded string from: %EF%92%87
static const unsigned char widget_text_2[] = {0xef, 0x92, 0x87, 0};
// UTF-8 encoded string from: %EE%89%8C
static const unsigned char widget_text_3[] = {0xee, 0x89, 0x8c, 0};
// UTF-8 encoded string from: %EE%A8%94
static const unsigned char widget_text_4[] = {0xee, 0xa8, 0x94, 0};
// UTF-8 encoded string from: %E5%A4%A7%E5%B0%8F%E4%BF%A1%E6%81%AF
static const unsigned char widget_text_5[] = {0xe5, 0xa4, 0xa7, 0xe5, 0xb0, 0x8f, 0xe4, 0xbf, 0xa1, 0xe6, 0x81, 0xaf, 0};
// UTF-8 encoded string from: %EF%90%AD
static const unsigned char widget_text_6[] = {0xef, 0x90, 0xad, 0};
// UTF-8 encoded string from: %E6%96%87%E4%BB%B6%E8%B7%AF%E5%BE%84
static const unsigned char widget_text_7[] = {0xe6, 0x96, 0x87, 0xe4, 0xbb, 0xb6, 0xe8, 0xb7, 0xaf, 0xe5, 0xbe, 0x84, 0};

typedef struct {
        ui_widget_t *ref_0;
        ui_widget_t *ref_2;
        ui_widget_t *name;
        ui_widget_t *ref_4;
        ui_widget_t *datetime;
        ui_widget_t *ref_6;
        ui_widget_t *size;
        ui_widget_t *ref_8;
        ui_widget_t *path;
} file_info_panel_refs_t;

typedef struct file_info_panel_react_state {
        char empty;
} file_info_panel_react_state_t;

typedef struct file_info_panel_react {
        file_info_panel_react_state_t state;
        file_info_panel_refs_t refs;
} file_info_panel_react_t;

static ui_widget_prototype_t *file_info_panel_proto;

static void file_info_panel_init_prototype(void)
{
        file_info_panel_proto = ui_create_widget_prototype("file_info_panel", NULL);
}

static void file_info_panel_load_template(ui_widget_t *parent, file_info_panel_refs_t *refs)
{
        ui_widget_t *w[17];

        ui_widget_add_class(parent, "file-info-panel hidden border-t border-l border-l-black p-4 rounded-l");
        w[0] = ui_create_widget("text");
        ui_widget_add_class(w[0], "mb-6 text-xl font-bold");
        ui_widget_set_text(w[0], (const char*)widget_text_0);
        refs->ref_0 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_0, "fui-icon-regular absolute top-4 right-4 opacity-70 hover:opacity-100");
        ui_widget_set_text(refs->ref_0, (const char*)widget_text_1);
        w[1] = ui_create_widget(NULL);
        ui_widget_add_class(w[1], "flex mb-4");
        w[2] = ui_create_widget(NULL);
        ui_widget_add_class(w[2], "flex-none field-icon");
        refs->ref_2 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_2, "fui-icon-regular");
        ui_widget_set_text(refs->ref_2, (const char*)widget_text_2);
        ui_widget_append(w[2], refs->ref_2);
        w[3] = ui_create_widget(NULL);
        ui_widget_add_class(w[3], "flex-auto pl-4");
        refs->name = ui_create_widget("text");
        ui_widget_add_class(refs->name, "field-label");
        ui_widget_append(w[3], refs->name);
        ui_widget_append(w[1], w[2]);
        ui_widget_append(w[1], w[3]);
        w[4] = ui_create_widget(NULL);
        ui_widget_add_class(w[4], "flex mb-4");
        w[5] = ui_create_widget(NULL);
        ui_widget_add_class(w[5], "flex-none field-icon");
        refs->ref_4 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_4, "fui-icon-regular");
        ui_widget_set_text(refs->ref_4, (const char*)widget_text_3);
        ui_widget_append(w[5], refs->ref_4);
        w[6] = ui_create_widget(NULL);
        ui_widget_add_class(w[6], "flex-auto pl-4");
        refs->datetime = ui_create_widget("text");
        ui_widget_add_class(refs->datetime, "field-value");
        ui_widget_append(w[6], refs->datetime);
        ui_widget_append(w[4], w[5]);
        ui_widget_append(w[4], w[6]);
        w[7] = ui_create_widget(NULL);
        ui_widget_add_class(w[7], "flex mb-4");
        w[8] = ui_create_widget(NULL);
        ui_widget_add_class(w[8], "flex-none field-icon");
        refs->ref_6 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_6, "fui-icon-regular");
        ui_widget_set_text(refs->ref_6, (const char*)widget_text_4);
        ui_widget_append(w[8], refs->ref_6);
        w[9] = ui_create_widget(NULL);
        ui_widget_add_class(w[9], "flex-auto pl-4");
        w[10] = ui_create_widget(NULL);
        w[11] = ui_create_widget("text");
        ui_widget_add_class(w[11], "field-label mb-1");
        ui_widget_set_text(w[11], (const char*)widget_text_5);
        refs->size = ui_create_widget("text");
        ui_widget_add_class(refs->size, "field-value");
        ui_widget_append(w[10], w[11]);
        ui_widget_append(w[10], refs->size);
        ui_widget_append(w[9], w[10]);
        ui_widget_append(w[7], w[8]);
        ui_widget_append(w[7], w[9]);
        w[12] = ui_create_widget(NULL);
        ui_widget_add_class(w[12], "flex mb-4");
        w[13] = ui_create_widget(NULL);
        ui_widget_add_class(w[13], "flex-none field-icon");
        refs->ref_8 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_8, "fui-icon-regular");
        ui_widget_set_text(refs->ref_8, (const char*)widget_text_6);
        ui_widget_append(w[13], refs->ref_8);
        w[14] = ui_create_widget(NULL);
        ui_widget_add_class(w[14], "flex-auto pl-4");
        w[15] = ui_create_widget(NULL);
        w[16] = ui_create_widget("text");
        ui_widget_add_class(w[16], "field-label mb-1");
        ui_widget_set_text(w[16], (const char*)widget_text_7);
        refs->path = ui_create_widget("a");
        ui_widget_add_class(refs->path, "field-value text-sky-500 hover:text-sky-700");
        ui_widget_append(w[15], w[16]);
        ui_widget_append(w[15], refs->path);
        ui_widget_append(w[14], w[15]);
        ui_widget_append(w[12], w[13]);
        ui_widget_append(w[12], w[14]);
        ui_widget_append(parent, w[0]);
        ui_widget_append(parent, refs->ref_0);
        ui_widget_append(parent, w[1]);
        ui_widget_append(parent, w[4]);
        ui_widget_append(parent, w[7]);
        ui_widget_append(parent, w[12]);
}

static void file_info_panel_react_update(ui_widget_t *w)
{
        file_info_panel_react_t *_that = ui_widget_get_data(w, file_info_panel_proto);
        ui_widget_set_style_string(_that->refs.ref_0, "font-size", "20px");
}

static void file_info_panel_close(ui_widget_t *w, ui_event_t *e, void *arg);

static void file_info_panel_react_init_events(ui_widget_t *w)
{
        file_info_panel_react_t *_that = ui_widget_get_data(w, file_info_panel_proto);
        ui_widget_on(_that->refs.ref_0, "click", file_info_panel_close, w);
}

static void file_info_panel_react_init(ui_widget_t *w)
{
        file_info_panel_react_t *_that = ui_widget_get_data(w, file_info_panel_proto);
        file_info_panel_load_template(w, &_that->refs);
        file_info_panel_react_init_events(w);
}

static void file_info_panel_react_destroy(ui_widget_t *w)
{
}

void ui_load_file_info_panel_resources(void)
{
        ui_load_css_string(css_str_file_info_panel, "file-info-panel.scss");
}
