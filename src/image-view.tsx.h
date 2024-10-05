/** This file is generated from image-view.tsx */
#include <ui.h>
#include "../vendor.node_modules/@lcui/react-icons/dist/style.css.h"
#include "image-view.scss.h"
#include "global.css.h"

// UTF-8 encoded string from: %EF%92%87
static const unsigned char widget_text_0[] = {0xef, 0x92, 0x87, 0};
// UTF-8 encoded string from: %E4%BC%BC%E4%B9%8E%E4%B8%8D%E6%94%AF%E6%8C%81%E6%AD%A4%E6%96%87%E4%BB%B6%E6%A0%BC%E5%BC%8F%E3%80%82
static const unsigned char widget_text_1[] = {0xe4, 0xbc, 0xbc, 0xe4, 0xb9, 0x8e, 0xe4, 0xb8, 0x8d, 0xe6, 0x94, 0xaf, 0xe6, 0x8c, 0x81, 0xe6, 0xad, 0xa4, 0xe6, 0x96, 0x87, 0xe4, 0xbb, 0xb6, 0xe6, 0xa0, 0xbc, 0xe5, 0xbc, 0x8f, 0xe3, 0x80, 0x82, 0};
// UTF-8 encoded string from: %EE%B6%AE
static const unsigned char widget_text_2[] = {0xee, 0xb6, 0xae, 0};
// UTF-8 encoded string from: %EE%B6%B3
static const unsigned char widget_text_3[] = {0xee, 0xb6, 0xb3, 0};
// UTF-8 encoded string from: %EE%AF%BB
static const unsigned char widget_text_4[] = {0xee, 0xaf, 0xbb, 0};
// UTF-8 encoded string from: %EE%AF%B5
static const unsigned char widget_text_5[] = {0xee, 0xaf, 0xb5, 0};
// UTF-8 encoded string from: %EE%9C%B6
static const unsigned char widget_text_6[] = {0xee, 0x9c, 0xb6, 0};
// UTF-8 encoded string from: %EE%A8%94
static const unsigned char widget_text_7[] = {0xee, 0xa8, 0x94, 0};
// UTF-8 encoded string from: %EE%A9%83
static const unsigned char widget_text_8[] = {0xee, 0xa9, 0x83, 0};
// UTF-8 encoded string from: 100%25
static const unsigned char widget_text_9[] = {0x31, 0x30, 0x30, 0x25, 0};
// UTF-8 encoded string from: %EF%96%8E
static const unsigned char widget_text_10[] = {0xef, 0x96, 0x8e, 0};
// UTF-8 encoded string from: %EF%96%98
static const unsigned char widget_text_11[] = {0xef, 0x96, 0x98, 0};
// UTF-8 encoded string from: %EE%BA%8F
static const unsigned char widget_text_12[] = {0xee, 0xba, 0x8f, 0};
// UTF-8 encoded string from: %EE%BA%8E
static const unsigned char widget_text_13[] = {0xee, 0xba, 0x8e, 0};
// UTF-8 encoded string from: %EF%85%9E
static const unsigned char widget_text_14[] = {0xef, 0x85, 0x9e, 0};

typedef struct {
        ui_widget_t *progressbar;
        ui_widget_t *content;
        ui_widget_t *tip;
        ui_widget_t *ref_3;
        ui_widget_t *filename;
        ui_widget_t *prev;
        ui_widget_t *ref_6;
        ui_widget_t *next;
        ui_widget_t *ref_8;
        ui_widget_t *ref_9;
        ui_widget_t *ref_10;
        ui_widget_t *ref_11;
        ui_widget_t *ref_13;
        ui_widget_t *image_size;
        ui_widget_t *ref_15;
        ui_widget_t *file_size;
        ui_widget_t *percentage;
        ui_widget_t *fit;
        ui_widget_t *ref_19;
        ui_widget_t *ref_20;
        ui_widget_t *zoom_out;
        ui_widget_t *slider;
        ui_widget_t *zoom_in;
        ui_widget_t *maximize;
        ui_widget_t *file_info_panel;
} image_view_refs_t;

typedef struct image_view_react_state {
        char empty;
} image_view_react_state_t;

typedef struct image_view_react {
        image_view_react_state_t state;
        image_view_refs_t refs;
} image_view_react_t;

static ui_widget_prototype_t *image_view_proto;

static void image_view_init_prototype(void)
{
        image_view_proto = ui_create_widget_prototype("image_view", NULL);
}

static void image_view_load_template(ui_widget_t *parent, image_view_refs_t *refs)
{
        ui_widget_t *w[8];

        ui_widget_add_class(parent, "image-view flex bg-[#1f1f1f] w-full h-full");
        w[0] = ui_create_widget(NULL);
        ui_widget_add_class(w[0], "flex h-full flex-auto flex-col");
        w[1] = ui_create_widget(NULL);
        ui_widget_add_class(w[1], "progress");
        refs->progressbar = ui_create_widget(NULL);
        ui_widget_add_class(refs->progressbar, "bar");
        ui_widget_append(w[1], refs->progressbar);
        refs->content = ui_create_widget(NULL);
        ui_widget_add_class(refs->content, "flex-auto flex items-center justify-center");
        refs->tip = ui_create_widget(NULL);
        ui_widget_add_class(refs->tip, "tip");
        refs->ref_3 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_3, "fui-icon-regular icon");
        ui_widget_set_text(refs->ref_3, (const char*)widget_text_0);
        refs->filename = ui_create_widget("text");
        w[2] = ui_create_widget("text");
        ui_widget_set_text(w[2], (const char*)widget_text_1);
        ui_widget_append(refs->tip, refs->ref_3);
        ui_widget_append(refs->tip, refs->filename);
        ui_widget_append(refs->tip, w[2]);
        ui_widget_append(refs->content, refs->tip);
        refs->prev = ui_create_widget(NULL);
        ui_widget_add_class(refs->prev, "switch-button prev");
        refs->ref_6 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_6, "fui-icon-filled");
        ui_widget_set_text(refs->ref_6, (const char*)widget_text_2);
        ui_widget_append(refs->prev, refs->ref_6);
        refs->next = ui_create_widget(NULL);
        ui_widget_add_class(refs->next, "switch-button next");
        refs->ref_8 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_8, "fui-icon-filled");
        ui_widget_set_text(refs->ref_8, (const char*)widget_text_3);
        ui_widget_append(refs->next, refs->ref_8);
        w[3] = ui_create_widget(NULL);
        ui_widget_add_class(w[3], "toolbar");
        w[4] = ui_create_widget("toggle_button");
        ui_widget_add_class(w[4], "button");
        refs->ref_9 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_9, "fui-icon-regular icon");
        ui_widget_set_text(refs->ref_9, (const char*)widget_text_4);
        refs->ref_10 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_10, "fui-icon-filled icon");
        ui_widget_set_text(refs->ref_10, (const char*)widget_text_5);
        ui_widget_append(w[4], refs->ref_9);
        ui_widget_append(w[4], refs->ref_10);
        w[5] = ui_create_widget(NULL);
        ui_widget_add_class(w[5], "divider");
        refs->ref_11 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_11, "fui-icon-regular icon button mr-1");
        ui_widget_set_text(refs->ref_11, (const char*)widget_text_6);
        w[6] = ui_create_widget(NULL);
        ui_widget_add_class(w[6], "file-info mr-auto opacity-50 flex border-l border-l-white h-4 items-center pl-3");
        refs->ref_13 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_13, "fui-icon-regular mr-2 text-lg");
        ui_widget_set_text(refs->ref_13, (const char*)widget_text_7);
        refs->image_size = ui_create_widget("text");
        ui_widget_add_class(refs->image_size, "mr-4");
        refs->ref_15 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_15, "fui-icon-regular m-2");
        ui_widget_set_text(refs->ref_15, (const char*)widget_text_8);
        refs->file_size = ui_create_widget("text");
        ui_widget_append(w[6], refs->ref_13);
        ui_widget_append(w[6], refs->image_size);
        ui_widget_append(w[6], refs->ref_15);
        ui_widget_append(w[6], refs->file_size);
        refs->percentage = ui_create_widget("text");
        ui_widget_add_class(refs->percentage, "percentage");
        ui_widget_set_text(refs->percentage, (const char*)widget_text_9);
        refs->fit = ui_create_widget(NULL);
        ui_widget_add_class(refs->fit, "button fit-button");
        refs->ref_19 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_19, "fui-icon-regular icon icon-fit");
        ui_widget_set_text(refs->ref_19, (const char*)widget_text_10);
        refs->ref_20 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_20, "fui-icon-filled icon icon-fit-fill");
        ui_widget_set_text(refs->ref_20, (const char*)widget_text_11);
        ui_widget_append(refs->fit, refs->ref_19);
        ui_widget_append(refs->fit, refs->ref_20);
        refs->zoom_out = ui_create_widget("text");
        ui_widget_add_class(refs->zoom_out, "fui-icon-regular icon button");
        ui_widget_set_text(refs->zoom_out, (const char*)widget_text_12);
        refs->slider = ui_create_widget("Slider");
        refs->zoom_in = ui_create_widget("text");
        ui_widget_add_class(refs->zoom_in, "fui-icon-regular icon button");
        ui_widget_set_text(refs->zoom_in, (const char*)widget_text_13);
        w[7] = ui_create_widget(NULL);
        ui_widget_add_class(w[7], "divider");
        refs->maximize = ui_create_widget("text");
        ui_widget_add_class(refs->maximize, "fui-icon-regular icon button");
        ui_widget_set_text(refs->maximize, (const char*)widget_text_14);
        ui_widget_append(w[3], w[4]);
        ui_widget_append(w[3], w[5]);
        ui_widget_append(w[3], refs->ref_11);
        ui_widget_append(w[3], w[6]);
        ui_widget_append(w[3], refs->percentage);
        ui_widget_append(w[3], refs->fit);
        ui_widget_append(w[3], refs->zoom_out);
        ui_widget_append(w[3], refs->slider);
        ui_widget_append(w[3], refs->zoom_in);
        ui_widget_append(w[3], w[7]);
        ui_widget_append(w[3], refs->maximize);
        ui_widget_append(w[0], w[1]);
        ui_widget_append(w[0], refs->content);
        ui_widget_append(w[0], refs->prev);
        ui_widget_append(w[0], refs->next);
        ui_widget_append(w[0], w[3]);
        refs->file_info_panel = ui_create_widget("file_info_panel");
        ui_widget_add_class(refs->file_info_panel, "flex-none w-[360px] h-full");
        ui_widget_append(parent, w[0]);
        ui_widget_append(parent, refs->file_info_panel);
}

static void image_view_react_update(ui_widget_t *w)
{
        image_view_react_t *_that = ui_widget_get_data(w, image_view_proto);
        ui_widget_set_style_string(_that->refs.ref_3, "font-size", "80px");
        ui_widget_set_style_string(_that->refs.ref_13, "font-size", "14px");
        ui_widget_set_style_string(_that->refs.ref_15, "font-size", "14px");
}

static void image_view_open_file_info_panel(ui_widget_t *w, ui_event_t *e, void *arg);

static void image_view_react_init_events(ui_widget_t *w)
{
        image_view_react_t *_that = ui_widget_get_data(w, image_view_proto);
        ui_widget_on(_that->refs.ref_11, "click", image_view_open_file_info_panel, w);
}

static void image_view_react_init(ui_widget_t *w)
{
        image_view_react_t *_that = ui_widget_get_data(w, image_view_proto);
        image_view_load_template(w, &_that->refs);
        image_view_react_init_events(w);
}

static void image_view_react_destroy(ui_widget_t *w)
{
}

void ui_load_image_view_resources(void)
{
        ui_load_css_string(css_str_style, "style.css");
        ui_load_css_string(css_str_image_view, "image-view.scss");
        ui_load_css_string(css_str_global, "global.css");
}
