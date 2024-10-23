/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 * Free pins are configured automatically as Analog (this feature is enabled through
 * the Code Generation settings)
 */
void MX_GPIO_Init(void) {
    LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
    LL_PWR_EnableVddIO2();

    //    /**/
    //    LL_GPIO_ResetOutputPin(GPIOB, LD3_Pin | LD2_Pin);
    //
    //    /**/
    //    LL_GPIO_ResetOutputPin(GPIOG, LL_GPIO_PIN_6);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_2 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4 | LL_GPIO_PIN_5 | LL_GPIO_PIN_6 |
    //                          LL_GPIO_PIN_7 | LL_GPIO_PIN_8 | LL_GPIO_PIN_9 | LL_GPIO_PIN_10 | LL_GPIO_PIN_11 |
    //                          LL_GPIO_PIN_12 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15 | LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4 |
    //                          LL_GPIO_PIN_5 | LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8 | LL_GPIO_PIN_9 |
    //                          LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOF, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_3;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOH, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin =
    //        LL_GPIO_PIN_0 | LL_GPIO_PIN_5 | LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8 | LL_GPIO_PIN_10 |
    //        LL_GPIO_PIN_12;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_2 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4 | LL_GPIO_PIN_15;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_10 | LL_GPIO_PIN_11 |
    //                          LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_15 | LL_GPIO_PIN_4 | LL_GPIO_PIN_5 |
    //                          LL_GPIO_PIN_6 | LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4 |
    //                          LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_15;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LD3_Pin | LD2_Pin;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    //    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    //    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9 | LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 |
    //                          LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15 | LL_GPIO_PIN_0 | LL_GPIO_PIN_1 |
    //                          LL_GPIO_PIN_2 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4 | LL_GPIO_PIN_5 | LL_GPIO_PIN_6 |
    //                          LL_GPIO_PIN_7;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);
    //
    //    /**/
    //    GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    //    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    //    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    //    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    //    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    //    LL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    //
    //    /**/
    //    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);
    //
    //    /**/
    //    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
    //    EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
    //    EXTI_InitStruct.LineCommand = ENABLE;
    //    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    //    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    //    LL_EXTI_Init(&EXTI_InitStruct);
    //
    //    /**/
    //    LL_GPIO_SetPinPull(B1_GPIO_Port, B1_Pin, LL_GPIO_PULL_NO);
    //
    //    /**/
    //    LL_GPIO_SetPinMode(B1_GPIO_Port, B1_Pin, LL_GPIO_MODE_INPUT);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
