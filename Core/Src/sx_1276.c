#include <stdio.h>
#include "board_config.h"
#include "sx_1276.h"
#include "gpio.h"
#include "stm32l072xx.h"
#include "spi.h"
#include "uart.h"

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

void SX1276_SetTX(){
    /**
     * Sets the internal registers to change to transmit mode.
     * after that, the device is ready to transmit 
     */

}

void SX1276_Transmit(){
    /**
     *  Sends a byte to the internal FIFO of the sx1276 to be transmitted. 
     * */    

}



float SX1276_GetFreq(){
    /**
     * @brief Gets the RF Carrier Frequncey of the LORA Transceiver 
     * and return float format that represent the frequnecy in Hz. 
     */

}