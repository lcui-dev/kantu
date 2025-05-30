#include <errno.h>
#include <locale.h>
#include <stdio.h>
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
        if (chdir(dirname) != 0) {
                perror("chdir");
        }
        free(binpath);
        free(dirname);
#endif
}

int main(int argc, char *argv[])
{
        setcwd(argv[0]);
        setlocale(LC_CTYPE, "");
        app_init();
        ui_widget_set_title(ui_root(), L"Kantu");
        if (argc > 1) {
                ui_widget_t *view = ui_create_image_view();
                char *filepath = path_from(argv[1]);
                ui_widget_append(ui_root(), view);
                image_view_load_file(view, filepath);
                free(filepath);
        } else {
                ui_widget_append(ui_root(), ui_create_home());
        }
        return app_run();
}
