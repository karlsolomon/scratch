#ifndef _PINS_H_
#define _PINS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LD1_PORT GPIOC
#define LD1_PIN LL_GPIO_PIN_7
#define LD2_PORT GPIOB
#define LD2_PIN LL_GPIO_PIN_7
#define LD3_PORT GPIOB
#define LD3_PIN LL_GPIO_PIN_14
#define BTN1_PORT GPIOA
#define BTN1_PIN LL_GPIO_PIN_13

#define VCP_TX_PORT GPIOA
#define VCP_TX_PIN LL_GPIO_PIN_2
#define VCP_RX_PORT GPIOA
#define VCP_RX_PIN LL_GPIO_PIN_3

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _PINS_H_
