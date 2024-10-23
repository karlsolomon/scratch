
#include "com.h"
#include "main.h"
#include "pins.h"
#include "projdefs.h"
#include "rtos.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_ll_gpio.h"
#include "task.h"

void vcpTask(void *parameters) {
    (void)parameters;
#define BUFSIZE 128
#define BAUD 9600
    LL_GPIO_InitTypeDef tx;
    tx.Pin = VCP_TX_PIN;
    tx.Alternate = LL_GPIO_AF_7;
    LL_GPIO_InitTypeDef rx;
    rx.Pin = VCP_RX_PIN;
    rx.Alternate = LL_GPIO_AF_7;

    __HAL_RCC_USART2_CLK_ENABLE();
    COMPort com = COMPort(VCP_TX_PORT, USART2, tx, BUFSIZE, rx, BUFSIZE, BAUD);
    com.configure();

    for (;;) {
        while (!com.isInputEmpty()) {
            uint8_t c;
            com.getc(&c);
            com.puts(&c, 1);
        }
        vTaskDelay(1);
    }
}
