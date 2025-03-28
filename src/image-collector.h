#ifndef IMAGE_COLLECTOR_H
#define IMAGE_COLLECTOR_H

#include <yutil.h>

typedef enum {
        IMAGE_COLLECTOR_EVENT_OPEN,
        IMAGE_COLLECTOR_EVENT_FOUND,
        IMAGE_COLLECTOR_EVENT_FINISHED,
} image_collector_event_type_t;

typedef struct image_collector image_collector_t;

image_collector_t *image_collector_create(void);

void image_collector_destroy(image_collector_t *c);

void image_collector_listen(image_collector_t *c,
                            void (*callback)(image_collector_t *,
                                             image_collector_event_type_t,
                                             void *),
                            void *data);

void image_collector_notify(image_collector_t *c,
                            image_collector_event_type_t type);

void image_collector_load_file(image_collector_t *c, const char *file);

bool image_collector_has_next(image_collector_t *c);

bool image_collector_has_prev(image_collector_t *c);

void image_collector_next(image_collector_t *c);

void image_collector_prev(image_collector_t *c);

const char *image_collector_get_file(image_collector_t *c);

void image_collector_get_files(image_collector_t *c, list_t *files,
                               size_t index);

size_t image_collector_get_index(image_collector_t *c);

#endif
