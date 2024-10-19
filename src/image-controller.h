#include <ui.h>

typedef struct image_controller {
        float scale;
        float viewport_width, viewport_height;
        float viewport_center_x, viewport_center_y;
        float image_offset_x, image_offset_y;
        ui_image_t *image;
} image_controller_t;

void image_controller_init(image_controller_t *c);

void image_controller_destroy(image_controller_t *c);

void image_controller_set_position(image_controller_t *c, float image_offset_x,
                                   float image_offset_y);

float image_controller_compute_zoom_to_fit(image_controller_t *c);

void image_controller_set_scale(image_controller_t *c, float scale);

void image_controller_zoom_in(image_controller_t *c);

void image_controller_zoom_out(image_controller_t *c);

void image_controller_zoom_to_fit(image_controller_t *c);

bool image_controller_can_zoom_in(image_controller_t *c);

bool image_controller_can_zoom_out(image_controller_t *c);

bool image_controller_can_zoom_to_fit(image_controller_t *c);

void image_controller_load_file(image_controller_t *c, const char *file);
