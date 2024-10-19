#include "slider.tsx.h"
#include "slider.h"

typedef struct {
        slider_react_t base;
        double min;
        double max;
        double value;
        bool dragging;
} slider_t;

static slider_t *file_info_panel_get(ui_widget_t *w)
{
        return ui_widget_get_data(w, slider_proto);
}

static void slider_init(ui_widget_t *w)
{
        slider_t *slider =
            ui_widget_add_data(w, slider_proto, sizeof(slider_t));
        slider->min = 0;
        slider->max = 100;
        slider->value = 0;
        slider_react_init(w);
}

static void slider_destroy(ui_widget_t *w)
{
        slider_react_destroy(w);
}

void slider_update(ui_widget_t *w)
{
        slider_t *slider = file_info_panel_get(w);
        double value =
            (slider->value - slider->min) / (slider->max - slider->min);

        slider->base.state.percentage = value * 100.0;
        ui_widget_set_style_unit_value(
            slider->base.refs.thumb, css_prop_left,
            (css_numeric_value_t)(value * w->content_box.width), CSS_UNIT_PX);
        slider_react_update(w);
}

void slider_set_min(ui_widget_t *w, double min)
{
        slider_t *slider = file_info_panel_get(w);
        slider->min = min;
        slider_set_value(w, slider->value);
}

void slider_set_max(ui_widget_t *w, double max)
{
        slider_t *slider = file_info_panel_get(w);
        slider->max = max;
        slider_set_value(w, slider->value);
}

void slider_set_value(ui_widget_t *w, double value)
{
        slider_t *slider = file_info_panel_get(w);

        if (value < slider->min) {
                value = slider->min;
        }
        if (value > slider->max) {
                value = slider->max;
        }
        slider->value = value;
        slider_update(w);
}

double slider_get_value(ui_widget_t *w)
{
        slider_t *slider = file_info_panel_get(w);
        return slider->value;
}

void slider_on_mousemove(ui_widget_t *w, ui_event_t *e, void *arg)
{
        slider_t *slider = file_info_panel_get(w);
        ui_event_t change_event;
        float offset_x, offset_y;

        if (!slider->dragging) {
                return;
        }
        ui_widget_get_offset(w, NULL, &offset_x, &offset_y);
        slider_set_value(
            w, slider->min +
                   (e->mouse.x - (offset_x + w->computed_style.padding_left)) /
                       w->content_box.width * (slider->max - slider->min));
        ui_event_init(&change_event, "change");
        ui_widget_emit_event(w, change_event, NULL);
        
}

void slider_on_mousedown(ui_widget_t *w, ui_event_t *e, void *arg)
{
        slider_t *slider = file_info_panel_get(w);

        slider->dragging = true;
        ui_widget_set_mouse_capture(w);
        slider_on_mousemove(w, e, arg);
}

void slider_on_mouseup(ui_widget_t *w, ui_event_t *e, void *arg)
{
        slider_t *slider = file_info_panel_get(w);

        slider->dragging = false;
        ui_widget_release_mouse_capture(w);
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
