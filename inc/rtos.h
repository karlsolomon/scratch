#ifndef _TASK_UTILS_H_
#define _TASK_UTILS_H_

#include "FreeRTOS.h"

#define DEFAULT_TASK_STACK_SIZE 128

#define RTOS_PRIORITY_HIGHEST (configMAX_PRIORITIES - 1)

using RTOS_Priority_e = enum {
    RTOS_PRIORITY_IDLE = 0,
    RTOS_PRIORITY_LOW = 1,
    RTOS_PRIORITY_NORMAL = 2,
    RTOS_PRIORITY_HIGH = 3,
    RTOS_PRIORITY_MAX = RTOS_PRIORITY_HIGHEST
};
void vcpTask(void *parameters);
void heartbeatTask(void *parameters);
void exampleTask(void *parameters);
void RTOS_Init();
#endif
