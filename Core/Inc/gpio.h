#ifndef __GPIO_H
#define __GPIO_H
#include <stdio.h>
#include "stm32l072xx.h"

/**
 * changes the mode of the GPIO Pin for either reception or 
 * transmission of data, or either analog. 
 */


typedef enum GPIOPinNumberTag : __uint8_t {
    GPIO_PIN_0      = 0x0,
    GPIO_PIN_1      = 0x1,
    GPIO_PIN_2      = 0x2,
    GPIO_PIN_3      = 0x3,
    GPIO_PIN_4      = 0x4,
    GPIO_PIN_5      = 0x5,
    GPIO_PIN_6      = 0x6,
    GPIO_PIN_7      = 0x7,
    GPIO_PIN_8      = 0x8,
    GPIO_PIN_9      = 0x9,
    GPIO_PIN_10     = 0xA,
    GPIO_PIN_11     = 0xB,
    GPIO_PIN_12     = 0xC,
    GPIO_PIN_13     = 0xD,
    GPIO_PIN_14     = 0xE,
    GPIO_PIN_15     = 0xF

}GPIOPinNumber;

typedef enum GPIOPinModesTag : __uint8_t {
    InputMode       = 0x0,
    OutputMode      = 0x1,
    AlternateMode   = 0x2,
    AnalogMode      = 0x3

}GPIOPinModes;

typedef enum GPIOPinTypeTag : __uint8_t {
    PushPull        = 0x0,
    OpenDrain       = 0x1

}GPIOPinType;

/**
 * GPIO Output speed.
 */
typedef enum GPIOPinOutputSpeed : __uint8_t {
    LowSpeed        = 0x0,
    MediumSpeed     = 0x1,
    HighSpeed       = 0x2,
    VeryHighSpeed   = 0x3

}GPIOPinOutputSpeed;

/**
 * 
 * GPIO Pullup-PullDown, GPIO can be pulled to a voltage high, low or none.
 * 
 */
typedef enum GPIOPinPUPRTag : __uint8_t {
    NoPull          = 0x0,    
    PullUp          = 0x1,    
    PullDown        = 0x2    

}GPIOPinPUPR;
/**
 * GPIO Alternate functions, GPIO functionality can be changed, respectfully to 
 * the datasheet 
 */ 
typedef enum GPIOAlternateFunctionTag : __uint8_t {
    AF0             = 0x0,
    AF1             = 0x1,
    AF2             = 0x2,
    AF3             = 0x3,
    AF4             = 0x4,
    AF5             = 0x5,
    AF6             = 0x6,
    AF7             = 0x7

}GPIOAlternateFunction; 

typedef enum GPIONameTag : __uint8_t {
    GPIO_A          = 0,
    GPIO_B          = 1,
    GPIO_C          = 2,
    GPIO_D          = 3,
    GPIO_E          = 4,
    GPIO_H          = 5

}GPIOName;


/**
 * GPIO Object declartions
 */
typedef struct GPIO_Object {
    GPIOPinNumber           PinNumber;
    GPIOName                Name;
    GPIOPinModes            Mode;
    GPIOPinOutputSpeed      Speed;
    GPIOPinPUPR             Pupr;
    GPIOPinType             Type;
    GPIOAlternateFunction   AF;  
    GPIO_TypeDef            *GPIOP;

}GPIO_Object;


static const GPIO_Object GPIOB_5 = {
    .PinNumber          = GPIO_PIN_5,
    .Name               = GPIO_B,
    .Mode               = OutputMode,
    .Speed              = MediumSpeed,
    .Pupr               = NoPull,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOB
};

/**
 * UART Connection to computer Debugging
 */

static const GPIO_Object TX_Debug = {
    .PinNumber          = GPIO_PIN_2,
    .Name               = GPIO_A,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF4,
    .GPIOP              = GPIOA
};

static const GPIO_Object RX_Debug = {
    .PinNumber          = GPIO_PIN_3,
    .Name               = GPIO_A,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF4,
    .GPIOP              = GPIOA
};

/**
 * UART Connections to L80-m39 IC
 */

static const GPIO_Object TX_L80 = {
    .PinNumber          = GPIO_PIN_9,
    .Name               = GPIO_A,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF4,
    .GPIOP              = GPIOA
};

static const GPIO_Object RX_L80 = {
    .PinNumber          = GPIO_PIN_10,
    .Name               = GPIO_A,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF4,
    .GPIOP              = GPIOA
};

/**
 * SX1276 GPIOs
 */
static const GPIO_Object SPI_MOSI_SX1276 = {
    .PinNumber          = GPIO_PIN_7,
    .Name               = GPIO_A,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullDown,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOA
};

static const GPIO_Object SPI_MISO_SX1276 = {
    .PinNumber          = GPIO_PIN_6,
    .Name               = GPIO_A,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullDown,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOA
};

static const GPIO_Object SPI_SCLK_SX1276 = {
    .PinNumber          = GPIO_PIN_3,
    .Name               = GPIO_B,
    .Mode               = AlternateMode,
    .Speed              = HighSpeed,
    .Pupr               = PullDown,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOB
};

static const GPIO_Object SPI_NSS_SX1276 = {
    .PinNumber          = GPIO_PIN_15,
    .Name               = GPIO_A,
    .Mode               = OutputMode,
    .Speed              = HighSpeed,
    .Pupr               = NoPull,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOA
};

static const GPIO_Object TCXO_SX1276 = {
    .PinNumber          = GPIO_PIN_12,
    .Name               = GPIO_A,
    .Mode               = OutputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOA
};

static const GPIO_Object DIO0_SX1276 = {
    .PinNumber          = GPIO_PIN_4,
    .Name               = GPIO_B,
    .Mode               = InputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOB
};

static const GPIO_Object DIO1_SX1276 = {
    .PinNumber          = GPIO_PIN_1,
    .Name               = GPIO_B,
    .Mode               = InputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOB
};

static const GPIO_Object DIO2_SX1276 = {
    .PinNumber          = GPIO_PIN_0,
    .Name               = GPIO_B,
    .Mode               = InputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOB
};

static const GPIO_Object DIO3_SX1276 = {
    .PinNumber          = GPIO_PIN_13,
    .Name               = GPIO_C,
    .Mode               = InputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOC
};

static const GPIO_Object DIO4_SX1276 = {
    .PinNumber          = GPIO_PIN_5,
    .Name               = GPIO_A,
    .Mode               = InputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOA
};

static const GPIO_Object DIO5_SX1276 = {
    .PinNumber          = GPIO_PIN_4,
    .Name               = GPIO_A,
    .Mode               = InputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOA
};

static const GPIO_Object RESET_SX1276 = {
    .PinNumber          = GPIO_PIN_0,
    .Name               = GPIO_C,
    .Mode               = OutputMode,
    .Speed              = MediumSpeed,
    .Pupr               = PullUp,
    .Type               = PushPull,
    .AF                 = AF0,
    .GPIOP              = GPIOC
};


/**
 * GPIOs Basic Functions
 */
void      GPIO_Init (GPIO_Object Obj);
void      GPIO_Set  (GPIO_Object Obj);
void      GPIO_Reset(GPIO_Object Obj);
__uint8_t GPIO_Read (GPIO_Object Obj);

#endif
