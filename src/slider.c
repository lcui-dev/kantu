#include "slider.tsx.h"
#include "slider.h"

typedef struct {
        slider_react_t base;
        // Add additional states to your component here
        // ...
} slider_t;

static void slider_init(ui_widget_t *w)
{
        ui_widget_add_data(w, slider_proto, sizeof(slider_t));
        slider_react_init(w);
        // Write the initialization code for your component here
        // such as state initialization, event binding, etc
        // ...
}

static void slider_destroy(ui_widget_t *w)
{
        // Write code here to destroy the relevant resources of the component
        // ...

        slider_react_destroy(w);
}

void slider_update(ui_widget_t *w)
{
        slider_react_update(w);
        // Write code here to update other content of your component
        // ...
}

ui_widget_t *ui_create_slider(void)
{
        return ui_create_widget_with_prototype(slider_proto);
}

void ui_register_slider(void)
{
        slider_init_prototype();
        slider_proto->init = slider_init;
        slider_proto->destroy = slider_destroy;
}
