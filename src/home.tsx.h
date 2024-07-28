/** This file is generated from home.tsx */
#include <ui.h>
#include "home.scss.h"

// UTF-8 encoded string from: kantu
static const unsigned char widget_text_0[] = {0x6b, 0x61, 0x6e, 0x74, 0x75, 0};
// UTF-8 encoded string from: %E7%89%88%E6%9C%AC%EF%BC%9A0.1.0
static const unsigned char widget_text_1[] = {0xe7, 0x89, 0x88, 0xe6, 0x9c, 0xac, 0xef, 0xbc, 0x9a, 0x30, 0x2e, 0x31, 0x2e, 0x30, 0};
// UTF-8 encoded string from: An%20image%20viewer
static const unsigned char widget_text_2[] = {0x41, 0x6e, 0x20, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x20, 0x76, 0x69, 0x65, 0x77, 0x65, 0x72, 0};
// UTF-8 encoded string from: %E7%94%A8%E6%B3%95%EF%BC%9A%E5%8F%B3%E9%94%AE%E5%8D%95%E5%87%BB%E5%9B%BE%E7%89%87%E6%96%87%E4%BB%B6%20-%3E%20%E6%89%93%E5%BC%80%E6%96%B9%E5%BC%8F%20-%3E%20%E9%80%89%E6%8B%A9%E5%85%B6%E4%BB%96%E5%BA%94%E7%94%A8%20-%3E%20%E9%80%89%E6%8B%A9%20kantu
static const unsigned char widget_text_3[] = {0xe7, 0x94, 0xa8, 0xe6, 0xb3, 0x95, 0xef, 0xbc, 0x9a, 0xe5, 0x8f, 0xb3, 0xe9, 0x94, 0xae, 0xe5, 0x8d, 0x95, 0xe5, 0x87, 0xbb, 0xe5, 0x9b, 0xbe, 0xe7, 0x89, 0x87, 0xe6, 0x96, 0x87, 0xe4, 0xbb, 0xb6, 0x20, 0x2d, 0x3e, 0x20, 0xe6, 0x89, 0x93, 0xe5, 0xbc, 0x80, 0xe6, 0x96, 0xb9, 0xe5, 0xbc, 0x8f, 0x20, 0x2d, 0x3e, 0x20, 0xe9, 0x80, 0x89, 0xe6, 0x8b, 0xa9, 0xe5, 0x85, 0xb6, 0xe4, 0xbb, 0x96, 0xe5, 0xba, 0x94, 0xe7, 0x94, 0xa8, 0x20, 0x2d, 0x3e, 0x20, 0xe9, 0x80, 0x89, 0xe6, 0x8b, 0xa9, 0x20, 0x6b, 0x61, 0x6e, 0x74, 0x75, 0};

typedef struct home_react_state {
        char empty;
} home_react_state_t;

typedef struct home_react {
        home_react_state_t state;
} home_react_t;

static ui_widget_prototype_t *home_proto;

static void home_init_prototype(void)
{
        home_proto = ui_create_widget_prototype("home", NULL);
}

static void home_load_template(ui_widget_t *parent)
{
        ui_widget_t *w[7];

        ui_widget_add_class(parent, "home");
        w[0] = ui_create_widget(NULL);
        ui_widget_add_class(w[0], "container");
        w[1] = ui_create_widget(NULL);
        ui_widget_add_class(w[1], "header");
        w[2] = ui_create_widget(NULL);
        ui_widget_add_class(w[2], "logo");
        w[3] = ui_create_widget("text");
        ui_widget_add_class(w[3], "name");
        ui_widget_set_text(w[3], (const char*)widget_text_0);
        w[4] = ui_create_widget("text");
        ui_widget_add_class(w[4], "version");
        ui_widget_set_text(w[4], (const char*)widget_text_1);
        w[5] = ui_create_widget("text");
        ui_widget_add_class(w[5], "description");
        ui_widget_set_text(w[5], (const char*)widget_text_2);
        ui_widget_append(w[1], w[2]);
        ui_widget_append(w[1], w[3]);
        ui_widget_append(w[1], w[4]);
        ui_widget_append(w[1], w[5]);
        w[6] = ui_create_widget("text");
        ui_widget_add_class(w[6], "usage");
        ui_widget_set_text(w[6], (const char*)widget_text_3);
        ui_widget_append(w[0], w[1]);
        ui_widget_append(w[0], w[6]);
        ui_widget_append(parent, w[0]);
}

static void home_react_update(ui_widget_t *w)
{
        home_react_t *_that = ui_widget_get_data(w, home_proto);
}

static void home_react_init(ui_widget_t *w)
{
        home_react_t *_that = ui_widget_get_data(w, home_proto);
        home_load_template(w);
}

static void home_react_destroy(ui_widget_t *w)
{
}

void ui_load_home_resources(void)
{
        ui_load_css_string(css_str_home, "home.scss");
}
