#include <RelayMgr.h>
#include "RelayMgr_Priv.h"

/* Global Variables */

RelayMgr_Data_Type RelayMgr_Data;

uint8 RelayMgr_OneTimeCounter = 1U;
String RelayMgr_SerialPrint = "";


/* Functions */
/********************************************************
* RelayMgr Init function. 
********************************************************/
void RelayMgr_Init(void)
{
#ifdef SERIAL_PRINT_RELAYMGR
    RelayMgr_SerialPrint = "RelayMgr: Init Start...";
    Serial.print(RelayMgr_SerialPrint);
#endif

    RelayMgr_Data.State = RELAYMGR_STATE_INIT;

#ifdef SERIAL_PRINT_RELAYMGR
    RelayMgr_SerialPrint = "  ...Stop.";
    Serial.println(RelayMgr_SerialPrint);
#endif

}

/********************************************************
* RelayMgr Main function. 
********************************************************/
void RelayMgr_Main(void)
{
    if (0U < RelayMgr_OneTimeCounter)
    {
        RelayMgr_OneTimeCounter = 0U;
#ifdef SERIAL_PRINT_RELAYMGR
        RelayMgr_SerialPrint = "RelayMgr: Loop Start.";
        Serial.println(RelayMgr_SerialPrint);
#endif
    }
    else
    {
        /* do nothing */
    }

    switch (RelayMgr_Data.State)
    {
        case RELAYMGR_STATE_INIT:
        {
            RelayMgr_Data.State = RELAYMGR_STATE_RUN;
            break;
        }
        case RELAYMGR_STATE_RUN:
        {
            /* Do nothing */
            break;
        }        
        default:
            break;
    }

}
