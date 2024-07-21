#include <yutil.h>
#include <thread.h>

typedef enum {
        IMAGE_COLLECTOR_STATE_EXITED,
        IMAGE_COLLECTOR_STATE_READY,
        IMAGE_COLLECTOR_STATE_PENDING,
        IMAGE_COLLECTOR_STATE_LOADING,
        IMAGE_COLLECTOR_STATE_FINISHED,
        IMAGE_COLLECTOR_STATE_ERROR,
} image_collector_state_t;

typedef struct image_collector image_collector_t;

struct image_collector {
        char *file;
        image_collector_state_t state;
        list_t files;
        size_t index;
        char *dirname;
        thread_t tid;
        thread_mutex_t mutex;
        thread_cond_t cond;
        void *callback_arg;
        void (*callback)(image_collector_t *, void *);
};

void image_collector_init(image_collector_t *c);

void image_collector_destroy(image_collector_t *c);

void image_collector_load_file(image_collector_t *c, const char *file);

bool image_collector_has_next(image_collector_t *c);

bool image_collector_has_prev(image_collector_t *c);

char *image_collector_get_file(image_collector_t *c);

char *image_collector_next(image_collector_t *c);

char *image_collector_prev(image_collector_t *c);
