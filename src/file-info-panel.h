#include <ui.h>
#include "file-info-reader.h"

void ui_register_file_info_panel(void);

ui_widget_t *ui_create_file_info_panel(void);

void file_info_panel_update(ui_widget_t *w);

void ui_load_file_info_panel_resources(void);

void file_info_panel_set_info(ui_widget_t *w, file_info_t *info);
