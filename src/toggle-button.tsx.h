/** This file is generated from toggle-button.tsx */
#include <ui.h>
#include "toggle-button.scss.h"



typedef struct toggle_button_react_state {
        char empty;
} toggle_button_react_state_t;

typedef struct toggle_button_react {
        toggle_button_react_state_t state;
} toggle_button_react_t;

static ui_widget_prototype_t *toggle_button_proto;

static void toggle_button_init_prototype(void)
{
        toggle_button_proto = ui_create_widget_prototype("toggle_button", NULL);
}

static void toggle_button_load_template(ui_widget_t *parent)
{
        ui_widget_add_class(parent, "toggle-button");
}

static void toggle_button_react_update(ui_widget_t *w)
{
        toggle_button_react_t *_that = ui_widget_get_data(w, toggle_button_proto);
}

static void toggle_button_react_init(ui_widget_t *w)
{
        toggle_button_react_t *_that = ui_widget_get_data(w, toggle_button_proto);
        toggle_button_load_template(w);
}

static void toggle_button_react_destroy(ui_widget_t *w)
{
}

void ui_load_toggle_button_resources(void)
{
        ui_load_css_string(css_str_toggle_button, "toggle-button.scss");
}
