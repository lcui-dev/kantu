#include <stdio.h>
#include <ui_widgets.h>
#include <ui_server.h>
#include <LCUI/app.h>
#include "utils.h"
#include "image-view.tsx.h"
#include "image-view.h"
#include "image-controller.h"
#include "file-info-panel.h"
#include "film-view.h"
#include "slider.h"
#include "toggle-button.h"
#include "utils.h"

typedef struct {
        image_view_react_t base;
        image_controller_t controller;
        image_collector_t *collector;
        file_info_reader_t *reader;

        float mouse_x, mouse_y;
        float mouse_offset_x, mouse_offset_y;
        bool dragging;
} image_view_t;

static image_view_t *image_view_get(ui_widget_t *w)
{
        return ui_widget_get_data(w, image_view_proto);
}

static void image_view_on_zoom_in(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_controller_zoom_in(&view->controller);
        image_view_update(e->data);
}

static void image_view_on_zoom_out(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_controller_zoom_out(&view->controller);
        image_view_update(e->data);
}

static void image_view_on_zoom_to_1(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_controller_set_scale(&view->controller, 1.0f);
        image_view_update(e->data);
}

static void image_view_on_zoom_to_fit(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_controller_zoom_to_fit(&view->controller);
        image_view_update(e->data);
}

static void image_view_on_keydown(ui_widget_t *root, ui_event_t *e, void *arg)
{
        ui_widget_t *w = e->data;
        image_view_t *view = image_view_get(w);

        switch (e->key.code) {
        case KEY_EQUAL:
                image_controller_zoom_in(&view->controller);
                image_view_update(w);
                break;
        case KEY_MINUS:
                image_controller_zoom_out(&view->controller);
                image_view_update(w);
                break;
        case KEY_LEFT:
                image_collector_prev(view->collector);
                break;
        case KEY_RIGHT:
                image_collector_next(view->collector);
                break;
        case KEY_ESCAPE:
                if (ui_widget_has_class(w, "maximized")) {
                        image_view_restore(w);
                }
                break;
        default:
                break;
        }
}

static void image_view_on_mousedown(ui_widget_t *w, ui_event_t *e, void *arg)
{
        float offset_x, offset_y;
        image_view_t *view = image_view_get(e->data);

        ui_widget_get_offset(w, NULL, &offset_x, &offset_y);
        ui_widget_set_mouse_capture(w);
        view->mouse_offset_x =
            e->mouse.x - offset_x - view->controller.image_offset_x;
        view->mouse_offset_y =
            e->mouse.y - offset_y - view->controller.image_offset_y;
        view->dragging = true;
}

static void image_view_on_mousemove(ui_widget_t *w, ui_event_t *e, void *arg)
{
        float offset_x, offset_y;
        image_view_t *view = image_view_get(e->data);

        ui_widget_get_offset(w, NULL, &offset_x, &offset_y);
        view->mouse_x = e->mouse.x - offset_x;
        view->mouse_y = e->mouse.y - offset_y;
        if (view->dragging) {
                image_controller_set_position(
                    &view->controller,
                    e->mouse.x - offset_x - view->mouse_offset_x,
                    e->mouse.y - offset_y - view->mouse_offset_y);
                image_view_update(e->data);
        }
}

static void image_view_on_mouseup(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        view->dragging = false;
        ui_widget_release_mouse_capture(w);
}

static void image_view_on_mousewheel(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_controller_t *c = &view->controller;
        float scale = view->controller.scale;
        float center_x = (view->mouse_x - c->image_offset_x) / scale;
        float center_y = (view->mouse_y - c->image_offset_y) / scale;

        if (e->wheel.delta_y > 0) {
                image_controller_zoom_in(c);
        } else {
                image_controller_zoom_out(c);
        }
        image_controller_set_position(c, view->mouse_x - center_x * c->scale,
                                      view->mouse_y - center_y * c->scale);
        image_view_update(e->data);
}

static void image_view_on_prev_mousedown(ui_widget_t *w, ui_event_t *e,
                                         void *arg)
{
        e->cancel_bubble = true;
}

static void image_view_on_next_mousedown(ui_widget_t *w, ui_event_t *e,
                                         void *arg)
{
        e->cancel_bubble = true;
}

static void image_view_on_next(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_collector_next(view->collector);
}

static void image_view_on_prev(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_collector_prev(view->collector);
}

static void image_view_on_load_file_info(file_info_t *info, void *arg)
{
        image_view_update(arg);
}

void image_view_on_mutation(ui_mutation_list_t *list,
                            ui_mutation_observer_t *observer, void *arg)
{
        image_view_reset(arg);
}

void image_view_open_file_info_panel(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);

        ui_widget_remove_class(view->base.refs.file_info_panel, "hidden");
}

void image_view_maximize(ui_widget_t *w)
{
        ui_widget_add_class(w, "maximized");
        lcui_set_ui_display_mode(LCUI_DISPLAY_MODE_FULLSCREEN);
}

void image_view_restore(ui_widget_t *w)
{
        ui_widget_remove_class(w, "maximized");
        lcui_set_ui_display_mode(LCUI_DISPLAY_MODE_DEFAULT);
}

void image_view_on_maximize(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_maximize(e->data);
}

void image_view_update(ui_widget_t *w)
{
        size_t len;
        char size_str[64];
        char percentage_str[8] = "100%";
        wchar_t title[80];
        image_view_t *view = image_view_get(w);
        image_controller_t *c = &view->controller;
        file_info_t *info = file_info_reader_get_info(view->reader);

        if (ui_image_valid(c->image)) {
                len = mbstowcs(title, path_basename(c->image->path), 64);
                if (len > 60) {
                        title[60] = '.';
                        title[61] = '.';
                        title[62] = '.';
                        title[63] = 0;
                } else {
                        title[len] = 0;
                }
                ui_widget_set_title(ui_root(), title);

                snprintf(size_str, 31, "%gpx %gpx",
                         c->scale * c->image->data.width,
                         c->scale * c->image->data.height);
                ui_widget_set_style_string(view->base.refs.content,
                                           "background-size", size_str);
                snprintf(percentage_str, 7, "%d%%",
                         (int)(view->controller.scale * 100));
                slider_set_value(view->base.refs.slider, c->scale * 100.0);
        } else {
                slider_set_value(view->base.refs.slider, 100.0);
        }

        ui_text_set_content(view->base.refs.file_size, info->file_size);
        ui_text_set_content(view->base.refs.image_size, info->image_size);
        ui_widget_set_style_unit_value(view->base.refs.content,
                                       css_prop_background_position_x,
                                       c->image_offset_x, CSS_UNIT_PX);
        ui_widget_set_style_unit_value(view->base.refs.content,
                                       css_prop_background_position_y,
                                       c->image_offset_y, CSS_UNIT_PX);

        ui_text_set_content(view->base.refs.percentage, percentage_str);

        ui_widget_set_disabled(view->base.refs.zoom_in,
                               !image_controller_can_zoom_in(c));
        ui_widget_set_disabled(view->base.refs.zoom_out,
                               !image_controller_can_zoom_out(c));

        if (image_collector_has_prev(view->collector)) {
                ui_widget_show(view->base.refs.prev);
        } else {
                ui_widget_hide(view->base.refs.prev);
        }
        if (image_collector_has_next(view->collector)) {
                ui_widget_show(view->base.refs.next);
        } else {
                ui_widget_hide(view->base.refs.next);
        }

        if (!c->image || c->image->state != UI_IMAGE_STATE_COMPLETE ||
            c->image->error == PD_OK) {
                ui_widget_hide(view->base.refs.tip);
        } else {
                ui_widget_show(view->base.refs.tip);
        }

        if (image_controller_can_zoom_to_fit(c)) {
                ui_widget_remove_class(view->base.refs.fit, "active");
        } else {
                ui_widget_add_class(view->base.refs.fit, "active");
        }
        toggle_button_set_checked(
            view->base.refs.toggle_film_view,
            ui_widget_is_visible(view->base.refs.film_view));
        file_info_panel_set_info(view->base.refs.file_info_panel, info);
        image_view_react_update(w);
}

void image_view_reset(ui_widget_t *w)
{
        image_view_t *view = image_view_get(w);
        image_controller_t *c = &view->controller;

        c->viewport_width = view->base.refs.content->padding_box.width;
        c->viewport_height = view->base.refs.content->padding_box.height;
        image_controller_zoom_to_fit(c);
        image_view_update(w);
}

static void image_view_on_image_event(ui_image_event_t *e)
{
        image_view_t *view = image_view_get(e->data);

        switch (e->type) {
        case UI_IMAGE_EVENT_PROGRESS:
                ui_widget_set_style_unit_value(
                    view->base.refs.progressbar, css_prop_width,
                    e->image->progress, CSS_UNIT_PERCENT);
                return;
        case UI_IMAGE_EVENT_LOAD:
                image_view_reset(e->data);
                break;
        case UI_IMAGE_EVENT_ERROR:
                image_view_update(e->data);
                break;
        default:
                break;
        }
        ui_widget_hide(view->base.refs.progressbar);
}

static void image_view_on_image_start_load(ui_image_event_t *e)
{
        image_view_reset(e->data);
        ui_image_off_progress(e->image, image_view_on_image_start_load,
                              e->data);
}

static void image_view_on_film_view_toggle(ui_widget_t *w, ui_event_t *e,
                                           void *arg)
{
        image_view_t *view = image_view_get(e->data);

        if (ui_widget_is_visible(view->base.refs.film_view)) {
                film_view_hide(view->base.refs.film_view);
        } else {
                film_view_show(view->base.refs.film_view);
        }
        image_view_update(e->data);
}

static void image_view_on_fit(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);

        if (image_controller_can_zoom_to_fit(&view->controller)) {
                image_controller_zoom_to_fit(&view->controller);
        } else {
                image_controller_set_scale(&view->controller, 1.0f);
        }
        image_view_update(e->data);
}

static void image_view_on_load_file(ui_widget_t *w, const char *file)
{
        image_view_t *view = image_view_get(w);
        image_controller_t *c = &view->controller;

        if (c->image) {
                ui_image_off_load(c->image, image_view_on_image_event, w);
                ui_image_off_error(c->image, image_view_on_image_event, w);
                ui_image_off_progress(c->image, image_view_on_image_event, w);
                ui_image_off_progress(c->image, image_view_on_image_start_load,
                                      w);
        }
        image_controller_load_file(c, file);
        file_info_reader_load_file(view->reader, file);
        ui_text_set_content(view->base.refs.filename, path_basename(file));
        ui_image_on_load(c->image, image_view_on_image_event, w);
        ui_image_on_error(c->image, image_view_on_image_event, w);
        ui_image_on_progress(c->image, image_view_on_image_event, w);
        ui_image_on_progress(c->image, image_view_on_image_start_load, w);
        ui_widget_set_style_unit_value(view->base.refs.progressbar,
                                       css_prop_width, 0, CSS_UNIT_PERCENT);
        ui_widget_show(view->base.refs.progressbar);
        ui_widget_set_background_image_url(view->base.refs.content, file);
        logger_debug("[image-view] %s\n", "load file");
}

void image_view_on_collector_event(image_collector_t *c,
                                   image_collector_event_type_t type, void *arg)
{
        if (type == IMAGE_COLLECTOR_EVENT_OPEN) {
                image_view_on_load_file(arg, image_collector_get_file(c));
        }
        image_view_update(arg);
}

void image_view_load_file(ui_widget_t *w, const char *file)
{
        image_view_t *view = image_view_get(w);

        image_collector_load_file(view->collector, file);
}

void image_view_on_slider_change(ui_widget_t *w, ui_event_t *e, void *arg)
{
        image_view_t *view = image_view_get(e->data);
        image_controller_set_scale(&view->controller,
                                   (float)(slider_get_value(w) / 100.0));
        image_view_update(e->data);
}

static void image_view_init(ui_widget_t *w)
{
        image_view_t *view = UI_WDIGET_ADD_DATA(w, image_view);
        image_view_refs_t *refs = &view->base.refs;
        ui_mutation_observer_init_t options = { .properties = true };
        ui_mutation_observer_t *observer;

        view->reader = file_info_reader_create(image_view_on_load_file_info, w);
        view->collector = image_collector_create();
        image_view_react_init(w);
        image_controller_init(&view->controller);
        image_collector_listen(view->collector, image_view_on_collector_event,
                               w);
        observer = ui_mutation_observer_create(image_view_on_mutation, w);
        ui_mutation_observer_observe(observer, refs->content, options);
        ui_widget_on(ui_root(), "keydown", image_view_on_keydown, w);
        film_view_set_image_collector(refs->film_view, view->collector);
        slider_set_min(refs->slider, 10);
        slider_set_max(refs->slider, 800);
        image_view_update(w);
}

static void image_view_destroy(ui_widget_t *w)
{
        image_view_t *view = image_view_get(w);
        image_view_react_destroy(w);
        image_collector_destroy(view->collector);
        image_controller_destroy(&view->controller);
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
