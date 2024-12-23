#include <string.h>

const char *str_last_char(const char *str, char ch);
const char *path_last_sep(const char *path);
const char *path_basename(const char *path);
char *path_from(const char *str);
char *path_dirname(const char *path);
char *path_join(const char *dir, const char *name);
int format_size(char buf[16], size_t size);
