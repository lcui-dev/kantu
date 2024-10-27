#include <ui.h>
#include "image-collector.h"

void ui_register_film_view(void);

ui_widget_t *ui_create_film_view(void);

void film_view_update(ui_widget_t *w);

void ui_load_film_view_resources(void);

void film_view_show(ui_widget_t *w);

void film_view_hide(ui_widget_t *w);

void film_view_set_image_collector(ui_widget_t *w, image_collector_t *c);
