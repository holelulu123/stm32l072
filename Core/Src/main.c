#define STM32L0xx
#define CPU_FREQ 16000000
#include "stm32l072xx.h"
#include "gpio.h"
#include "rcc.h"
#include "board_config.h"
#include "main.h"
#include "uart.h"
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
    // SetClock(Clock_Configuration);
    struct UART_Configuration uart_config;
    uart_config.baud_rate = 9600;
    uart_config.clock_rate = 16000000;
    
    UART_debug_set_registers(uart_config.clock_rate, 
        uart_config.baud_rate);
        
    UART_l80_m39_set_registers(uart_config.clock_rate,
        uart_config.baud_rate);
            
    UART_printf("System Clock is : %f\r\n" ,SystemClock);
    UART_printf("PLL VCO is      : %f\r\n" ,PLLVCO);
    UART_printf("System Clock is : %x\r\n" ,((RCC->CFGR >> RCC_CFGR_PLLSRC_Pos) & 0x1));
    UART_printf("PLL ON is       : %x\r\n" ,((RCC->CR >> RCC_CR_PLLON_Pos) & 0x1));
    
    // int delay = 5;
    // __uint8_t address = 0x10;
    // __uint8_t data = 0x15;  
    // Configurates_SPI(SX1276_SPI);
    // SPI_WriteRegister(address ,data);
    GPIO_Init(GPIOB_5, GPIOB);
    
    while(1) {
        GPIO_Set(GPIOB_5, GPIOB);
        
        delay_ms(10);
        GPIO_Reset(GPIOB_5, GPIOB);
        delay_ms(10);
    }
}

