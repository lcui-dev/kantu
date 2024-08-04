/** This file is generated from image-view.tsx */
#include <ui.h>
#include "../vendor.node_modules/@lcui/react-icons/dist/style.css.h"
#include "image-view.scss.h"

// UTF-8 encoded string from: %EF%92%87
static const unsigned char widget_text_0[] = {0xef, 0x92, 0x87, 0};
// UTF-8 encoded string from: %E4%BC%BC%E4%B9%8E%E4%B8%8D%E6%94%AF%E6%8C%81%E6%AD%A4%E6%96%87%E4%BB%B6%E6%A0%BC%E5%BC%8F%E3%80%82
static const unsigned char widget_text_1[] = {0xe4, 0xbc, 0xbc, 0xe4, 0xb9, 0x8e, 0xe4, 0xb8, 0x8d, 0xe6, 0x94, 0xaf, 0xe6, 0x8c, 0x81, 0xe6, 0xad, 0xa4, 0xe6, 0x96, 0x87, 0xe4, 0xbb, 0xb6, 0xe6, 0xa0, 0xbc, 0xe5, 0xbc, 0x8f, 0xe3, 0x80, 0x82, 0};
// UTF-8 encoded string from: %EE%B6%AE
static const unsigned char widget_text_2[] = {0xee, 0xb6, 0xae, 0};
// UTF-8 encoded string from: %EE%B6%B3
static const unsigned char widget_text_3[] = {0xee, 0xb6, 0xb3, 0};
// UTF-8 encoded string from: 100%25
static const unsigned char widget_text_4[] = {0x31, 0x30, 0x30, 0x25, 0};
// UTF-8 encoded string from: %EE%BA%8F
static const unsigned char widget_text_5[] = {0xee, 0xba, 0x8f, 0};
// UTF-8 encoded string from: %EE%BA%8E
static const unsigned char widget_text_6[] = {0xee, 0xba, 0x8e, 0};
// UTF-8 encoded string from: %EF%9A%8D
static const unsigned char widget_text_7[] = {0xef, 0x9a, 0x8d, 0};
// UTF-8 encoded string from: %EF%9C%8A
static const unsigned char widget_text_8[] = {0xef, 0x9c, 0x8a, 0};
// UTF-8 encoded string from: %EF%85%9E
static const unsigned char widget_text_9[] = {0xef, 0x85, 0x9e, 0};

typedef struct {
        ui_widget_t *ref_0;
        ui_widget_t *ref_1;
        ui_widget_t *ref_2;
        ui_widget_t *zoom_out;
        ui_widget_t *zoom_in;
        ui_widget_t *fill;
        ui_widget_t *original;
        ui_widget_t *maximize;
        ui_widget_t *progressbar;
        ui_widget_t *content;
        ui_widget_t *tip;
        ui_widget_t *filename;
        ui_widget_t *prev;
        ui_widget_t *next;
        ui_widget_t *percentage;
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
        ui_widget_t *w[4];

        ui_widget_add_class(parent, "image-view");
        w[0] = ui_create_widget(NULL);
        ui_widget_add_class(w[0], "progress");
        refs->progressbar = ui_create_widget(NULL);
        ui_widget_add_class(refs->progressbar, "bar");
        ui_widget_append(w[0], refs->progressbar);
        refs->content = ui_create_widget(NULL);
        ui_widget_add_class(refs->content, "content");
        refs->tip = ui_create_widget(NULL);
        ui_widget_add_class(refs->tip, "tip");
        refs->ref_0 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_0, "fui-icon-regular icon");
        ui_widget_set_text(refs->ref_0, (const char*)widget_text_0);
        refs->filename = ui_create_widget("text");
        w[1] = ui_create_widget("text");
        ui_widget_set_text(w[1], (const char*)widget_text_1);
        ui_widget_append(refs->tip, refs->ref_0);
        ui_widget_append(refs->tip, refs->filename);
        ui_widget_append(refs->tip, w[1]);
        ui_widget_append(refs->content, refs->tip);
        refs->prev = ui_create_widget(NULL);
        ui_widget_add_class(refs->prev, "switch-button prev");
        refs->ref_1 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_1, "fui-icon-filled");
        ui_widget_set_text(refs->ref_1, (const char*)widget_text_2);
        ui_widget_append(refs->prev, refs->ref_1);
        refs->next = ui_create_widget(NULL);
        ui_widget_add_class(refs->next, "switch-button next");
        refs->ref_2 = ui_create_widget("text");
        ui_widget_add_class(refs->ref_2, "fui-icon-filled");
        ui_widget_set_text(refs->ref_2, (const char*)widget_text_3);
        ui_widget_append(refs->next, refs->ref_2);
        w[2] = ui_create_widget(NULL);
        ui_widget_add_class(w[2], "toolbar");
        refs->percentage = ui_create_widget("text");
        ui_widget_add_class(refs->percentage, "percentage");
        ui_widget_set_text(refs->percentage, (const char*)widget_text_4);
        refs->zoom_out = ui_create_widget("text");
        ui_widget_add_class(refs->zoom_out, "fui-icon-regular icon button");
        ui_widget_set_text(refs->zoom_out, (const char*)widget_text_5);
        refs->zoom_in = ui_create_widget("text");
        ui_widget_add_class(refs->zoom_in, "fui-icon-regular icon button");
        ui_widget_set_text(refs->zoom_in, (const char*)widget_text_6);
        refs->fill = ui_create_widget("text");
        ui_widget_add_class(refs->fill, "fui-icon-regular icon button");
        ui_widget_set_text(refs->fill, (const char*)widget_text_7);
        refs->original = ui_create_widget("text");
        ui_widget_add_class(refs->original, "fui-icon-regular icon button");
        ui_widget_set_text(refs->original, (const char*)widget_text_8);
        w[3] = ui_create_widget(NULL);
        ui_widget_add_class(w[3], "divider");
        refs->maximize = ui_create_widget("text");
        ui_widget_add_class(refs->maximize, "fui-icon-regular icon button");
        ui_widget_set_text(refs->maximize, (const char*)widget_text_9);
        ui_widget_append(w[2], refs->percentage);
        ui_widget_append(w[2], refs->zoom_out);
        ui_widget_append(w[2], refs->zoom_in);
        ui_widget_append(w[2], refs->fill);
        ui_widget_append(w[2], refs->original);
        ui_widget_append(w[2], w[3]);
        ui_widget_append(w[2], refs->maximize);
        ui_widget_append(parent, w[0]);
        ui_widget_append(parent, refs->content);
        ui_widget_append(parent, refs->prev);
        ui_widget_append(parent, refs->next);
        ui_widget_append(parent, w[2]);
}

static void image_view_react_update(ui_widget_t *w)
{
        image_view_react_t *_that = ui_widget_get_data(w, image_view_proto);
        ui_widget_set_style_string(_that->refs.ref_0, "font-size", "80px");
        ui_widget_set_style_string(_that->refs.ref_1, "font-size", "12px");
        ui_widget_set_style_string(_that->refs.ref_2, "font-size", "12px");
        ui_widget_set_style_string(_that->refs.zoom_out, "font-size", "16px");
        ui_widget_set_style_string(_that->refs.zoom_in, "font-size", "16px");
        ui_widget_set_style_string(_that->refs.fill, "font-size", "20px");
        ui_widget_set_style_string(_that->refs.original, "font-size", "20px");
        ui_widget_set_style_string(_that->refs.maximize, "font-size", "16px");
}

static void image_view_react_init(ui_widget_t *w)
{
        image_view_react_t *_that = ui_widget_get_data(w, image_view_proto);
        image_view_load_template(w, &_that->refs);
}

static void image_view_react_destroy(ui_widget_t *w)
{
}

void ui_load_image_view_resources(void)
{
        ui_load_css_string(css_str_style, "style.css");
        ui_load_css_string(css_str_image_view, "image-view.scss");
}
