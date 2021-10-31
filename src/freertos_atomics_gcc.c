#include <FreeRTOS.h>
#include <stdbool.h>

bool __atomic_compare_exchange_4(volatile void *ptr, void *expected, unsigned int desired, bool weak, int success_memorder, int failure_memorder) {
    bool ret = false;

    portENTER_CRITICAL();
    
    if (*(unsigned int *)ptr == *(unsigned int *)expected) {
        *(unsigned int *)ptr = desired;
        ret = true;
    } else {
        ret = false;
    }

    portEXIT_CRITICAL();

    return ret;
}
