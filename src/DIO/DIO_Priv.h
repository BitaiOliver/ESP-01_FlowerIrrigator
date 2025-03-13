#ifndef DIO_PRIV_H
#define DIO_PRIV_H 1
/**************** Includes ************/
#include <Arduino.h>

#include "CompilerSwitch.h"


/**************** Defines ************/
#define DIO_STATE_INIT                      1U
#define DIO_STATE_RUN                       2U

#define DIO_GPIO_0                          0U
#define DIO_GPIO_2                          2U

/**************** Varables ************/
typedef struct DIO_Data_Type_Tag
{
    uint8       State; 
}DIO_Data_Type;

/// TCP ///
//------//

/// Blynk ///
//--------//

/**************** Functions ************/

#endif