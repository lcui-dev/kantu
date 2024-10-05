/** This file is generated from slider.tsx */
#include <ui.h>
#include "slider.scss.h"



typedef struct {
        ui_widget_t *bar;
        ui_widget_t *thumb;
} slider_refs_t;

typedef struct slider_react_state {
        char empty;
} slider_react_state_t;

typedef struct slider_react {
        slider_react_state_t state;
        slider_refs_t refs;
} slider_react_t;

static ui_widget_prototype_t *slider_proto;

static void slider_init_prototype(void)
{
        slider_proto = ui_create_widget_prototype("slider", NULL);
}

static void slider_load_template(ui_widget_t *parent, slider_refs_t *refs)
{
        ui_widget_t *w[1];

        ui_widget_add_class(parent, "slider");
        w[0] = ui_create_widget(NULL);
        ui_widget_add_class(w[0], "slider-track");
        refs->bar = ui_create_widget(NULL);
        ui_widget_add_class(refs->bar, "bg-blue-500");
        ui_widget_append(w[0], refs->bar);
        refs->thumb = ui_create_widget(NULL);
        ui_widget_add_class(refs->thumb, "slider-thumb");
        ui_widget_append(parent, w[0]);
        ui_widget_append(parent, refs->thumb);
}

static void slider_react_update(ui_widget_t *w)
{
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
}

static void slider_react_init(ui_widget_t *w)
{
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
        slider_load_template(w, &_that->refs);
}

static void slider_react_destroy(ui_widget_t *w)
{
}

void ui_load_slider_resources(void)
{
        ui_load_css_string(css_str_slider, "slider.scss");
}
