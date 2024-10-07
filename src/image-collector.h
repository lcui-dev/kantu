#include <yutil.h>
#include <thread.h>

typedef enum {
        IMAGE_COLLECTOR_EVENT_OPEN,
        IMAGE_COLLECTOR_EVENT_FOUND,
        IMAGE_COLLECTOR_EVENT_FINISHED,
} image_collector_event_type_t;

void image_collector_init(void);

void image_collector_destroy(void);

void image_collector_load_file(const char *file);

bool image_collector_has_next(void);

bool image_collector_has_prev(void);

const char *image_collector_get_file(void);

void image_collector_next(void);

void image_collector_prev(void);

size_t image_collector_get_index(void);

void image_collector_get_files(list_t *files, size_t index);

void image_collector_listen(void (*callback)(image_collector_event_type_t, void *),
                        void *data);
