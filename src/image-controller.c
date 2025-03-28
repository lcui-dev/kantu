#include "image-controller.h"

void image_controller_init(image_controller_t *c)
{
        c->scale = 1.f;
        c->image = NULL;
        c->image_offset_x = 0;
        c->image_offset_y = 0;
        c->focus_x = 0;
        c->focus_y = 0;
        c->viewport_width = 0;
        c->viewport_height = 0;
}

void image_controller_destroy(image_controller_t *c)
{
        if (c->image) {
                ui_image_destroy(c->image);
        }
        c->image = NULL;
}

void image_controller_load_file(image_controller_t *c, const char *file)
{
        if (c->image) {
                ui_image_destroy(c->image);
        }
        c->image = ui_image_create(file);
}

float image_controller_get_fit_scale(image_controller_t *c)
{
        pd_canvas_t *data = &c->image->data;
        float width_scale = data->width > c->viewport_width
                                ? c->viewport_width / data->width
                                : 1.f;
        float height_scale = data->height > c->viewport_height
                                 ? c->viewport_height / data->height
                                 : 1.f;

        return width_scale < height_scale ? width_scale : height_scale;
}

float image_controller_get_min_scale(image_controller_t *c)
{
        float fit_scale = image_controller_get_fit_scale(c);
        return fit_scale < SCALE_MIN ? fit_scale : SCALE_MIN;
}

void image_controller_set_scale(image_controller_t *c, float scale)
{
        float min_scale = image_controller_get_min_scale(c);
        if (scale < min_scale) {
                scale = min_scale;
        }
        if (scale > SCALE_MAX) {
                scale = SCALE_MAX;
        }
        c->scale = scale;
        image_controller_set_position(
            c, -(c->focus_x * c->scale - c->viewport_width / 2.f),
            -(c->focus_y * c->scale - c->viewport_height / 2.f));
}

void image_controller_set_position(image_controller_t *c, float image_offset_x,
                                   float image_offset_y)
{
        pd_canvas_t *data = &c->image->data;
        float image_width = c->scale * data->width;
        float image_height = c->scale * data->height;

        if (image_width <= c->viewport_width) {
                image_offset_x = (c->viewport_width - image_width) / 2.f;
        } else if (image_offset_x > 0) {
                image_offset_x = 0;
        } else if (c->viewport_width - image_offset_x > image_width) {
                image_offset_x = c->viewport_width - image_width;
        }
        if (image_height <= c->viewport_height) {
                image_offset_y = (c->viewport_height - image_height) / 2.f;
        } else if (image_offset_y > 0) {
                image_offset_y = 0;
        } else if (c->viewport_height - image_offset_y > image_height) {
                image_offset_y = c->viewport_height - image_height;
        }
        c->image_offset_x = image_offset_x;
        c->image_offset_y = image_offset_y;
        c->focus_x = (-c->image_offset_x + c->viewport_width / 2.f) / c->scale;
        c->focus_y = (-c->image_offset_y + c->viewport_height / 2.f) / c->scale;
}

void image_controller_zoom_to_fit(image_controller_t *c)
{
        c->scale = image_controller_get_fit_scale(c);
        image_controller_set_position(c, 0, 0);
}

bool image_controller_can_zoom_in(image_controller_t *c)
{
        return ui_image_valid(c->image) && c->scale < SCALE_MAX;
}

bool image_controller_can_zoom_out(image_controller_t *c)
{
        return ui_image_valid(c->image) &&
               c->scale > image_controller_get_min_scale(c);
}

bool image_controller_can_zoom_to_fit(image_controller_t *c)
{
        return ui_image_valid(c->image) &&
               image_controller_get_fit_scale(c) != c->scale;
}

void image_controller_zoom_in(image_controller_t *c)
{
        if (image_controller_can_zoom_in(c)) {
                image_controller_set_scale(c, c->scale + SCALE_STEP);
        }
}

void image_controller_zoom_out(image_controller_t *c)
{
        if (image_controller_can_zoom_out(c)) {
                image_controller_set_scale(c, c->scale - SCALE_STEP);
        }
}
