#include "image-controller.h"

#define SCALE_MAX 10.f
#define SCALE_STEP 0.2f

void image_controller_init(image_controller_t *c)
{
        c->scale = 1.f;
        c->min_scale = 1.f;
        c->image = NULL;
        c->image_offset_x = 0;
        c->image_offset_y = 0;
        c->viewport_center_x = 0;
        c->viewport_center_y = 0;
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
        c->viewport_center_x =
            (-c->image_offset_x + c->viewport_width / 2.f) / c->scale;
        c->viewport_center_y =
            (-c->image_offset_y + c->viewport_height / 2.f) / c->scale;
}

float image_controller_compute_zoom_to_fit(image_controller_t *c)
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

void image_controller_set_scale(image_controller_t *c, float scale)
{
        if (scale < c->min_scale) {
                scale = c->min_scale;
        }
        if (scale > SCALE_MAX) {
                scale = SCALE_MAX;
        }
        c->scale = scale;
        image_controller_set_position(
            c, -(c->viewport_center_x * c->scale - c->viewport_width / 2.f),
            -(c->viewport_center_y * c->scale - c->viewport_height / 2.f));
}

void image_controller_zoom_in(image_controller_t *c)
{
        image_controller_set_scale(c, c->scale + SCALE_STEP);
}

void image_controller_zoom_out(image_controller_t *c)
{
        image_controller_set_scale(c, c->scale - SCALE_STEP);
}

void image_controller_zoom_to_fit(image_controller_t *c)
{
        c->min_scale = image_controller_compute_zoom_to_fit(c);
        c->scale = c->min_scale;
        image_controller_set_position(c, 0, 0);
}

bool image_controller_can_zoom_in(image_controller_t *c)
{
        return ui_image_valid(c->image) && c->scale < SCALE_MAX;
}

bool image_controller_can_zoom_out(image_controller_t *c)
{
        return ui_image_valid(c->image) && c->scale > c->min_scale;
}

bool image_controller_can_zoom_to_fit(image_controller_t *c)
{
        return ui_image_valid(c->image) &&
               image_controller_compute_zoom_to_fit(c) != c->scale;
}

void image_controller_load_file(image_controller_t *c, const char *file)
{
        if (c->image) {
                ui_image_destroy(c->image);
        }
        c->image = ui_image_create(file);
}
