#include <time.h>

typedef struct file_info {
        char name[256];
        char file_size[32];
        char image_size[32];
        char *path;
        time_t mtime;
        unsigned width;
        unsigned height;
        unsigned bits;
} file_info_t;

typedef struct file_info_reader file_info_reader_t;

file_info_reader_t *file_info_reader_create(void (*callback)(file_info_t *, void *),
                                             void *callback_arg);

void file_info_reader_destroy(file_info_reader_t *reader);

void file_info_reader_load_file(file_info_reader_t *reader, const char *path);
