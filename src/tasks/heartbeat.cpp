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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <ranges>
#include <utility>
#include <vector>

#include "cmsis_os.h"
#include "main.h"
#include "pins.h"
#include "stm32l4xx_hal_gpio.h"
#include "task.h"
#include "taskUtils.h"

/* Definitions for heartbeatTask */
void heartbeatTask(void *argument);

osThreadId_t heartbeatTaskHandle;
uint32_t heartbeatTaskBuffer[DEFAULT_TASK_STACK_SIZE];
osStaticThreadDef_t heartbeatTaskControlBlock;
const osThreadAttr_t heartbeatTask_attributes = {
    .name = "heartbeatTask",
    .cb_mem = &heartbeatTaskControlBlock,
    .cb_size = sizeof(heartbeatTaskControlBlock),
    .stack_mem = &heartbeatTaskBuffer[0],
    .stack_size = sizeof(heartbeatTaskBuffer),
    .priority = (osPriority_t)osPriorityNormal1,
};

void heartbeatTaskInit() {
    /* creation of heartbeatTask */
    heartbeatTaskHandle = osThreadNew(heartbeatTask, nullptr, &heartbeatTask_attributes);
}

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
 * @brief Function implementing the heartbeatTask thread.
 * @param argument: Not used
 * @retval None
 */
void heartbeatTask(void *argument) {
    /* Add your application code here */
    LL_GPIO_InitTypeDef btn = {.Pin = LL_GPIO_PIN_13,
                               .Mode = LL_GPIO_MODE_INPUT,
                               .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                               .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                               .Pull = LL_GPIO_PULL_NO,
                               .Alternate = LL_GPIO_AF_0};
    LL_GPIO_InitTypeDef led1 = {.Pin = LD1_PIN,
                                .Mode = LL_GPIO_MODE_OUTPUT,
                                .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                                .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                .Pull = LL_GPIO_PULL_NO,
                                .Alternate = LL_GPIO_AF_0};
    LL_GPIO_InitTypeDef led2 = {.Pin = LD2_PIN,
                                .Mode = LL_GPIO_MODE_OUTPUT,
                                .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                                .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                .Pull = LL_GPIO_PULL_NO,
                                .Alternate = LL_GPIO_AF_0};
    LL_GPIO_InitTypeDef led3 = {.Pin = LD3_PIN,
                                .Mode = LL_GPIO_MODE_OUTPUT,
                                .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                                .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                .Pull = LL_GPIO_PULL_NO,
                                .Alternate = LL_GPIO_AF_0};

    std::vector<std::pair<GPIO_TypeDef *, LL_GPIO_InitTypeDef>> pins = {
        {GPIOC, btn}, {LD1_PORT, led1}, {LD2_PORT, led2}, {LD3_PORT, led3}};

    std::vector<std::pair<GPIO_TypeDef *, LL_GPIO_InitTypeDef>> leds = {
        std::vector<std::pair<GPIO_TypeDef *, LL_GPIO_InitTypeDef>>(pins.begin() + 1, pins.end()),
    };

    // Initialize pins
    for (auto [port, pin] : pins) {
        LL_GPIO_Init(port, &pin);
    }

    for (auto [port, pin] : leds) {
        LL_GPIO_SetOutputPin(port, pin.Pin);
    }

    while (true) {
        for (auto [port, pin] : leds) {
            LL_GPIO_TogglePin(port, pin.Pin);
            /*osDelay(50);*/
            LL_mDelay(50);
        }

        for (auto [port, pin] : std::ranges::reverse_view(leds)) {
            LL_GPIO_TogglePin(port, pin.Pin);
            /*osDelay(50);*/
            LL_mDelay(50);
        }
    }
}
