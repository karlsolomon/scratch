/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "rtos.h"
#include "task.h"
void RTOS_Init() {
    (void)xTaskCreate(exampleTask, "example", configMINIMAL_STACK_SIZE, nullptr, RTOS_PRIORITY_IDLE, nullptr);
    (void)xTaskCreate(heartbeatTask, "heartbeat", configMINIMAL_STACK_SIZE, nullptr, RTOS_PRIORITY_LOW, nullptr);
    /*(void)xTaskCreate(vcpTask, "vcp", configMINIMAL_STACK_SIZE, nullptr, RTOS_PRIORITY_LOW, nullptr);*/
    vTaskStartScheduler();
}
void exampleTask(void *parameters) {
    (void)parameters;

    for (;;) {
        vTaskDelay(1); /* delay 100 ticks */
    }
}
