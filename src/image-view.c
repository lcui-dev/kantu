#include <stdio.h>
#include "image-view.tsx.h"
#include "image-view.h"
#include "image-controller.h"

typedef struct {
        image_view_react_t base;
        image_controller_t controller;
} image_view_t;

static void image_view_init(ui_widget_t *w)
{
        image_view_t *view;
        view = ui_widget_add_data(w, image_view_proto, sizeof(image_view_t));
        image_view_react_init(w);
        image_controller_init(&view->controller);
}

static void image_view_destroy(ui_widget_t *w)
{
        image_view_t *view = ui_widget_get_data(w, image_view_proto);
        image_view_react_destroy(w);
        image_controller_destroy(&view->controller);
}

void image_view_update(ui_widget_t *w)
{
        char size_str[64];
        image_view_t *view = ui_widget_get_data(w, image_view_proto);
        image_controller_t *c = &view->controller;

        snprintf(size_str, 31, "%gpx %gpx", c->scale * c->image->data.width,
                 c->scale * c->image->data.height);
        ui_widget_set_style_string(view->base.refs.content, "background-size",
                                   size_str);
        ui_widget_set_style_unit_value(view->base.refs.content,
                                       css_prop_background_position_x,
                                       c->image_offset_x, CSS_UNIT_PX);
        ui_widget_set_style_unit_value(view->base.refs.content,
                                       css_prop_background_position_y,
                                       c->image_offset_y, CSS_UNIT_PX);
        image_view_react_update(w);
}

ui_widget_t *ui_create_image_view(void)
{
        return ui_create_widget_with_prototype(image_view_proto);
}

void ui_register_image_view(void)
{
        image_view_init_prototype();
        image_view_proto->init = image_view_init;
        image_view_proto->destroy = image_view_destroy;
}

void image_view_reset(ui_widget_t *w)
{
        image_view_t *view = ui_widget_get_data(w, image_view_proto);
        image_controller_t *c = &view->controller;

        c->viewport_width = view->base.refs.content->padding_box.width;
        c->viewport_height = view->base.refs.content->padding_box.height;
        image_controller_reset_scale(c);
        image_view_update(w);
}

void image_view_on_image_event(ui_image_event_t *e)
{
        image_view_reset(e->data);
}

void image_view_load_file(ui_widget_t *w, const char *file)
{
        char *url;
        image_view_t *view = ui_widget_get_data(w, image_view_proto);
        image_controller_t *c = &view->controller;

        if (c->image) {
                ui_image_off_load(c->image, image_view_on_image_event, w);
        }
        image_controller_load_file(c, file);
        ui_image_on_load(c->image, image_view_on_image_event, w);

        url = malloc(sizeof(char) * (strlen(file) + 10));
        sprintf(url, "url(%s)", file);
        ui_widget_set_style_string(view->base.refs.content, "background-image",
                                   url);
        free(url);
}
