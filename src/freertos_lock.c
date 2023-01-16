#include <FreeRTOS.h>
#include <semphr.h>


int si_lock_take(void* lock, int block_time_ms) {

    if (block_time_ms == -1)
        block_time_ms = portMAX_DELAY;

    if (lock == NULL)
        return -1;

    if (xSemaphoreTake((SemaphoreHandle_t)lock, pdMS_TO_TICKS(block_time_ms)) == pdTRUE)
        return 0;

    return -1;
}

int si_lock_give(void* lock) {

    if (lock == NULL)
        return -1;

    xSemaphoreGive((SemaphoreHandle_t)lock);
    return 0;
}

static StaticSemaphore_t lock_buf[NUM_LOCKS];
static SemaphoreHandle_t lock[NUM_LOCKS] = { NULL };

void* si_lock_init(void) {

    for (int i = 0; i < NUM_LOCKS; i++) {
        if (lock[i] == NULL) {
            lock[i] = xSemaphoreCreateMutexStatic(&lock_buf[i]);
            return lock[i];
        }
    }

    return NULL;
}
