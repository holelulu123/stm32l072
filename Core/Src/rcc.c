#include "stm32l072xx.h"

void SetClock_HSI16(){
    /*
    Uses Internal-clock as the main clock.
    */

    RCC->CR &= ~(0x1 << 24); // Disable the PLL
    while(((RCC->CR >> 25) & 0b1) == 0b1); // Waits for the PLL to be clear
    
    // Control Registers
    RCC->CR |= (0x3 << 20); // RTC prescalar is set to 16, needs to learn more about the RTC clock and his purpose.
    RCC->CR &= ~(0x1 << 18); // Disable the bypass of the External clock (Using local Crystal Oscillator). 
    RCC->CR &= ~(0x1 << 8); // Disable the MSI Clock
    RCC->CR &= ~(0x1 << 16); // Disable the HSE Clock
    RCC->CR |= (0x1 << 0); // Enable the HSI16 Clock
    while(((RCC->CR >> 2) & 0b1) != 1); // wait for HSI16 clock to be stable and ready
    
    
    RCC->CFGR |= (0x1 << 0); // System clock switch - HSI16 Choosed
    while(((RCC->CFGR >> 2) & 0b11) != 0b01); // wait for the switch status to be locked on HSI16
    
    RCC->CFGR &= ~(0xF << 24); // MCO output disabled, no clock on MCO
}

void SetClock_HSI16_PLL(){
    /*
    Uses Internal-clock as the main clock with PLL stablization
    in this mode we enable HSI16 clock type and PLL, in the RCC section.
    */

    // Changing Voltage scaling range to 1.8V in order to reach VCO of 96MHz and then output clock 32MHz
    PWR->CR |= (0x1 << 12); 
    PWR->CR &= ~(0x1 << 11); 
    while((PWR->CR >> 11) & 0b11 != 0b01);
    
    
    RCC->CR &= ~(0x1 << 24); // Disable the PLL
    while(((RCC->CR >> 25) & 0b1) == 0b1); // Waits for the PLL to be clear
    
    //Switch to 1 wait - state 
    FLASH->ACR |= (0x1 << 0);

    // Control Registers
    RCC->CR |= (0x3 << 20); // RTC prescalar is set to 16, needs to learn more about the RTC clock and his purpose.
    RCC->CR &= ~(0x1 << 18); // Disable the bypass of the External clock (Using local Crystal Oscillator). 
    RCC->CR &= ~(0x1 << 8); // Disable the MSI Clock
    RCC->CR &= ~(0x1 << 16); // Disable the HSE Clock
    RCC->CR |= (0x1 << 0); // Enable the HSI16 Clock
    while(((RCC->CR >> 2) & 0b1) != 1); // wait for HSI16 clock to be stable and ready
    
    
    RCC->CFGR |= (0x1 << 0); // System clock switch - HSI16 Choosed
    while(((RCC->CFGR >> 2) & 0b11) != 0b01); // wait for the switch status to be locked on HSI16
    // Internal Clock sources calibration registers
    // TODO: To check what is the HSI Trim and calibration meaning
    // Clock configuration registers
    
    RCC->CFGR &= ~(0xF << 24); // MCO output disabled, no clock on MCO
    RCC->CFGR |= (0x1 << 18); // PLL multiplication factor by 4
    RCC->CFGR |= (0x1 << 22); // PLL Divider by 2
    RCC->CFGR &= ~(0x1 << 16); // PLL clock source
    
    // Enable the PLL
    RCC->CR |= (0x1 << 24);
    while(((RCC->CR >> 25) & 0b1) != 0b1); // Waits for the PLL to be Locked
    
    RCC->CFGR &= ~(0x3 << 0); // System clock data reset
    RCC->CFGR |= (0x3 << 0); // System clock switch - PLL Choosed
    while(((RCC->CFGR >> 2) & 0b11) != 0b11); // wait for the switch status to be locked on PLL
    

}