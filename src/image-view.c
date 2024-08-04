#include "image-view.tsx.h"
#include "image-view.h"

typedef struct {
        image_view_react_t base;
        // Add additional states to your component here
        // ...
} image_view_t;

static void image_view_init(ui_widget_t *w)
{
        ui_widget_add_data(w, image_view_proto, sizeof(image_view_t));
        image_view_react_init(w);
        // Write the initialization code for your component here
        // such as state initialization, event binding, etc
        // ...
}

static void image_view_destroy(ui_widget_t *w)
{
        // Write code here to destroy the relevant resources of the component
        // ...

        image_view_react_destroy(w);
}

void image_view_update(ui_widget_t *w)
{
        image_view_react_update(w);
        // Write code here to update other content of your component
        // ...
}

ui_widget_t *ui_create_image_view(void)
{
        return ui_create_widget_with_prototype(image_view_proto);
}

void ui_register_image_view(void)
{
        image_view_init_prototype();
        image_view_proto->init = image_view_init;
        image_view_proto->destroy = image_view_destroy;
}
