#ifndef __HC05_H
#define __HC05_H

#include "stm32f1xx_hal.h"
#include "string.h"
#include "usart.h"

#define HC05_HUART &huart1				/* 配置串口号 */

void HC05_Init();
void HC05_SendCMD(char *commond);

#endif
