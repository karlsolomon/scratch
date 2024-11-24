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
#define VCP_TX_AF LL_GPIO_AF_7
#define VCP_RX_PORT GPIOA
#define VCP_RX_PIN LL_GPIO_PIN_3
#define VCP_RX_AF LL_GPIO_AF_7

#define I2C_SCL_PORT GPIOB
#define I2C_SCL_PIN LL_GPIO_PIN_8
#define I2C_SCL_AF LL_GPIO_AF_4
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN LL_GPIO_PIN_9
#define I2C_SDA_AF LL_GPIO_AF_4

#define SPI_NSS_PORT GPIOA
#define SPI_NSS_PIN LL_GPIO_PIN_4
#define SPI_NSS_AF LL_GPIO_AF_5
#define SPI_SCK_PORT GPIOA
#define SPI_SCK_PIN LL_GPIO_PIN_5
#define SPI_SCK_AF LL_GPIO_AF_5
#define SPI_MISO_PORT GPIOA
#define SPI_MISO_PIN LL_GPIO_PIN_6
#define SPI_MISO_AF LL_GPIO_AF_5
#define SPI_MOSI_PORT GPIOA
#define SPI_MOSI_PIN LL_GPIO_PIN_7
#define SPI_MOSI_AF LL_GPIO_AF_5
#define SPI_CS_PORT GPIOA
#define SPI_CS_PIN LL_GPIO_PIN_0
#define SPI_CS_AF LL_GPIO_AF_0

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _PINS_H_
