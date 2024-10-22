#ifndef _TASK_UTILS_H_
#define _TASK_UTILS_H_

#include "FreeRTOS.h"

using osStaticThreadDef_t = StaticTask_t;
using osStaticMessageQDef_t = StaticQueue_t;
using osStaticTimerDef_t = StaticTimer_t;
using osStaticMutexDef_t = StaticSemaphore_t;
using osStaticSemaphoreDef_t = StaticSemaphore_t;
using osStaticEventGroupDef_t = StaticEventGroup_t;

#define DEFAULT_TASK_STACK_SIZE 128

void RTOS_Init();
#endif
