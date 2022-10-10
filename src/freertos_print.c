#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>

void rtos_debug_hook(void) {

    TaskStatus_t tasks[10];
    uint32_t total_time;
    int count = uxTaskGetSystemState(tasks, 10, &total_time);

    /* Divide by 100 for percentace calculations */
    total_time /= 100;

    /* Create a human readable table from the binary data. */
    for(int i = 0; i < count; i++) {

        printf("%s\t", tasks[i].pcTaskName);

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

        printf("\tprio: %lu", tasks[i].uxCurrentPriority);
        printf("\tstack: %lu", tasks[i].usStackHighWaterMark);
        printf("\tid: %lu", tasks[i].xTaskNumber);
        printf("\tload: %lu%%", tasks[i].ulRunTimeCounter / total_time);
        printf("\n");
        
    }

}   