/** This file is generated from film-view.tsx */
#include <ui.h>
#include "film-view.scss.h"



typedef struct {
        ui_widget_t *content;
} film_view_refs_t;

typedef struct film_view_react_state {
        char empty;
} film_view_react_state_t;

typedef struct film_view_react {
        film_view_react_state_t state;
        film_view_refs_t refs;
} film_view_react_t;

static ui_widget_prototype_t *film_view_proto;

static void film_view_init_prototype(void)
{
        film_view_proto = ui_create_widget_prototype("film_view", NULL);
}

static void film_view_load_template(ui_widget_t *parent, film_view_refs_t *refs)
{
        ui_widget_t *w[1];

        ui_widget_add_class(parent, "film-view hidden");
        refs->content = ui_create_widget(NULL);
        ui_widget_set_attr(refs->content, "id", "filmViewContent");
        ui_widget_add_class(refs->content, "film-view-content");
        w[0] = ui_create_widget("scrollbar");
        ui_widget_set_attr(w[0], "direction", "horizontal");
        ui_widget_set_attr(w[0], "target", "filmViewContent");
        ui_widget_append(parent, refs->content);
        ui_widget_append(parent, w[0]);
}

static void film_view_react_update(ui_widget_t *w)
{
        film_view_react_t *_that = ui_widget_get_data(w, film_view_proto);
}

static void film_view_react_init(ui_widget_t *w)
{
        film_view_react_t *_that = ui_widget_get_data(w, film_view_proto);
        film_view_load_template(w, &_that->refs);
}

static void film_view_react_destroy(ui_widget_t *w)
{
}

void ui_load_film_view_resources(void)
{
        ui_load_css_string(css_str_film_view, "film-view.scss");
}
