#ifndef __UART_H
#define __UART_H

#include "stm32l072xx.h"

typedef struct UART_Configuration {
    int baud_rate; // bps
    int clock_rate; // system clock rate

};

void UART_set_registers(int clock_rate, int baud_rate);
void UART_sendMessage(char message[]);

#endif