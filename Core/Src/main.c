#define STM32L0xx
#define CPU_FREQ 16000000
#include "stm32l072xx.h"
#include "main.h"
#include "rcc.h"
#include "stdio.h"
#include "uart.h"

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
    int delay = 3;
    while(1) {
        UART_l80_m39_ReadMessages();
        // GPIOB->ODR |= (0x1 << 5); // Outputs 1 through the PB5
        // delay_ms(delay);
        // UART_debug_sendMessage("Hello world!\r\n");
        // 
        // GPIOB->ODR &= ~(0x1 << 5); // Outputs 1 through the PB5 
        // delay_ms(delay);
    }
}

