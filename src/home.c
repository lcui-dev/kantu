#include "home.tsx.h"
#include "home.h"

typedef struct {
        home_react_t base;
        // Add additional states to your component here
        // ...
} home_t;

static void home_init(ui_widget_t *w)
{
        ui_widget_add_data(w, home_proto, sizeof(home_t));
        home_react_init(w);
        // Write the initialization code for your component here
        // such as state initialization, event binding, etc
        // ...
}

static void home_destroy(ui_widget_t *w)
{
        // Write code here to destroy the relevant resources of the component
        // ...

        home_react_destroy(w);
}

void home_update(ui_widget_t *w)
{
        home_react_update(w);
        // Write code here to update other content of your component
        // ...
}

ui_widget_t *ui_create_home(void)
{
        return ui_create_widget_with_prototype(home_proto);
}

void ui_register_home(void)
{
        home_init_prototype();
        home_proto->init = home_init;
        home_proto->destroy = home_destroy;
}
