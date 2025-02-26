#ifndef __SPI_H
#define __SPI_H
#include <stdio.h>

// SPI GPIO configuration
#define GPIOA_MOSI_PIN              7
#define GPIOA_MISO_PIN              6 
#define GPIOA_SCLK_PIN              5
#define GPIOA_NSS_PIN               4

void Configurates_SPI1();
void SPI_ReadRegister(__uint8_t address);
void SPI_WriteRegister(__uint8_t address, __uint8_t data);

#endif