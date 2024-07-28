#include <locale.h>
#include <LCUI.h>
#include <LCUI/main.h>
#include "home.h"

static void lcui_app_init(void)
{
        setlocale(LC_CTYPE, "");
        lcui_init();
        ui_load_home_resources();
        ui_register_home();
}

static int lcui_app_run(void)
{
        return lcui_run();
}

