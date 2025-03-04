#ifndef __SPI_H
#define __SPI_H
#include <stdio.h>
#include "stm32l072xx.h"

#define WriteConst                 ((__uint8_t)0x80)
#define ReadConst                  ((__uint8_t)0x7F)


/**
 * Choose the Right SPI interface, 
 * in our STM32 it's either SPI1 or SPI2. (There's is no more)
 */
typedef enum SPI_NumberTag : __uint8_t {
    SPI_1   = 0x0, 
    SPI_2   = 0x1  

}SPI_Number;

/**
 * Internal slave select - this bit has only effect if ssm bit is set
 * the value of this bit is forced onto the nss pin and the io value of the
 * NSS pin is ignored 
 *
 */
typedef enum SPI_SSI_Tag : __uint8_t {
    SSI_0   = 0x0, 
    SSI_1   = 0x1  

}SPI_SSI;


/**
 * Choose the Right SPI interface, 
 * in our STM32 it's either SPI1 or SPI2. (There's is no more)
 */
typedef enum SPI_SSM_Tag : __uint8_t {
    SSM_0   = 0x0,
    SSM_1   = 0x1  

}SPI_SSM;


/**
 * This configuration sets the clock of the SPI
 * for example -> FPCLK_2 sets the SPI clock = FPCLK / 2 
 */


typedef enum baudRateTag : __uint8_t {
    FPCLK_2       = 0x0,
    FPCLK_4       = 0x1,
    FPCLK_8       = 0x2,
    FPCLK_16      = 0x3,
    FPCLK_32      = 0x4,
    FPCLK_64      = 0x5,
    FPCLK_128     = 0x6,
    FPCLK_256     = 0x7

}SPI_baudRate;

/**
 * Sets the data size of one frame of SPI
 * either 8 bits or 16.
 */
typedef enum SPI_DataFrameFormatTag : __uint8_t {
    dataFrame_8bit   = 0x0,
    dataFrame_16bit  = 0x1

}SPI_DataFrameFormat;


/**
 * Sets the Clock Phase
 * when 0, the first clock transition is the first data capture edge
 * when 1, the second clock transition is the first data capture edge
 */
typedef enum SPI_CPHATag : __uint8_t {
    CPHA_0  = 0x0,
    CPHA_1  = 0x1

}SPI_CPHA;

/**
 * Sets the Clock polarity
 * when sets to 0, the clk reset to 0 when idle
 * when sets to 1, the clk sets to 1 when idle
 */
typedef enum SPI_CPOLtag : __uint8_t {
    CPOL_0  = 0x0,
    CPOL_1  = 0x1

}SPI_CPOL;

/**
 * Sets the MCU to be SPI Master
 */
typedef enum SPI_MasterTag : __uint8_t {
    SPI_SlaveSel   = 0x0,
    SPI_MasterSel  = 0x1

}SPI_Master;

typedef struct SPI_Object {
    GPIO_Object          MOSI;
    GPIO_Object          MISO;
    GPIO_Object          NSS;
    GPIO_Object          SCLK;
    SPI_TypeDef          *SPI_Struct;
    SPI_Number           SPIx;
    SPI_Master           MasterSel;
    SPI_DataFrameFormat  DFF;
    SPI_baudRate         baudRate;
    SPI_CPHA             CPHA;
    SPI_CPOL             CPOL;
    SPI_SSM              SSM;
    SPI_SSI              SSI;

}SPI_Object;

static const SPI_Object SPI_SX1276 = {
    .MOSI           = SPI_MOSI_SX1276,
    .MISO           = SPI_MISO_SX1276,
    .NSS            = SPI_NSS_SX1276,
    .SCLK           = SPI_SCLK_SX1276,
    .SPI_Struct     = SPI1,
    .SPIx           = SPI_1,
    .MasterSel      = SPI_MasterSel,
    .DFF            = dataFrame_8bit,
    .baudRate       = FPCLK_16,
    .CPHA           = CPHA_0,
    .CPOL           = CPOL_0,
    .SSM            = SSM_1,
    .SSI            = SSI_1

};


void      SPI_SetRegisters (SPI_Object Obj);
__uint8_t SPI_ReadRegister (__uint8_t address, SPI_Object Obj);
void      SPI_WriteRegister(__uint8_t address, __uint8_t data, SPI_Object Obj);

#endif