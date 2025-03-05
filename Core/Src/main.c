#define STM32L0xx
#include "stm32l072xx.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "board_config.h"
#include "main.h"
#include "spi.h"
#include "l80_m39.h"
#include "sx_1276.h"

void SystemInit()
{  
}

void delay_ms(uint32_t ms) {
    for (int i = 0; i < ms * SystemClock / 1000; i++);
}

int main(void)
{
    SetClock(Clock_Configuration);
    UART_SetRegisters(UART_Debug);
    SX1276_Init(SX1276_Obj);
    __uint8_t word = 0x2d;
    SX1276_Transmit(SX1276_Obj, word);
    UART_printf("-------------------------------------------------\r\n");
}   

