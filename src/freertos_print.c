 #include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>

#define MAX_TASKS 20

uint32_t task_time_last[MAX_TASKS];
uint32_t time_last;
uint32_t time_now;

void rtos_debug_hook(void) {

    time_last = time_now;

    TaskStatus_t tasks[uxTaskGetNumberOfTasks()];
    int count = uxTaskGetSystemState(tasks, MAX_TASKS, &time_now);

    /* Divide by 100 for percentace calculations */
    uint32_t total_time = (time_now - time_last) / 100;

    printf("\nCPU usage averaged over last %lu msec\n", total_time/10);

    /* Create a human readable table from the binary data. */
    for(int i = 0; i < count; i++) {

        if (tasks[i].xTaskNumber >= MAX_TASKS) {
            continue;
        }

        printf("%s\t", tasks[i].pcTaskName);

#if 0
        switch(tasks[i].eCurrentState) {
            case eRunning:
                printf("running ");
                break;
            case eReady:
                printf("ready   ");
                break;
            case eBlocked:
                printf("blocked ");
                break;
            case eSuspended:
                printf("suspend ");
                break;
            case eDeleted:
                printf("deleted ");
                break;
            case eInvalid: /* Fall through. */
            default:
                break;
        }
#endif

        uint32_t time_consumed = tasks[i].ulRunTimeCounter - task_time_last[tasks[i].xTaskNumber];
        task_time_last[tasks[i].xTaskNumber] = tasks[i].ulRunTimeCounter;

        printf("\tprio: %lu", tasks[i].uxCurrentPriority);
        printf("\tstack: %lu", tasks[i].usStackHighWaterMark);
        printf("\tid: %lu", tasks[i].xTaskNumber);
        printf("\tload: %lu%%", time_consumed / total_time);
        printf("\n");
        
    }

#if configSUPPORT_DYNAMIC_ALLOCATION > 0
    HeapStats_t pxHeapStats;
    vPortGetHeapStats(&pxHeapStats);
    if (pxHeapStats.xNumberOfSuccessfulAllocations > 0) {
        printf("Free Heap: %zu Bytes, Minimum since boot: %zu Bytes\n", pxHeapStats.xAvailableHeapSpaceInBytes, pxHeapStats.xMinimumEverFreeBytesRemaining);
    } else {
        printf("Application heap not in use\n");
    }
#endif

}
