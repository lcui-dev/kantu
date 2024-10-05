#include <ui.h>

typedef struct file_info {
        char name[256];
        char file_size[32];
        char image_size[32];
        time_t mtime;
        unsigned bits;
} file_info_t;

void ui_register_file_info_panel(void);

ui_widget_t *ui_create_file_info_panel(void);

file_info_t *file_info_panel_load_file(ui_widget_t *w, const char *path);

void file_info_panel_update(ui_widget_t *w);

void ui_load_file_info_panel_resources(void);
