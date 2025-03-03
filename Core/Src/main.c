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
    // UART_l80_m39_set_registers(16000000,9600);
    
    while(1) {
        // UART_Read(UART_L80, STARTING_PACKET_SIGN, ENDING_PACKET_SIGN, NMEA_MESSAGE_SIZE);
        char* message = UART_Read(UART_L80, STARTING_PACKET_SIGN, ENDING_PACKET_SIGN);
        GPS_NMEA_MessageNavigator(message);
    }
}

