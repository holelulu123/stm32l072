#include <stdio.h>
#include "board_config.h"
#include "sx_1276.h"
#include "gpio.h"
#include "stm32l072xx.h"
#include "spi.h"
#include "uart.h"

static __uint8_t SX1276_FifoPtr = SX1276_FifoTxBaseAddr; 




void SX1276_Mode_Stdby(SX1276_Object Obj){
    /**
     * @brief Switch the SX1276 to Stdby mode.
     */
    __uint8_t mode = SPI_ReadRegister(RegOpMode, Obj.SPI_Obj);
    SPI_WriteRegister(RegOpMode, RegOpMode_LongRangeMode, Obj.SPI_Obj);
    SPI_WriteRegister(RegOpMode, RegOpMode_Mode_Stdby, Obj.SPI_Obj);


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

void SX1276_SetSF(SX1276_Object Obj, enum LoraSpreadingFactor SF){
    /**
     * Set Spreading Factor for tranmission, Check enum in SX1276.h for options.
     */
    
    SX1276_Mode_Stdby(Obj);
    __uint8_t byte = (SF << RegModemConfig2_SF_Pos); 
    SPI_WriteRegister(RegModemConfig2, byte, Obj.SPI_Obj);

}

void SX1276_SetBW(SX1276_Object Obj, enum LoraBw BW){
    /**
     * Sets Bandwidth of LoRa Communication, Check enum in SX1276.h for options.
     */

    SX1276_Mode_Stdby(Obj);
    __uint8_t byte = (BW << RegModemConfig1_Bw_Pos); 
    SPI_WriteRegister(RegModemConfig1, byte, Obj.SPI_Obj);
}

void SX1276_Transmit(SX1276_Object Obj, __uint8_t* transmit_word, size_t size){
    /**
     *  Sends a byte to the internal FIFO of the sx1276 to be transmitted. 
     * */    
    if(SX1276_FifoPtr == SX1276_FifoTxMaxAddr){
        SX1276_FifoPtr = SX1276_FifoTxBaseAddr;
    }
    
    // Switch to stdby mode and Check if it switched to stdby
    SX1276_Mode_Stdby(Obj);
    __uint8_t TxDone = 0;
    __uint8_t index = 0;
    while(index < size){
    // Write to the pointer register, and then to the fifo.
        SPI_WriteRegister(RegFifoAddrPtr, SX1276_FifoPtr, Obj.SPI_Obj);
        SPI_WriteRegister(RegFifo, transmit_word[index], Obj.SPI_Obj);
        SPI_WriteRegister(RegOpMode, RegOpMode_Mode_TX, Obj.SPI_Obj);
        TxDone = 0;
        while(!TxDone){
            TxDone = SPI_ReadRegister(RegIrqFlags, Obj.SPI_Obj);
            TxDone = (TxDone >> 3) & 0x1; 
        }
        SX1276_FifoPtr++;
        index++;
    }


}



// float SX1276_GetFreq(){
//     /**
//      * @brief Gets the RF Carrier Frequncey of the LORA Transceiver 
//      * and return float format that represent the frequnecy in Hz. 
//      */

// }