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
    __uint8_t transmit_word[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9};
    size_t arr_size = sizeof(transmit_word) / sizeof(transmit_word[0]);
    float freq = 915e6;
    SX1276_SetFreq(SX1276_Obj, freq);
    SX1276_SetSF(SX1276_Obj, LoRa_SF_7);
    SX1276_SetBW(SX1276_Obj, LoRa_Bw_125);
    while(1){
        // SX1276_Transmit(SX1276_Obj, transmit_word, arr_size);
    }
}

