#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32l072xx.h"
#include "uart.h"
#include "l80_m39.h"

void UART_debug_set_registers(int clock_rate, int baud_rate){
    /*
    This Function sets the GPIO PA2 and PA3 for USART communication with the computer for debugging and logging functions 
    GPIOA -> PA2 -> TX
    GPIOA -> PA3 -> RX
    it configurates the setting for both USART2 and for GPIOA (PA2, PA3).
    ******* Explanation at everyline *********
    
    */
    
    /*
    1. Enable the clock of USART 
    1. Enable the GPIO clock
    2. Selected the alternate function AF4 -> 0100 for PA2 and PA3 (TX / RX)
    3. Configurate the GPIO settings 
    4. Configurate the USART settings 
    5. enable the USART register and Enable Transmittion (UE | TE), receievr isn't enable because the computer doesnt send back any data to the MCU. 
    
    */
    RCC->APB1ENR |= (0x1 << 17); // Enable the USART2 Clock
    RCC->IOPENR |= (0x1 << 0); // Enable the Clock of GPIO A
    
    
    GPIOA->MODER &= ~(0x3 << 4); // Clear PA2 mode
    GPIOA->MODER &= ~(0x3 << 6); // Clear PA3 mode
    GPIOA->MODER |= (0x2 << 4); // Select PA2 for Altenrate function
    GPIOA->MODER |= (0x2 << 6); // Select PA3 for Altenrate function
    
    GPIOA->AFR[0] |= (0x4 << 8); // Select PA2 for USART TX (AFSEL) 
    GPIOA->AFR[0] |= (0x4 << 12); // Select PA3 for USART RX (AFSEL)

    GPIOA->PUPDR |= (0x1 << 4); // Select Pull-up for PA2
    GPIOA->PUPDR |= (0x1 << 6); // Select pull-up for PA3

    GPIOA->OTYPER &= ~(0x1 << 2); // Resets to push-pull mode (output type) for PA9 (TX)

    GPIOA->OSPEEDR |= (0x2 << 4); // Select Output speed of High speed for PA9
    GPIOA->OSPEEDR |= (0x2 << 6); // Select Output speed of High speed for PA10

    //Enables the UART Clock
    USART2->CR1 &= ~(0x1 << 0); // Disable the USART
    RCC->CCIPR |= (0x1 << 2); // USART2 Clock source from System Clock
    // Sets the Baud Rate

    // If OVER8 is equal 1 -> oversampling by 8
    int USART_DIV;
    if ((USART2->CR1 >> 15) & 0x1){
        USART_DIV = (2 * clock_rate) / baud_rate;
        USART2->BRR &= ~(0xFFFF << 0); // Clear the USARTDIV
        USART2->BRR |= (USART_DIV << 0); // Set the desired baud rate
    } 
    // if OVER8 is equal 0 -> oversampling by 16 
    else {
        USART_DIV = clock_rate / baud_rate;
        USART2->BRR &= ~(0xFFFF << 0); // Clear the USARTDIV
        USART2->BRR |= (USART_DIV << 0); // Set the desired baud rate

    }

    USART2->CR1 |= (0x1 << 3); // Enable the Transmission
    USART2->CR1 |= (0x1 << 0); // Enable the USART
}

void UART_debug_sendMessage(char message[]){
    uint16_t size = strlen(message);
    for (int i = 0; i < size; i++){
        while(!((USART2->ISR >> 7) & 0x1));
        USART2->TDR = message[i];
    }
    
    // Wait for TC to be 1, indicates that the transmittion has completed
    while(!((USART2->ISR >> 6) & 0x1));

    // USART1->CR1 &= ~(0x1 << 3); // Disable the Transmission
}

void UART_l80_m39_set_registers(int clock_rate, int baud_rate){

    /*
    This Function sets registers of GPIO PA9 and PA10 and USART1 communication in order to comminucate with the IC l80-m39, a gps receiver. 
    
    GPIOA -> PA9  -> TX
    GPIOA -> PA10 -> RX
    it configurates the setting for both USART1 and for GPIOA (PA9, P10).
    ******* Explanation at everyline *********
    
    */
    
    /*
    1. Enable the clock of USART 
    1. Enable the GPIO clock
    2. Selected the alternate function AF4 -> 0100 for PA2 and PA3 (TX / RX)
    3. Configurate the GPIO settings 
    4. Configurate the USART settings 
    5. enable the USART register and Enable Transmittion (UE | TE), receievr isn't enable because the computer doesnt send back any data to the MCU. 
    
    */
    uint8_t GPIOA_TX = 9; 
    uint8_t GPIOA_RX = 10; 
    RCC->APB2ENR |= (0x1 << 14); // Enable the USART2 Clock
    RCC->IOPENR |= (0x1 << 0); // Enable the Clock of GPIO A
    
    
    GPIOA->MODER &= ~(0x3 << (GPIOA_TX * 2)); // Clear PA9 mode
    GPIOA->MODER &= ~(0x3 << (GPIOA_RX * 2)); // Clear PA10 mode
    GPIOA->MODER |= (0x2 << (GPIOA_TX * 2)); // Select PA9 for Altenrate function
    GPIOA->MODER |= (0x2 << (GPIOA_RX * 2)); // Select PA10 for Altenrate function
    // If Pins are 0-7 -> AFR[0], else if 8-15 -> AFR[1]

    GPIOA->AFR[1] |= (0x4 << (GPIOA_TX - 8)*4); // Select PA9 for USART TX (AFSEL) 
    GPIOA->AFR[1] |= (0x4 << (GPIOA_RX - 8)*4); // Select PA10 for USART RX (AFSEL)

    GPIOA->PUPDR |= (0x1 << (GPIOA_TX * 2)); // Select Pull-up for PA9
    GPIOA->PUPDR |= (0x1 << (GPIOA_RX * 2)); // Select pull-up for PA10

    GPIOA->OTYPER &= ~(0x1 << GPIOA_TX); // Resets to push-pull mode (output type) for PA9 (TX)

    GPIOA->OSPEEDR |= (0x2 << (GPIOA_TX * 2)); // Select Output speed of High speed for PA9
    GPIOA->OSPEEDR |= (0x2 << (GPIOA_RX * 2)); // Select Output speed of High speed for PA10

    //Enables the UART Clock
    USART1->CR1 &= ~(0x1 << 0); // Disable the USART
    RCC->CCIPR |= (0x1 << 0); // USART1 Clock source from System Clock

    // Sets the Baud Rate
    // If OVER8 is equal 1 -> oversampling by 8
    int USART_DIV;
    if ((USART1->CR1 >> 15) & 0x1){
        USART_DIV = (2 * clock_rate) / baud_rate;
        USART1->BRR &= ~(0xFFFF << 0); // Clear the USARTDIV
        USART1->BRR |= (USART_DIV << 0); // Set the desired baud rate
    } 
    // if OVER8 is equal 0 -> oversampling by 16 
    else {
        USART_DIV = clock_rate / baud_rate;
        USART1->BRR &= ~(0xFFFF << 0); // Clear the USARTDIV
        USART1->BRR |= (USART_DIV << 0); // Set the desired baud rate

    }
    USART1->CR3 |= (0x1 << 12); // Enable Overrun -> may cause losing data but in this situation data can be lost
    USART1->CR1 |= (0x1 << 2); // Enable the Reception
    USART1->CR1 |= (0x1 << 0); // Enable the USART1


}

void UART_l80_m39_ReadMessages(){
/*
This function reads the messages of the NMEA GPS Sensor. 
Reading occur only when the register RXNE is set, if its clear, wait is needed until the 
buffer filled up again.
There is a thing that called overrun error, which occured when a character is received when RXNE has not been reset.
Data cannot be transferred from the shift register to the RDR register until the RXNE is clear.nmea_message
When overrun error occurs 
1. ORE bit is set
2. ORE bit is reset by setting the ORECF bit in the ICR Register 

*/
    static char nmea_message[NMEA_MESSAGE_SIZE];
    memset(nmea_message, 0, NMEA_MESSAGE_SIZE);
    uint8_t start = 0;
    uint8_t end = 0;
    uint8_t index = 0;
    while(!end){
        while(!((USART1->ISR >> 5) & 0x1));
        uint32_t l80_log = USART1->RDR;
        // Waiting for $ that represent the starting of the communication
        if(!start){
            // Check if there is dollar sign
            if (l80_log == Starting_Packet){ 
                nmea_message[index] = (char)(l80_log & 0xFF);
                start = 1;
                index++;
            }
        }
        else{

            if(l80_log == Ending_packet){
                nmea_message[index] = '\r';
                nmea_message[index+1] = '\n';
                nmea_message[index+2] = '\0';
                end = 1;
            }
            else{
                nmea_message[index] = (char)(l80_log & 0xFF);
                index++;
            }

        }
    }
    GPS_NMEA_MessageParser(nmea_message);
}