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
#include "vcp.h"
void RTOS_Init() {
    (void)xTaskCreate(exampleTask, "example", configMINIMAL_STACK_SIZE, nullptr, EXAMPLE_PRIORITY, nullptr);
    (void)xTaskCreate(heartbeatTask, "heartbeat", configMINIMAL_STACK_SIZE, nullptr, HEARTBEAT_PRIORITY, nullptr);
    vcpTaskInit();
    vTaskStartScheduler();
}
void exampleTask(void *parameters) {
    (void)parameters;

    for (;;) {
        vTaskDelay(1); /* delay 100 ticks */
    }
}
