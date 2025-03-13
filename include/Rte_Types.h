#ifndef RTE_TYPES_H
#define RTE_TYPES_H 1
/**************** Includes ************/
#include <Arduino.h>

#include "CompilerSwitch.h"


#define RTE_TCPSERVER_SYNC_FLAG_THERMO              0U
#define RTE_TCPSERVER_SYNC_FLAG_BLYNK               1U

/**************** Data Types ************/
typedef struct Rte_Temperature_Reading_Type_Tag
{
    float      Data;
    uint8       Qf; 
}Rte_Temperature_Reading_Type;

/**************** Varables ************/

/**************** Functions ************/
void Rte_Init(void);
void Rte_DelayMs(unsigned int d);


#endif