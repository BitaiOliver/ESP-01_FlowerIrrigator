/**************** Includes ************/
#include <Arduino.h>
#include <Rte_Types.h>

#include "CompilerSwitch.h"

/**************** Defines ************/
#define RTE_DELAY_MS_FACTOR         16000U

/**************** Varables ************/
/// OS ///
uint8 Rte_TaskMgr_Handler_Flags;
//------//

/// WiFiMgr ///
uint8 Rte_WiFiMgr_WiFiStatus;
//----------//

/// Blynk ///
uint8 Rte_BlynkClient_ActionFlags;
uint8 Rte_BlynkClient_ServerConnStatus;
//---------------//


/**************** Functions ************/
void Rte_Init(void)
{
    /// OS ///
    Rte_TaskMgr_Handler_Flags = 0U;
    //------//
    
    /// WiFiMgr ///
    Rte_WiFiMgr_WiFiStatus = WIFI_STATUS_INIT;
    //-----------//

    /// Temperature ///
    Rte_BlynkClient_ActionFlags = 0U;
    //---------------//


}

void Rte_DelayMs(unsigned int d)
{
    unsigned int i;
    d = d * RTE_DELAY_MS_FACTOR;
    for (i = 0; i < d; i++)  // loop time is 5 machine cycles: 31.25ns @ 160MHz, 62.5ns @ 80MHz
    {
        asm("nop"); // minimum element to keep GCC from optimizing this function out.
    }

}