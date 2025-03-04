#include <stdio.h>
#include "stm32l072xx.h"
#include "gpio.h"
#include "spi.h"

void SPI_SetRegisters(SPI_Object Obj){
    /**
     * @brief This functions Sets the registers of SPI,
     * Initilizes the communication by the configuration of Obj
     * @param SPI_Object is a struct that consists on all the SPI 
     * configuration and GPIOS for communication
     */
    switch (Obj.SPIx) {
        case 0:
            RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN);
            break;
        case 1:
            RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN);
            break;
    }
    GPIO_Init(Obj.MISO);
    GPIO_Init(Obj.MOSI);
    GPIO_Init(Obj.NSS);
    GPIO_Init(Obj.SCLK);
    
    GPIO_Set(Obj.NSS);
    // For now lets not enable TCXO and lets see the effect.
    switch (Obj.SSM) {
        case 0:
            Obj.SPI_Struct->CR1 &= ~(SPI_CR1_SSM);
            break;
        case 1:
            Obj.SPI_Struct->CR1 |=  (SPI_CR1_SSM);
            if (Obj.SSI){
                Obj.SPI_Struct->CR1 |=  (SPI_CR1_SSI);
            }
    }
    // Data Frame Format
    Obj.SPI_Struct->CR1 &= ~(SPI_CR1_DFF); 
    Obj.SPI_Struct->CR1 |=  (Obj.DFF << SPI_CR1_DFF_Pos); 
    
    // Clock Polarity
    Obj.SPI_Struct->CR1 &= ~(SPI_CR1_CPOL); 
    Obj.SPI_Struct->CR1 |=  (Obj.CPOL << SPI_CR1_CPOL_Pos); 
    
    // Clock Phase
    Obj.SPI_Struct->CR1 &= ~(SPI_CR1_CPHA); 
    Obj.SPI_Struct->CR1 |=  (Obj.CPHA << SPI_CR1_CPHA_Pos); 

    // Master Selection
    Obj.SPI_Struct->CR1 &= ~(SPI_CR1_MSTR);
    Obj.SPI_Struct->CR1 |=  (Obj.MasterSel << SPI_CR1_MSTR_Pos);    

    /** 
     *  SPI / I2S selection -> We make hard coded SPI Choosen
     * Because this function is only for settings register of SPI.
     * I2S Registers Configuration would be on a different function.
     */ 
    Obj.SPI_Struct->I2SCFGR &= ~(SPI_I2SCFGR_I2SMOD);
    
    // SPI Baud Rate Selection
    Obj.SPI_Struct->CR1 &= ~(SPI_CR1_BR_Msk);
    Obj.SPI_Struct->CR1 |=  (Obj.baudRate << SPI_CR1_BR_Pos);
    
    Obj.SPI_Struct->CR2 |=  (SPI_CR2_SSOE);
    Obj.SPI_Struct->CR1 |=  (SPI_CR1_SPE);
    
}

void SPI_WriteRegister(__uint8_t address, __uint8_t data, SPI_Object Obj){
    /*
    This function writes a data (8 bit) to a register
    */
    address |= WriteConst; // Adds 1 to the MSB of the address to represent a write operation
    __uint8_t word[2] = {address, data}; 
    __uint8_t temp;
    GPIO_Reset(Obj.NSS);
    for(int i = 0; i < sizeof(word); i++){
        while(!(Obj.SPI_Struct->SR & SPI_SR_TXE)); 
        Obj.SPI_Struct->DR = word[i];
        while(!(Obj.SPI_Struct->SR & SPI_SR_RXNE));
        temp = Obj.SPI_Struct->DR;
    } 
    GPIO_Set(Obj.NSS);
}

__uint8_t SPI_ReadRegister(__uint8_t address, SPI_Object Obj){
    /*
    This function reads a data from address sent.
    it gets address as an argument send a read requests 
    and gets an answer that represent the data of the register
    at the time.
    
    */
    __uint8_t temp;
    __uint8_t data[2] = {address & ReadConst, 0x0}; // Creates a data and dummy to let the NSS stays and Sclk to continue transfering clock
    GPIO_Reset(Obj.NSS);
    // Transmit operation
    for (int i = 0; i < sizeof(data); i++){
        Obj.SPI_Struct->DR = data[i]; // Write char (8 bit) to the TX Buffer (8b-dataframe).
        while(!(Obj.SPI_Struct->SR & SPI_SR_TXE)); 
        while(!(Obj.SPI_Struct->SR & SPI_SR_RXNE)); // wait in a while loop until the busy flag is cleared by HW. 
        temp = Obj.SPI_Struct->DR;
    }
    GPIO_Set(Obj.NSS);
    return temp;

}
