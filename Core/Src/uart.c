#include "stm32l072xx.h"
#include <string.h>

void UART_set_registers(int clock_rate, int baud_rate){
    /*
    This Function sets the GPIO PA2 and PA3 for USART communication 
    PA9 - TX
    PA10 - RX
    it configurates the setting for both USART1 and for the specific GPIO.

    ******* Explanation at everyline *********
    
    */
    
    /*
    1. Enable the GPIO clock if its disabled
    2. Selected the alternate function AF4 -> 0100 for PA9 and PA10 (TX / RX)
    3. Configurate the Pins for PA9 and PA10 
    4. Configurate the USART1 settings 
    5. enable the USART1 register (UE)
    
    */
    RCC->APB2ENR |= (0x1 << 14); // Enable the USART1 Clock
    if((RCC->IOPENR >> 0) & 0x1){}
    else {
        RCC->IOPENR |= (0x1 << 0); // Enable the Clock of GPIO A
    }
    
    GPIOA->AFR[1] |= (0x4 << 4); // Select PA9 for USART TX (AFSEL) 
    GPIOA->AFR[1] |= (0x4 << 8); // Select PA10 for USART RX (AFSEL)
    
    GPIOA->MODER &= ~(0x3 << 18); // Clear PA9 mode
    GPIOA->MODER &= ~(0x3 << 20); // Clear PA10 mode
    GPIOA->MODER |= (0x2 << 18); // Select PA9 for Altenrate function
    GPIOA->MODER |= (0x2 << 20); // Select PA10 for Altenrate function

    GPIOA->PUPDR |= (0x1 << 18); // Select Pull-up for PA9
    GPIOA->PUPDR |= (0x1 << 20); // Select pull-up for PA10

    GPIOA->OTYPER &= ~(0x1 << 9); // Resets to push-pull mode (output type) for PA9 (TX)

    GPIOA->OSPEEDR |= (0x2 << 18); // Select Output speed of High speed for PA9
    GPIOA->OSPEEDR |= (0x2 << 20); // Select Output speed of High speed for PA10

    //Enables the UART Clock
    USART1->CR1 &= ~(0x1 << 0); // Disable the USART
    RCC->CCIPR |= (0x1 << 0); // USART1 Clock source from System Clock
    // Sets the Baud Rate

    // If OVER8 is equal 1 -> oversampling by 8
    int USART_DIV;
    if ((USART1->CR1 >> 15) & 0x1){
        USART_DIV = (2 * clock_rate) / baud_rate;
        USART1->BRR &= ~(0xFFFF << 0); // Clear the USARTDIV
        USART1->BRR |= (USART_DIV << 0); // set the baud rate to 38400
    } 
    // if OVER8 is equal 0 -> oversampling by 16 
    else {
        USART_DIV = clock_rate / baud_rate;
        USART1->BRR &= ~(0xFFFF << 0); // Clear the USARTDIV
        USART1->BRR |= (USART_DIV << 0); // set the baud rate to 38400

    }

    USART1->CR1 |= (0x1 << 3); // Enable the Transmission
    USART1->CR1 |= (0x1 << 0); // Enable the USART
}

void UART_sendMessage(char message[]){
    int size = strlen(message);
    for (int i = 0; i < size; i++) {
        while(!((USART1->ISR >> 7) & 0x1));
            USART1->TDR = message[i];
            }
    // Wait for TC to be 1, indicates that the transmittion has completed
    while(!((USART1->ISR >> 6) & 0x1));
    // USART1->CR1 &= ~(0x1 << 3); // Disable the Transmission

}
