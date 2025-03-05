#define STM32L0xx
#include "stm32l072xx.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "board_config.h"
#include "main.h"
#include "spi.h"
#include "l80_m39.h"

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
    UART_SetRegisters(UART_L80);
    
    __uint8_t temp;
    __uint8_t address = 0x01;
    __uint8_t data = 0x80;
    temp = SPI_ReadRegister(address, SPI_SX1276);
    UART_printf("The data of address 0x%x is: 0x%x\r\n",address, temp);
    
    // SPI_WriteRegister(address, data, SPI_SX1276);
    // temp = SPI_ReadRegister(address, SPI_SX1276);
    // UART_printf("The data of address 0x%x is: 0x%x\r\n",address, temp);
}   

