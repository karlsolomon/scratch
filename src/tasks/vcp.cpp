
#include "vcp.h"

#include <cstdint>
#include <cstring>
#include <string>

#include "FreeRTOS.h"
#include "com.h"
#include "main.h"
#include "pins.h"
#include "portmacro.h"
#include "projdefs.h"
#include "rtos.h"
#include "semphr.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_ll_gpio.h"
#include "task.h"

void vcpSemGetLazy();
void vcpSemGetRaiseHolder();
auto vcpSemPut() -> BaseType_t;
auto vcpPuts(std::string s);
auto vcpPuts(uint8_t *buf, size_t len);
auto vcpPutc(uint8_t c) -> void;

SemaphoreHandle_t vcpWriteSem;
StaticSemaphore_t vcpWriteSemBuf;
COMPort *port = nullptr;

/*****************
 * PUBLIC
 ****************/

void vcpTaskInit() {
    (void)xTaskCreate(vcpTask, "vcp", configMINIMAL_STACK_SIZE + ((VCP_BUFSIZE_TX + VCP_BUFSIZE_RX) / sizeof(uint32_t)),
                      nullptr, RTOS_PRIORITY_LOW, nullptr);
    LL_GPIO_InitTypeDef tx;
    tx.Pin = VCP_TX_PIN;
    tx.Alternate = LL_GPIO_AF_7;
    LL_GPIO_InitTypeDef rx;
    rx.Pin = VCP_RX_PIN;
    rx.Alternate = LL_GPIO_AF_7;

    __HAL_RCC_USART2_CLK_ENABLE();
    static COMPort com = COMPort(VCP_TX_PORT, USART2, tx, VCP_BUFSIZE_TX, rx, VCP_BUFSIZE_TX, VCP_BAUD);
    port = &com;
    port->configure();

    vcpWriteSem = xSemaphoreCreateBinaryStatic(&vcpWriteSemBuf);
    xSemaphoreGive(vcpWriteSem);
}

void vcpTask(void *parameters) {
    (void)parameters;
    for (;;) {
        // echo user input
        if (!port->isInputEmpty()) {
            uint8_t c;
            port->getc(&c);
            vcpSemGetLazy();
            port->putc(&c);
            vcpSemPut();
        }
        static size_t missedBytes = 0;
        if (port->getMissedBytes() > missedBytes) {
            std::string warning = "VCP missed bytes: " + std::to_string((uint32_t)port->getMissedBytes()) + "\n\r";
            vcpPutLazy(warning);
        }
        vTaskDelay(1);
    }
}

auto vcpPutLazy(std::string s) -> void { vcpPutLazy((uint8_t *)s.c_str(), s.length()); }
auto vcpPutUrgent(std::string s) -> void { vcpPutUrgent((uint8_t *)s.c_str(), s.length()); }

auto vcpPutLazy(uint8_t *buf, size_t len) -> void {
    while (!port->outputHasSpace(len)) {
        vTaskDelay(1);
    }
    vcpSemGetLazy();
    // TODO: check for enough space, if not raise priority of consumer
    port->puts(buf, len);
    vcpSemPut();
}

auto vcpPutUrgent(uint8_t *buf, size_t len) -> void {
    vcpSemGetRaiseHolder();
    // TODO: check for enough space, if not raise priority of consumer
    port->puts(buf, len);
    vcpSemPut();
}

/*****************
 * PRIVATE
 ****************/

void vcpSemGetLazy() { xSemaphoreTake(vcpWriteSem, pdMS_TO_TICKS(1000)); }
void vcpSemGetRaiseHolder() {
    BaseType_t res = xSemaphoreTake(vcpWriteSem, 0);

    // If current task is higher priority than holder, raise holder to current task's priority until we acquire the
    // mutex
    if (res == pdFAIL) {
        auto *holder = xSemaphoreGetMutexHolder(vcpWriteSem);
        auto origPri = uxTaskPriorityGet(holder);
        vTaskPrioritySet(holder, std::max(origPri, uxTaskPriorityGet(nullptr)));
        vcpSemGetLazy();
        vTaskPrioritySet(holder, origPri);
    }
}

auto vcpSemPut() -> BaseType_t { return xSemaphoreGive(vcpWriteSem); }
