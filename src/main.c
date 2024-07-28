﻿#include "main.h"
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
    char *dirname = path_dirname(argv[0]);
    chdir(dirname);
    free(dirname);
#endif

    lcui_app_init();

    ui_widget_append(ui_root(), ui_create_home());

    return lcui_app_run();
}