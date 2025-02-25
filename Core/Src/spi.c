#include <stdio.h>
#include "stm32l072xx.h"
#include "spi.h"
#include "uart.h"
#include "sx_1276.h"

void SetRegisters_SPI1(){
    /*
    This function sets the registers for SPI1 communication
    for half-duplex.
    */
    
    // Enable Clock for SPI1, GPIOA and GPIOB
    RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN); // Enable the SPI1 Clock
    RCC->IOPENR |= (RCC_IOPENR_GPIOAEN); // Enable the Clock of GPIO A
    RCC->IOPENR |= (RCC_IOPENR_GPIOBEN); // Enable the Clock of GPIO B
    
    // GPIO CONFIGURATION 
    
    GPIOA->MODER |= (0x1 << GPIOA_TCXO_POWER); // Select PA12 for output mode
    GPIOA->MODER |= (0x2 << GPIOA_MISO_PIN); // Select PA6 for Altenrate function
    GPIOA->MODER |= (0x2 << GPIOA_MOSI_PIN); // Select PA7 for Altenrate function
    GPIOA->MODER |= (0x1 << GPIOA_NSS_PIN); // Select PA15 for output mode
    GPIOB->MODER |= (0x2 << GPIOB_SCLK_PIN); // Select PB3 for Altenrate function
    
    GPIOA->AFR[1] |= (0x0 << GPIOA_TCXO_POWER * 4); // Select PA12 for normal GPIO -> Needs to change Here!
    GPIOA->AFR[0] |= (0x0 << GPIOA_MISO_PIN * 4); // Select PA6 for MISO (AFSEL 0)
    GPIOA->AFR[0] |= (0x0 << GPIOA_MOSI_PIN * 4); // Select PA7 for MOSI (AFSEL 0) 
    GPIOA->AFR[1] |= (0x0 << (GPIOA_NSS_PIN - 8) * 4); // Select PA15 for NSS (AFSEL 0)
    GPIOB->AFR[0] |= (0x0 << GPIOB_SCLK_PIN * 4); // Select PB3 for PSCLK (AFSEL 0)

    GPIOA->PUPDR &= ~(0x3 << GPIOA_TCXO_POWER); // Resets value for PA12 
    GPIOA->PUPDR |= (0x1 << GPIOA_TCXO_POWER); // Select pull-up for PA12
    GPIOA->PUPDR |= (0x0 << GPIOA_MISO_PIN * 2); // Select Pull-down for PA6
    GPIOA->PUPDR |= (0x0 << GPIOA_MOSI_PIN * 2); // Select Pull-down for PA7
    GPIOA->PUPDR &= ~(0x3 << GPIOA_NSS_PIN * 2); // Select no-pull for PA15
    GPIOB->PUPDR |= (0x0 << GPIOB_SCLK_PIN * 2); // Select pull-down for PB3


    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_12); // Select push-pull for PA12
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_6); // Select push-pull for PA6
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_7); // Select push-pull for PA7
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_15); // Select push-pull for PA15
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_3); // Select push-pull for PB3

    GPIOA->OSPEEDR |= (0x2 << GPIOA_MISO_PIN * 2); // Select Output speed of High speed for PA5
    GPIOA->OSPEEDR |= (0x2 << GPIOA_MOSI_PIN * 2); // Select Output speed of High speed for PA4
    GPIOA->OSPEEDR |= (0x2 << GPIOA_NSS_PIN * 2); // Select Output speed of High speed for PA6
    GPIOB->OSPEEDR |= (0x2 << GPIOB_SCLK_PIN * 2); // Select Output speed of High speed for PA7

    // SPI CONFIGURATION
    // SPI1->CR1 &= ~(SPI_CR1_SPE_Msk); // Disables SPI
    // SPI1->CR1 |= (SPI_CR1_BIDIMODE); // Enables Half-duplex mode 
    SPI1->CR1 &= ~(SPI_CR1_DFF | SPI_CR1_CPOL | SPI_CR1_CPHA); // Clears the data frame format to 0, make it 8-bit frame, and clock polarity and clock phase to 0.
    SPI1->CR1 |= (SPI_CR1_MSTR); // Sets the MCU to the master
    SPI1->I2SCFGR &= ~(SPI_I2SCFGR_I2SMOD); // SPI Mode is selected
    SPI1->CR1 |= (0x7 << SPI_CR1_BR_Pos); // Sets the SPI Baud rate to Fpclk / 256
    SPI1->CR2 |= (SPI_CR2_SSOE);
    SPI1->CR1 |= (SPI_CR1_SPE_Msk); // Enables SPI
}

void SPI_ReadRegister(char *data){
    /*
    This function reads a data from address sent.
    
    */

    // Needs to make NSS low when starting a write sequence
    char temp;
    while((SPI1->SR >> SPI_SR_BSY_Pos) & 0x1 == 0x1); // wait in a while loop until the busy flag is cleared by HW. 
    GPIOA->ODR &= ~(0x1 << GPIOA_NSS_PIN); // Driving NSS PIN LOW 
    while (*data){
        // wait in a while loop until transmit buffer is empty.
        if((SPI1->SR >> SPI_SR_TXE_Pos) & 0x1 == 0x1){ 
            SPI1->DR = *data; // Write char (8 bit) to the TX Buffer (8b-dataframe).
            data++; // Itirate the pointer to the next address for the next word.
        }
        while((SPI1->DR >> SPI_SR_RXNE_Pos) & 0x1 != 0x1); 
        temp = (SPI1->DR & 0xFF); 
        UART_printf("The Read value from SPI is: 0x%x\r\n", temp);
        GPIOA->ODR |= (0x1 << GPIOA_NSS_PIN); // Setting NSS PIN HIGH
        
    }
}
