#include <stdio.h>
#include "board_config.h"
#include "sx_1276.h"
#include "gpio.h"
#include "stm32l072xx.h"
#include "spi.h"
#include "uart.h"

static __uint8_t SX1276_FifoPtr = SX1276_FifoTxBaseAddr; 

void SX1276_Test(SX1276_Object Obj){
    SPI_WriteRegister(RegOpMode, ZeroByte, Obj.SPI_Obj);
    SPI_WriteRegister(RegOpMode, RegOpMode_Mode_Sleep, Obj.SPI_Obj);
    __uint8_t Mode    = SPI_ReadRegister(RegOpMode, Obj.SPI_Obj);
    UART_printf("Mode is: 0x%x \r\n", Mode);
    
    SPI_WriteRegister(RegOpMode, RegOpMode_LongRangeMode, Obj.SPI_Obj);
    SPI_WriteRegister(RegOpMode, RegOpMode_Mode_Stdby, Obj.SPI_Obj);
    
    Mode    = SPI_ReadRegister(RegOpMode, Obj.SPI_Obj);
    UART_printf("Mode is: 0x%x \r\n", Mode);
// 
    // __uint8_t FifoAddrPtr    = SPI_ReadRegister(RegFifoAddrPtr, Obj.SPI_Obj);
    // UART_printf("FifoAddrPtr = 0x%x\r\n", FifoAddrPtr);
    // 
    // __uint8_t FifoTxBaseAddr = SPI_ReadRegister(RegFifoAddrPtr, Obj.SPI_Obj);
    // UART_printf("FifoTxBaseAddr = 0x%x\r\n", FifoTxBaseAddr);
    // 
    // SPI_WriteRegister(RegFifo, 0x0A, Obj.SPI_Obj);
    // 
    // FifoAddrPtr    = SPI_ReadRegister(RegFifoAddrPtr, Obj.SPI_Obj);
    // UART_printf("FifoAddrPtr = 0x%x\r\n", FifoAddrPtr);
    // 
    // FifoTxBaseAddr = SPI_ReadRegister(RegFifoAddrPtr, Obj.SPI_Obj);
    // UART_printf("FifoTxBaseAddr = 0x%x\r\n", FifoTxBaseAddr);
    // 
    // SPI_WriteRegister(RegFifoAddrPtr, 0x0, Obj.SPI_Obj);
    // __uint8_t value_of_fifo = SPI_ReadRegister(RegFifo, Obj.SPI_Obj);
    // UART_printf("Value of FIFO is = 0x%x\r\n", value_of_fifo);
    // 

    UART_printf("-------------------------------------------------\r\n");

    
}

void SX1276_Init(SX1276_Object Obj){
    /** 
     * @brief Initializes the registers of the SX1276 IC,  
     */
     // Init All the GPIOS, DIOx, TCXOx and reset and RF switches
    GPIO_Init(Obj.TCXO);
    GPIO_Set(Obj.TCXO);
    SPI_SetRegisters(Obj.SPI_Obj);



}

void SX1276_SetFreq(SX1276_Object Obj, float freq){
    /**
     * @brief Sets the RF Carrier Frequncey of the LORA Transceiver
     * @param freq -> sets the RF carrier frequency of the LO of the SX1276
     */

    __uint8_t readValue = SPI_ReadRegister(RegOpMode ,Obj.SPI_Obj);  
    __uint8_t tempValue = readValue & ~(RegOpMode_Mode_Msk);
    SPI_WriteRegister(RegOpMode, tempValue, Obj.SPI_Obj);
    // Calculate the freq and divide it to lsb, msb, mid 
    int frf = (freq / FSTEP);
    __uint8_t msb = 0xFF & (frf >> 16);
    __uint8_t mid = 0xFF & (frf >> 8);
    __uint8_t lsb = 0xFF & frf;
    // Write the new frequnecy to the registers 
    SPI_WriteRegister(RegFrfMsb, msb, Obj.SPI_Obj);
    SPI_WriteRegister(RegFrfMid, mid, Obj.SPI_Obj);
    SPI_WriteRegister(RegFrfLsb, lsb, Obj.SPI_Obj);
    SPI_WriteRegister(RegOpMode, readValue, Obj.SPI_Obj);



}


void SX1276_Transmit(SX1276_Object Obj, __uint8_t word){
    /**
     *  Sends a byte to the internal FIFO of the sx1276 to be transmitted. 
     * */    
    if(SX1276_FifoPtr == SX1276_FifoTxMaxAddr){
        SX1276_FifoPtr = SX1276_FifoTxBaseAddr;
    }
     // Switch to stdby mode
    SPI_WriteRegister(RegOpMode, RegOpMode_Mode_Stdby, Obj.SPI_Obj);
    // Write to the pointer register, and then to the fifo.
    SPI_WriteRegister(RegFifoAddrPtr, SX1276_FifoPtr, Obj.SPI_Obj);
    SPI_WriteRegister(RegFifo, word, Obj.SPI_Obj);
    SPI_WriteRegister(RegOpMode, RegOpMode_Mode_TX, Obj.SPI_Obj);
    while(!((SPI_ReadRegister(RegIrqFlags, Obj.SPI_Obj) >> 3) & 0x1));
    SX1276_FifoPtr++;



}



// float SX1276_GetFreq(){
//     /**
//      * @brief Gets the RF Carrier Frequncey of the LORA Transceiver 
//      * and return float format that represent the frequnecy in Hz. 
//      */

// }