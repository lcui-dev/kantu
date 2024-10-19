/** This file is generated from slider.tsx */
#include <ui.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct {
        ui_widget_t *bar;
        ui_widget_t *thumb;
} slider_refs_t;

typedef struct slider_react_state {
        double percentage;
} slider_react_state_t;

typedef struct slider_react {
        slider_react_state_t state;
        slider_refs_t refs;
} slider_react_t;

static ui_widget_prototype_t *slider_proto;

static void slider_init_prototype(void)
{
        slider_proto = ui_create_widget_prototype("slider", NULL);
}

static void slider_load_template(ui_widget_t *parent, slider_refs_t *refs)
{
        ui_widget_t *w[1];

        ui_widget_add_class(parent, "flex items-center px-[9px] h-[40px]");
        w[0] = ui_create_widget(NULL);
        ui_widget_add_class(w[0], "w-full h-[4px] rounded-[4px] bg-slate-500");
        refs->bar = ui_create_widget(NULL);
        ui_widget_add_class(refs->bar, "h-full bg-sky-500");
        ui_widget_append(w[0], refs->bar);
        refs->thumb = ui_create_widget(NULL);
        ui_widget_add_class(refs->thumb, "absolute top-[50%] -mt-[9px] w-[18px] h-[18px] rounded-[9px] border-[4px] bg-sky-500 border-slate-600 hover:border-[3px]");
        ui_widget_append(parent, w[0]);
        ui_widget_append(parent, refs->thumb);
}

static void slider_react_init_state(ui_widget_t *w)
{
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
        _that->state.percentage = 0;
}

static void slider_react_destroy_state(ui_widget_t *w)
{
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
}

static void slider_react_update(ui_widget_t *w)
{
        char* str_0 = NULL;
        size_t str_0_len = 8;
        char* str_2 = NULL;
        char* str_3 = strdup2("%");
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
        str_2 = malloc(sizeof(char) * 32);
        snprintf(str_2, 31, "%lf", _that->state.percentage);
        str_2[31] = 0;
        str_0_len += strlen(str_2);
        str_0_len += strlen(str_3);
        str_0 = malloc(sizeof(char) * str_0_len);
        strcpy(str_0, str_2);
        strcat(str_0, str_3);
        ui_widget_set_style_string(_that->refs.bar, "width", str_0);
        free(str_0);
        free(str_2);
        free(str_3);
}

static void slider_on_mousedown(ui_widget_t *w, ui_event_t *e, void *arg);

static void slider_on_mousemove(ui_widget_t *w, ui_event_t *e, void *arg);

static void slider_on_mouseup(ui_widget_t *w, ui_event_t *e, void *arg);

static void slider_react_init_events(ui_widget_t *w)
{
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
        ui_widget_on(w, "mousedown", slider_on_mousedown, w);
        ui_widget_on(w, "mousemove", slider_on_mousemove, w);
        ui_widget_on(w, "mouseup", slider_on_mouseup, w);
}

static void slider_react_init(ui_widget_t *w)
{
        slider_react_t *_that = ui_widget_get_data(w, slider_proto);
        slider_load_template(w, &_that->refs);
        slider_react_init_state(w);
        slider_react_init_events(w);
        slider_react_update(w);
}

static void slider_react_destroy(ui_widget_t *w)
{
        slider_react_destroy_state(w);
}

void ui_load_slider_resources(void)
{
}
