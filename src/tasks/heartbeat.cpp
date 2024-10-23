#include <ranges>
#include <utility>
#include <vector>

#include "main.h"
#include "pins.h"
#include "projdefs.h"
#include "rtos.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_ll_gpio.h"
#include "task.h"

static const LL_GPIO_InitTypeDef led1 = {.Pin = LD1_PIN,
                                         .Mode = LL_GPIO_MODE_OUTPUT,
                                         .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                                         .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                         .Pull = LL_GPIO_PULL_NO,
                                         .Alternate = LL_GPIO_AF_0};
static const LL_GPIO_InitTypeDef led2 = {.Pin = LD2_PIN,
                                         .Mode = LL_GPIO_MODE_OUTPUT,
                                         .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                                         .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                         .Pull = LL_GPIO_PULL_NO,
                                         .Alternate = LL_GPIO_AF_0};
static const LL_GPIO_InitTypeDef led3 = {.Pin = LD3_PIN,
                                         .Mode = LL_GPIO_MODE_OUTPUT,
                                         .Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
                                         .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                         .Pull = LL_GPIO_PULL_NO,
                                         .Alternate = LL_GPIO_AF_0};
static const std::vector<std::pair<GPIO_TypeDef *, LL_GPIO_InitTypeDef>> leds = {
    {LD1_PORT, led1}, {LD2_PORT, led2}, {LD3_PORT, led3}};

void heartbeatTask(void *parameters) {
    (void)parameters;
    // Initialize pins
    for (auto [port, pin] : leds) {
        LL_GPIO_Init(port, &pin);
    }
    while (true) {
        for (auto [port, pin] : leds) {
            LL_GPIO_TogglePin(port, pin.Pin);
            vTaskDelay(pdMS_TO_TICKS(50));
        }

        for (auto [port, pin] : std::ranges::reverse_view(leds)) {
            LL_GPIO_TogglePin(port, pin.Pin);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}
