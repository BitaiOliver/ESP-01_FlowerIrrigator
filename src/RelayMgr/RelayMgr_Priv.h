#ifndef RELAYMGR_PRIV_H
#define RELAYMGR_PRIV_H 1
/**************** Includes ************/
#include <Arduino.h>
#include <Rte_Types.h>
#include "CompilerSwitch.h"


/**************** Defines ************/
#define RELAYMGR_STATE_INIT                      1U
#define RELAYMGR_STATE_RUN                       2U

/**************** Varables ************/
typedef struct RelayMgr_Data_Type_Tag
{
    uint8       State; 
}RelayMgr_Data_Type;

/// TCP ///
//------//

/// Temperature ///
extern Rte_Temperature_Reading_Type Rte_Temperature_ReadedTemp;
#define Rte_IRead_Temperature_ReadedTemperature    Rte_Temperature_ReadedTemp
//---------------//

/**************** Functions ************/

#endif