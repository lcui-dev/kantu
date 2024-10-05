#include "toggle-button.tsx.h"
#include "toggle-button.h"

typedef struct {
        toggle_button_react_t base;
        // Add additional states to your component here
        // ...
} toggle_button_t;

static void toggle_button_init(ui_widget_t *w)
{
        ui_widget_add_data(w, toggle_button_proto, sizeof(toggle_button_t));
        toggle_button_react_init(w);
        // Write the initialization code for your component here
        // such as state initialization, event binding, etc
        // ...
}

static void toggle_button_destroy(ui_widget_t *w)
{
        // Write code here to destroy the relevant resources of the component
        // ...

        toggle_button_react_destroy(w);
}

void toggle_button_update(ui_widget_t *w)
{
        toggle_button_react_update(w);
        // Write code here to update other content of your component
        // ...
}

void toggle_button_set_checked(ui_widget_t *w, bool checked)
{
        if (checked) {
                ui_widget_add_class(w, "checked");
        } else {
                ui_widget_remove_class(w, "checked");
        }
}

ui_widget_t *ui_create_toggle_button(void)
{
        return ui_create_widget_with_prototype(toggle_button_proto);
}

void ui_register_toggle_button(void)
{
        toggle_button_init_prototype();
        toggle_button_proto->init = toggle_button_init;
        toggle_button_proto->destroy = toggle_button_destroy;
}
