#include <yutil.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

const char *str_last_char(const char *str, char ch)
{
        const char *p, *ch_p = NULL;

        for (p = str; *p; p++) {
                if (*p == ch) {
                        ch_p = p;
                }
        }
        return ch_p;
}

const char *path_last_sep(const char *path)
{
        const char *sep1 = str_last_char(path, '\\');
        const char *sep2 = str_last_char(path, '/');

        if (sep1) {
                if (sep2) {
                        return sep1 > sep2 ? sep1 : sep2;
                }
                return sep1;
        }
        return sep2;
}

char *path_dirname(const char *path)
{
        size_t len;
        char *dirname;
        const char *sep = path_last_sep(path);

        if (!sep) {
                sep = path;
        }
        len = sep - path;
        dirname = malloc(sizeof(char) * (len + 1));
        strncpy(dirname, path, len);
        dirname[len] = 0;
        return dirname;
}

const char *path_basename(const char *path)
{
        const char *sep = path_last_sep(path);
        return sep == NULL ? path : sep + 1;
}

char *path_join(const char *dir, const char *name)
{
        size_t len;
        char *path;

        if (dir == NULL) {
                return strdup2(name);
        }
        len = strlen(dir) + strlen(name) + 1;
        path = malloc(sizeof(char) * (len + 1));
        snprintf(path, len + 1, "%s%c%s", dir, PATH_SEP, name);
        return path;
}

int format_size(char buf[16], size_t size)
{
        const char *units[] = { "B", "KB", "MB", "GB", "TB" };
        int i = 0;

        while (size >= 1024) {
                size /= 1024;
                i++;
        }
        return snprintf(buf, 16, "%zu %s", size, units[i]);
}
