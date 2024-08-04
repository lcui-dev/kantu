#include <ui.h>

void ui_register_image_view(void);

ui_widget_t *ui_create_image_view(void);

void image_view_update(ui_widget_t *w);

void ui_load_image_view_resources(void);

void image_view_load_file(ui_widget_t *w, const char *file);

void image_view_reset(ui_widget_t *w);

