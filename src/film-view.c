#include <ptk.h>
#include <LCUI/app.h>
#include <ui_widgets.h>
#include "film-view.tsx.h"
#include "film-view.h"

typedef enum {
        FILM_VIEW_STATE_PENDING,
        FILM_VIEW_STATE_LOADED,
        FILM_VIEW_STATE_FINISHED,
} film_view_state_t;

typedef struct {
        film_view_react_t base;
        film_view_state_t state;
        image_collector_t *collector;
        size_t loaded_index;
        size_t index;
        int timer;
} film_view_t;

static film_view_t *film_view_get(ui_widget_t *w)
{
        return ui_widget_get_data(w, film_view_proto);
}

static void film_view_select(ui_widget_t *w)
{
        ui_widget_t *child;
        film_view_t *view = film_view_get(w);

        child = ui_widget_get_child(view->base.refs.content, view->index);
        if (child) {
                ui_widget_remove_class(child, "selected");
        }
        view->index = image_collector_get_index(view->collector);
        child = ui_widget_get_child(view->base.refs.content, view->index);
        if (child) {
                ui_widget_add_class(child, "selected");
                if (!ui_widget_in_viewport(child)) {
                        ui_scrollarea_set_scroll_left(
                            w, child->border_box.x - w->padding_box.width / 2);
                }
        }
}

static void film_view_on_collector_event(image_collector_t *c,
                                         image_collector_event_type_t type,
                                         void *arg)
{
        film_view_t *view = film_view_get(arg);

        switch (type) {
        case IMAGE_COLLECTOR_EVENT_FINISHED:
                view->state = FILM_VIEW_STATE_LOADED;
                logger_debug("[film-view] image collector finished\n");
                break;
        case IMAGE_COLLECTOR_EVENT_FOUND:
                film_view_select(arg);
                logger_debug("[film-view] image collector index changed: %d\n",
                             view->index);
                break;
        default:
                break;
        }
}

static void film_view_on_click(ui_widget_t *w, ui_event_t *e, void *arg)
{
        film_view_t *view = film_view_get(w);
        ui_widget_t *target = e->target;

        for (; target; target = target->parent) {
                if (ui_widget_has_class(target, "film-view-item")) {
                        image_collector_load_file(
                            view->collector,
                            ui_widget_get_attr(target, "data-src"));
                        break;
                }
        }
}

static void film_view_init(ui_widget_t *w)
{
        film_view_t *view;
        film_view_proto->proto->init(w);
        view = ui_widget_add_data(w, film_view_proto, sizeof(film_view_t));
        view->state = FILM_VIEW_STATE_PENDING;
        view->index = 0;
        view->loaded_index = 0;
        view->collector = NULL;
        film_view_react_init(w);
        ui_scrollarea_set_wheel_scroll_direction(w, UI_SCROLLAREA_HORIZONTAL);
        ui_widget_on(w, "click", film_view_on_click, w);
        film_view_update(w);
}

static void film_view_destroy(ui_widget_t *w)
{
        film_view_t *view = film_view_get(w);

        if (view->timer) {
                ptk_clear_interval(view->timer);
        }
        film_view_react_destroy(w);
}

static void film_view_append_image(ui_widget_t *w, const char *file)
{
        ui_widget_t *item = ui_create_widget(NULL);
        ui_widget_add_class(item, "film-view-item");
        ui_widget_set_background_image_url(item, file);
        ui_widget_set_attr(item, "data-src", file);
        ui_widget_append(w, item);
}

static void film_view_load_images(void *arg)
{
        ui_widget_t *w = arg;
        film_view_t *view = film_view_get(w);
        list_t files;
        list_node_t *node;

        list_create(&files);
        image_collector_get_files(view->collector, &files, view->loaded_index);
        for (list_each(node, &files)) {
                film_view_append_image(view->base.refs.content, node->data);
        }
        view->loaded_index += files.length;
        if (view->state == FILM_VIEW_STATE_LOADED) {
                ptk_clear_interval(view->timer);
                view->timer = 0;
                view->state = FILM_VIEW_STATE_FINISHED;
        }
        lcui_post_task(w, (worker_task_cb)film_view_select, NULL);
        logger_debug("[film-view] loaded %d images, state=%d\n", files.length,
                     view->state);
        list_destroy(&files, free);
}

void film_view_update(ui_widget_t *w)
{
        film_view_react_update(w);
}

ui_widget_t *ui_create_film_view(void)
{
        return ui_create_widget_with_prototype(film_view_proto);
}

void film_view_show(ui_widget_t *w)
{
        film_view_t *view = film_view_get(w);
        ui_widget_remove_class(w, "hidden");
        if (view->collector && !view->timer &&
            view->state != FILM_VIEW_STATE_FINISHED) {
                view->timer = ptk_set_interval(500, film_view_load_images, w);
        }
}

void film_view_set_image_collector(ui_widget_t *w, image_collector_t *c)
{
        film_view_t *view = film_view_get(w);

        view->collector = c;
        image_collector_listen(c, film_view_on_collector_event, w);
}

void film_view_hide(ui_widget_t *w)
{
        ui_widget_add_class(w, "hidden");
}

void ui_register_film_view(void)
{
        film_view_init_prototype();
        film_view_proto->init = film_view_init;
        film_view_proto->destroy = film_view_destroy;
}
