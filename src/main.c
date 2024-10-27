
#include "main.h"
#include "utils.h"

#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif

static void on_timer(void *arg)
{
        ui_print_tree(NULL);
}

int main(int argc, char *argv[])
{
        int ret;

#ifndef DEBUG
        char *dirname = path_dirname(argv[0]);
        chdir(dirname);
        free(dirname);
#endif

        lcui_app_init();
        // ui_widget_resize(ui_root(), 200, 800);
        // ptk_set_timeout(10000, on_timer, NULL);

        // if (argc > 1) {
        if (1) {
                ui_widget_t *view = ui_create_image_view();
                ui_widget_append(ui_root(), view);
                // image_view_load_file(view, argv[1]);
                image_view_load_file(view, "C:\\Users\\LC-So\\Pictures\\狗狗.jpg");
        } else {
                ui_widget_append(ui_root(), ui_create_home());
                ui_widget_set_title(ui_root(), L"kantu");
        }

        ret = lcui_app_run();
        return ret;
}
