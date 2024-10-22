#include "com.h"

#include <cstdint>

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_usart.h"

std::map<USART_TypeDef*, COMPort*> COMPort::ports = std::map<USART_TypeDef*, COMPort*>();

std::map<USART_TypeDef*, std::pair<IRQn_Type, uint32_t>> COMPort::irqMap =
    std::map<USART_TypeDef*, std::pair<IRQn_Type, uint32_t>>{
#if defined(USART1)
        {USART1, {USART1_IRQn, LL_RCC_USART1_CLKSOURCE_PCLK2}},
#endif
#if defined(USART2)
        {USART2, {USART2_IRQn, LL_RCC_USART2_CLKSOURCE_PCLK1}},
#endif
#if defined(USART3)
        {USART3, {USART3_IRQn, LL_RCC_USART3_CLKSOURCE_PCLK1}},
#endif
#if defined(UART4)
        {UART4, {UART4_IRQn, LL_RCC_UART4_CLKSOURCE_PCLK1}},
#endif
#if defined(UART5)
        {UART5, {UART5_IRQn, LL_RCC_UART5_CLKSOURCE_PCLK1}},
#endif
#if defined(USART6)
        {USART6, {USART6_IRQn, LL_RCC_USART6_CLKSOURCE_PCLK2}},
#endif
    };

COMPort::COMPort(GPIO_TypeDef* port, USART_TypeDef* usart, LL_GPIO_InitTypeDef tx, size_t maxOutputSize,
                 LL_GPIO_InitTypeDef rx, size_t maxInputSize, uint32_t baudRate) {
    this->input = Ring<uint8_t>(maxInputSize);
    this->output = Ring<uint8_t>(maxOutputSize);
    this->rx = rx;
    this->tx = tx;
    this->usart = usart;
    this->port = port;
    this->baudRate = baudRate;
    ports[usart] = this;
    LL_USART_Disable(this->usart);
}

COMPort::COMPort(GPIO_TypeDef* port, USART_TypeDef* usart, LL_GPIO_InitTypeDef tx, size_t maxOutputSize,
                 LL_GPIO_InitTypeDef rx, size_t maxInputSize, uint32_t baudRate, int priority)
    : COMPort(port, usart, tx, maxOutputSize, rx, maxInputSize, baudRate) {
    this->priority = priority;
}

void COMPort::irqHandler(USART_TypeDef* uart) {
    uint8_t c;
    COMPort* com = ports[uart];
    if (LL_USART_IsActiveFlag_RXNE(uart)) {
        c = LL_USART_ReceiveData8(com->usart);
        com->input.push(c);
    }
    if (LL_USART_IsActiveFlag_TXE(com->usart) && LL_USART_IsActiveFlag_TC(com->usart)) {
        if (com->output.isEmpty()) {
            LL_USART_DisableIT_TXE(com->usart);  // no need to fire interrupt if the buffer is empty
        } else {
            com->output.pop(&c);
            LL_USART_TransmitData8(com->usart, c);
        }
    }
}

void COMPort::puts(uint8_t const* const buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        putc(buf + i);
    }
    if (!LL_USART_IsEnabledIT_TXE(this->usart)) {
        LL_USART_EnableIT_TXE(this->usart);  //  enable TXE interrupt
    }
}

void COMPort::gets(uint8_t* const buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        getc(buf + i);
    }
}
void COMPort::configure() {
    this->tx.Mode = LL_GPIO_MODE_ALTERNATE;
    this->tx.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    this->tx.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    this->tx.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(this->port, &this->tx);

    this->rx.Mode = LL_GPIO_MODE_ALTERNATE;
    this->rx.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    this->rx.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    this->rx.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(this->port, &this->rx);

    LL_USART_InitTypeDef USART_InitStruct;
    /*USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;*/
    USART_InitStruct.BaudRate = this->baudRate;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(this->usart, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(this->usart);
    LL_USART_EnableDirectionTx(this->usart);
    LL_USART_EnableDirectionRx(this->usart);
    if (!LL_USART_IsEnabledIT_TXE(this->usart)) {
        LL_USART_EnableIT_TXE(this->usart);
    }
    if (!LL_USART_IsEnabledIT_RXNE(this->usart)) {
        LL_USART_EnableIT_RXNE(this->usart);
    }
    NVIC_SetPriority(irqMap[this->usart].first, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(irqMap[this->usart].first);
    LL_RCC_SetUSARTClockSource(irqMap[this->usart].second);
    LL_USART_Enable(this->usart);
};
