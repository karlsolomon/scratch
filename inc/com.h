#ifndef _COM_H_
#define _COM_H_
#include <cstdint>
#include <cstdio>
#include <map>

#include "ring.h"
#include "stm32l4xx_ll_gpio.h"

class COMPort {
 private:
    Ring<uint8_t> input = Ring<uint8_t>(0);
    Ring<uint8_t> output = Ring<uint8_t>(0);
    LL_GPIO_InitTypeDef tx;
    LL_GPIO_InitTypeDef rx;
    GPIO_TypeDef *port;
    USART_TypeDef *usart;
    uint32_t baudRate;
    int priority = 0;
    static std::map<USART_TypeDef *, COMPort *> ports;
    static std::map<USART_TypeDef *, std::pair<IRQn_Type, uint32_t>> irqMap;

 public:
    COMPort() = delete;
    COMPort(GPIO_TypeDef *port, USART_TypeDef *usart, LL_GPIO_InitTypeDef tx, size_t maxOutputSize,
            LL_GPIO_InitTypeDef rx, size_t maxInputSize, uint32_t baudRate);
    COMPort(GPIO_TypeDef *port, USART_TypeDef *usart, LL_GPIO_InitTypeDef tx, size_t maxOutputSize,
            LL_GPIO_InitTypeDef rx, size_t maxInputSize, uint32_t baudRate, int priority);
    ~COMPort() { COMPort::ports.erase(this->usart); }
    void configure();
    void putc(const uint8_t *c) { this->output.push(*c); }
    void puts(const uint8_t *, size_t len);
    void getc(uint8_t *const c) { this->input.pop(c); }
    void gets(uint8_t *, size_t len);
    auto getInputSize() -> size_t { return this->input.getN(); }
    auto isInputEmpty() -> bool { return this->input.isEmpty(); }
    auto isOutputFull() -> bool { return this->output.isFull(); }
    static void irqHandler(USART_TypeDef *);
};

#endif  // _COM_H_
