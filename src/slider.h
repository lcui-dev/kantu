#include <ui.h>

void ui_register_slider(void);

ui_widget_t *ui_create_slider(void);

void slider_update(ui_widget_t *w);

void slider_set_min(ui_widget_t *w, double min);

void slider_set_max(ui_widget_t *w, double max);

void slider_set_value(ui_widget_t *w, double value);

double slider_get_value(ui_widget_t *w);

void ui_load_slider_resources(void);
