#define STM32L0xx
#define CPU_FREQ 16000000
#include "stm32l072xx.h"
#include "main.h"
#include "rcc.h"
#include "uart.h"
#include "board_config.h"
#include "spi.h"
void SystemInit()
{  
}

void delay_ms(uint32_t ms) {
    for (int i = 0; i < ms * CPU_FREQ / 1000; i++);
}

int main(void)
{
    SetClock_HSI16();
    struct UART_Configuration uart_config;
    uart_config.baud_rate = 9600;
    uart_config.clock_rate = 16000000;

    UART_debug_set_registers(uart_config.clock_rate, 
    uart_config.baud_rate);
    
    UART_l80_m39_set_registers(uart_config.clock_rate,
    uart_config.baud_rate
    );

    
    RCC->IOPENR |= (0x1 << 1); // Enable GPIOB clock
    RCC->IOPSMENR |= (0x1 << 1); //Enable the GPIO B


    GPIOB->MODER &= ~(0x3 << 10); // Resets the necessary pins
    GPIOB->MODER |= (0x1 << 10);  // Set as output
    GPIOB->OSPEEDR |= (0x3 << 10);
    int delay = 5;
    __uint8_t address = 0x10;
    __uint8_t data = 0x15;  
    Configurates_SPI(SX1276_SPI);
    // SPI_WriteRegister(address ,data);
    while(1) {
        // UART_l80_m39_ReadMessages();
        if (data > 0x50){data = 0;}
        SPI_ReadRegister(address, SX1276_SPI);
        delay_ms(delay);
        SPI_WriteRegister(address, data, SX1276_SPI);
        data ++;
    }
}

