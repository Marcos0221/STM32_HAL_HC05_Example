#include "HC05.h"

uint8_t HC05_RxBuffer[2];				// 长度两字节，分别用于 选择 和 控制

/**
 * 配置
 * GPIOA PIN3 推挽输出 默认高电平
 * USART1 波特率9600 开启中断
 */


// 串口中断接收的数据在这里处理
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// PC13 为低电平时，发光二极管会亮，这里做一个使用蓝牙控制 PC13 高低电平的实验
	if(HC05_RxBuffer[0] == 'L')
	{
		// 只要当蓝牙模块收到 L1 打开， L0 关闭
		if(HC05_RxBuffer[1] == '0')
		{
			// 关闭
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

			// 回复
			HAL_UART_Transmit_IT(HC05_HUART, (uint8_t*)"Received Successfully! L0\n", 26);
		}
		if(HC05_RxBuffer[1] == '1')
		{
			// 开启
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

			// 回复
			HAL_UART_Transmit_IT(HC05_HUART, (uint8_t*)"Received Successfully! L1\n", 26);
		}
	}

	// 再次开启接收，这样就可以实现持续对话
	HAL_UART_Receive_IT(HC05_HUART, HC05_RxBuffer, 2);
}

void HC05_Init()
{
	// 将 EN 引脚拉高，让蓝牙模块进入AT命令模式
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

	// 这里延时一下，等待蓝牙模块上电后再进行发送数据
	HAL_Delay(4000);

	// 先进入配置模式，此时蓝牙模块串口波特率为38400
	HAL_UART_DeInit(HC05_HUART);							// 重置串口
	MX_USART_UART_Init(HC05_HUART, USART1, 38400);			// 以 38400 波特率初始化串口

	/* 自定义配置 */
	HC05_SendCMD("AT+NAME=测试1\r\n");
	HC05_SendCMD("AT+PSWD=8888\r\n");
	// ...

	/* 自定义配置 */

	// 将 EN 引脚拉低，然后重启蓝牙模块
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

	// 重启蓝牙模块，这时候蓝牙模块串口的波特率为9600
	HC05_SendCMD("AT+RESET\r\n");

	HAL_UART_DeInit(HC05_HUART);							// 重置串口
	MX_USART1_UART_Init();

	// 开启串口中断接收
	HAL_UART_Receive_IT(HC05_HUART, HC05_RxBuffer, 2);
}

// 串口发送配置命令
void HC05_SendCMD(char *commond)
{
	HAL_UART_Transmit(HC05_HUART, (uint8_t*)commond, strlen(commond), 100);

}

