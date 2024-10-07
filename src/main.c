#include <locale.h>
#include "main.h"
#include "utils.h"
#include "image-collector.h"

#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[])
{
        int ret;

#ifndef DEBUG
        char *dirname = path_dirname(argv[0]);
        chdir(dirname);
        free(dirname);
#endif

        lcui_app_init();
        image_collector_init();
        ui_widget_resize(ui_root(), 1280, 800);

        if (argc > 1) {
                ui_widget_t *view = ui_create_image_view();
                ui_widget_append(ui_root(), view);
                image_collector_load_file(view, argv[1]);
        } else {
                ui_widget_append(ui_root(), ui_create_home());
                ui_widget_set_title(ui_root(), L"kantu");
        }

        ret = lcui_app_run();
        image_collector_destroy();
        return ret;
}
