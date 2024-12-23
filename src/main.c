#include "main.h"
#include "utils.h"

#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[])
{
#ifndef DEBUG
        char *bin_path = path_from(argv[0]);
        char *dirname = path_dirname(bin_path);
        chdir(dirname);
        free(bin_path);
        free(dirname);
#endif

        setlocale(LC_ALL, "");
        lcui_app_init();
        if (argc > 1) {
                ui_widget_t *view = ui_create_image_view();
                char *file_path = path_from(argv[1]);
                ui_widget_append(ui_root(), view);
                image_view_load_file(view, file_path);
                free(file_path);
        } else {
                ui_widget_append(ui_root(), ui_create_home());
                ui_widget_set_title(ui_root(), L"kantu");
        }
        return lcui_app_run();
}
