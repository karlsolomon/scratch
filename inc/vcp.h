#ifndef _VCP_H_
#define _VCP_H_
#include <string>

#include "FreeRTOS.h"
#define VCP_BUFSIZE_TX 32
#define VCP_BUFSIZE_RX 32
#define VCP_BAUD 921600

void vcpTask(void* parameters);
void vcpTaskInit();
void vcpPutLazy(uint8_t* buf, size_t len);
void vcpPutLazy(std::string s);
void vcpPutUrgent(uint8_t* buf, size_t len);
void vcpPutUrgent(std::string s);
#endif  // _VCP_H_
