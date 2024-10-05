#include <ui.h>

void ui_register_toggle_button(void);

ui_widget_t *ui_create_toggle_button(void);

void toggle_button_update(ui_widget_t *w);

void toggle_button_set_checked(ui_widget_t *w, bool checked);

void ui_load_toggle_button_resources(void);
