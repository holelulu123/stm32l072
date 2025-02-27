#ifndef __SPI_H
#define __SPI_H
#include <stdio.h>
#include "stm32l072xx.h"


void Configurates_SPI(SPI_TypeDef *SPI_interface);
__uint8_t SPI_ReadRegister(__uint8_t address, SPI_TypeDef *SPI_interface);
void SPI_WriteRegister(__uint8_t address, __uint8_t data, SPI_TypeDef *SPI_interface);

#endif