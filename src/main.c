#include "main.h"
#include "utils.h"

#ifdef _WIN32
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif

void setcwd(const char *path)
{
#ifndef DEBUG
        char *binpath = path_from(path);
        char *dirname = path_dirname(binpath);
        chdir(dirname);
        free(binpath);
        free(dirname);
#endif
}

int main(int argc, char *argv[])
{
        setcwd(argv[0]);
        setlocale(LC_ALL, "");
        app_init();
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
        return app_run();
}
