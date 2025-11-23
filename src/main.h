#include <locale.h>
#include <LCUI.h>
#include <LCUI/main.h>
#include "file-info-panel.h"
#include "film-view.h"
#include "home.h"
#include "image-view.h"
#include "slider.h"
#include "toggle-button.h"

static void app_init(void)
{
        lcui_init();
        ui_load_file_info_panel_resources();
        ui_load_film_view_resources();
        ui_load_home_resources();
        ui_load_image_view_resources();
        ui_load_slider_resources();
        ui_load_toggle_button_resources();
        ui_register_file_info_panel();
        ui_register_film_view();
        ui_register_home();
        ui_register_image_view();
        ui_register_slider();
        ui_register_toggle_button();
}

static int app_run(void)
{
        return lcui_run();
}
