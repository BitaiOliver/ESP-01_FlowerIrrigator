#include <TaskMgr.h>
#include <DIO.h>
#include <WiFiMgr.h>
#include <BlynkClient.h>


#include "TaskMgr_Priv.h"
#include "CompilerSwitch.h"

/* Global shared variables */
uint8 TaskMgr_InRunPrintCounter = 0U;
uint8 TaskMgr_OneTimeCounter = 1U;
String TaskMgr_SerialPrint = "";



void TaskMgr_Init(void)
{
#ifdef SERIAL_PRINT_TASKMGR
  TaskMgr_SerialPrint = "TaskMgr: Init Start....";
  Serial.print(TaskMgr_SerialPrint);
#endif

    /// OS ///
    /* Initialize timer handlers flag */
    Rte_IRead_TaskMgr_Handler_Flags = 0U;
    /* Call Rte_Init() */
    Rte_Init();
    //------//

    /// DIO ///
    DIO_Init();
    //-------//

    /// WifiMgr ///
    WiFiMgr_Init();
    //----------//

    /* Blynk init lasts much time so keep it in the last position. */
    /// Blynk ///
    BlynkClient_Init();
    //---------//



#ifdef SERIAL_PRINT_TASKMGR
  TaskMgr_SerialPrint = "TaskMgr: ...Stop.";
  Serial.println(TaskMgr_SerialPrint);
#endif

}

void Handle_500ms_Task(void)
{
    /* do nothing */
}
void Handle_1s_Task(void)
{
    DIO_Main();
    WiFiMgr_Main();

    BlynkClient_Main();     /* Has to be after thermo in order to has its inputs */

    /* Print function for debugging */
    TaskMgr_InRunPrint();
}
void Handle_5s_Task(void)
{
    /* do nothing */
}
void Handle_10s_Task(void)
{
    /* do nothing */
}
void Handle_30s_Task(void)
{  
    /* do nothing */
}
void Handle_1m_Task(void)
{
    /* do nothing */
    Rte_IWrite_TaskMgr_BlynkClient_ActionFlags |= (1 << 1U);
}

void TaskMgr_Main(void)
{
    if (0U < TaskMgr_OneTimeCounter)
    {
        TaskMgr_OneTimeCounter = 0U;
#ifdef SERIAL_PRINT_TASKMGR
        TaskMgr_SerialPrint = "TaskMgr: Loop Start.";
        Serial.println(TaskMgr_SerialPrint);
#endif
    }
    else
    {
        /* do nothing */
    }

    /* The order of the tasks are decreasing because rearly executed tasks set flags 
        for often executed tasks */
    if(FALSE != (Rte_IRead_TaskMgr_Handler_Flags & (1 << TIMER_1M_ID)))
    {
        /* Reset flag */
        Rte_IRead_TaskMgr_Handler_Flags &= ~(1 << TIMER_1M_ID);
        /* Call handler */
        Handle_1m_Task();
    }
    else
    {
        /* code */
    }
    if(FALSE != (Rte_IRead_TaskMgr_Handler_Flags & (1 << TIMER_30S_ID)))
    {
        /* Reset flag */
        Rte_IRead_TaskMgr_Handler_Flags &= ~(1 << TIMER_30S_ID);
        /* Call handler */
        Handle_30s_Task();
    }
    else
    {
        /* code */
    }
    if(FALSE != (Rte_IRead_TaskMgr_Handler_Flags & (1 << TIMER_10S_ID)))
    {
        /* Reset flag */
        Rte_IRead_TaskMgr_Handler_Flags &= ~(1 << TIMER_10S_ID);
        /* Call handler */
        Handle_10s_Task();
    }
    else
    {
        /* code */
    }
    if(FALSE != (Rte_IRead_TaskMgr_Handler_Flags & (1 << TIMER_5S_ID)))
    {
        /* Reset flag */
        Rte_IRead_TaskMgr_Handler_Flags &= ~(1 << TIMER_5S_ID);
        /* Call handler */
        Handle_5s_Task();
    }
    else
    {
        /* code */
    }
    if(FALSE != (Rte_IRead_TaskMgr_Handler_Flags & (1 << TIMER_1S_ID)))
    {
        /* Reset flag */
        Rte_IRead_TaskMgr_Handler_Flags &= ~(1 << TIMER_1S_ID);
        /* Call handler */
        Handle_1s_Task();
    }
    else
    {
        /* code */
    }
    if(FALSE != (Rte_IRead_TaskMgr_Handler_Flags & (1 << TIMER_500MS_ID)))
    {
        /* Reset flag */
        Rte_IRead_TaskMgr_Handler_Flags &= ~(1 << TIMER_500MS_ID);
        /* Call handler */
        Handle_500ms_Task();
    }
    else
    {
        /* code */
    }
}

void TaskMgr_InRunPrint(void)
{
#ifdef SERIAL_PRINT_TASKMGR
    switch (TaskMgr_InRunPrintCounter)
    {
        case 0:
        {
            TaskMgr_InRunPrintCounter = 1U;
            TaskMgr_SerialPrint = "TaskMgr: Running 1s.";
            Serial.println(TaskMgr_SerialPrint);
            break;
        }
        case 1:
        {
            TaskMgr_InRunPrintCounter = 2U;
            TaskMgr_SerialPrint = "TaskMgr: Run:  W: " + String(Rte_IRead_TaskMgr_WifiStatus) + " B: " + String(Rte_IRead_TaskMgr_ServerConnStatus);
            Serial.println(TaskMgr_SerialPrint);
            break;
        }
        case 2:
        {
            TaskMgr_InRunPrintCounter = 3U;
            TaskMgr_SerialPrint = "TaskMgr: Run:  W: " + String(Rte_IRead_TaskMgr_WifiStatus) + " B: " + String(Rte_IRead_TaskMgr_ServerConnStatus);
            Serial.println(TaskMgr_SerialPrint);
            break;
        }
        case 3:
        {
            TaskMgr_InRunPrintCounter = 1U;
            TaskMgr_SerialPrint = "TaskMgr: Run:  W: " + String(Rte_IRead_TaskMgr_WifiStatus) + " B: " + String(Rte_IRead_TaskMgr_ServerConnStatus);
            Serial.println(TaskMgr_SerialPrint);
            break;
        }
        default:
            break;
    }
#endif
}

