#include "CompilerSwitch.h"


#include <BlynkClient.h>
#include <DIO.h>
#include "BlynkClient_Priv.h"



BlynkClient_Data_Type BlynkClient_Data;


uint8 BlynkClient_OneTimeCounter = 1U;
String BlynkClient_SerialPrint = "";

/* this counter is decremented after startup */
uint8 BlynkClient_StartupCounter = 3U;

/* Functions */
/********************************************************
* BlynkClient Init function. 
********************************************************/
void BlynkClient_Init(void)
{
#ifdef SERIAL_PRINT_BLYNK
    BlynkClient_SerialPrint = "BlynkClient: Init Start...";
    Serial.print(BlynkClient_SerialPrint);
#endif

    BlynkClient_Data.State = BLYNKCLIENT_STATE_INIT;
    BlynkClient_Data.Notification = BLYNKCLIENT_NO_NOTIFICATION;
    BlynkClient_Data.SyncCounter = 0U;
    BlynkClient_Data.u8PumpFlag = 0U;
    /* Init with max value to start connect at startup.*/
    BlynkClient_Data.ReconnectCounter = BLYNKCLIENT_RECONNECT_WAIT_TIME;
    BlynkClient_Data.u8DataSendingState = BLYNKCLIENT_DATA_SEND_ST1;

 
    /* Blynk Configuration */
    Blynk.config(Blynk_Auth_Token);
    //Blynk.begin(Blynk_Auth_Token);

   // Blynk.begin(Blynk_Auth_Token, WiFi_Name, WiFi_Password);
    // You can also specify server:
    //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
    //Blynk.begin(Blynk_Auth_Token, WiFi_Name, WiFi_Password, IPAddress(IP_1st,IP_2nd,IP_3rd,IP_4th),BLYNKCLIENT_PORT);
    //Blynk.begin(Blynk_Auth_Token, WiFi_Name, WiFi_Password);
#ifdef SERIAL_PRINT_BLYNK
    BlynkClient_SerialPrint = "  ...Stop.";
    Serial.println(BlynkClient_SerialPrint);
#endif

}
/********************************************************
* BlynkClient Main function. 
********************************************************/
void BlynkClient_Main(void)
{
    if (0U < BlynkClient_OneTimeCounter)
    {
        BlynkClient_OneTimeCounter = 0U;
#ifdef SERIAL_PRINT_BLYNK
        BlynkClient_SerialPrint = "BlynkClient: Loop Start.";
        Serial.println(BlynkClient_SerialPrint);
#endif
    }
    else
    {
        /* do nothing */
    }
    if(WIFI_STATUS_CONNECTED == Rte_IRead_BlynkClient_WifiStatus)
    {

        blynkclient_CheckBlinkState();

        switch (BlynkClient_Data.State)
        {
            case BLYNKCLIENT_STATE_INIT:
            {
                /* Wait */
                BlynkClient_SerialPrint = "BlynkClient: BlynkState: Init.";
                Serial.println(BlynkClient_SerialPrint);

                break;
            }
            case BLYNKCLIENT_STATE_CONNECTED:
            {
                /* Run Blynk Handler */
                Blynk.run();

                /* Handle init phase by sync data from server */
                if (BLYNKCLIENT_SYNC_WAIT > BlynkClient_Data.SyncCounter)
                {
                    blynkclient_InitSyncDatas();
                    BlynkClient_Data.SyncCounter++;    
                }
                else
                {
                    /* Init phase done -> do nothing */
                }

                blynkclient_HandlePumpState();    
                
                break;
            }
            case BLYNKCLIENT_STATE_NOT_CONNECTED:
            {
                BlynkClient_SerialPrint = "BlynkClient: BlynkState: NOT Connected.";
                Serial.println(BlynkClient_SerialPrint);

                if(0U < BlynkClient_StartupCounter)
                {
                    /* at sturtup run a few times the blynk client */
                    for (uint8 i = 0; i < 5; i++)
                    {
                        /* Run Blynk Handler */
                        Blynk.run();
                    }
                    BlynkClient_StartupCounter--;
                }
                /* Wait */
                if (BLYNKCLIENT_RECONNECT_WAIT_TIME < BlynkClient_Data.ReconnectCounter)
                {
                    /* Reset counter. */
                    BlynkClient_Data.ReconnectCounter = 0U;
                    //Blynk.disconnect();
                    //Blynk.config(Blynk_Auth_Token);
                    BlynkClient_SerialPrint = "Blynk: Test loop";
                    Serial.println(BlynkClient_SerialPrint);

                    for (uint8 i = 0; i < 5; i++)
                    {
                        /* Run Blynk Handler */
                        Blynk.run();
                    }
                    
                // Blynk.connect();
                }
                else
                {
                    /* increment counter */
                    BlynkClient_Data.ReconnectCounter++;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        /* wait for wifi */
    }
    
}

/********************************************************
* BlynkClient handles the master heating status sending to Blynk server. 
********************************************************/
void blynkclient_HandlePumpState(void)
{
    if (0U != BlynkClient_Data.u8PumpFlag)
    {
        DIO_SetRelayPinValue(BLYNKCLIENT_RELAY_PIN, DIO_RELAY_PIN_ON);

        Blynk.virtualWrite(BLYNKCLIENT_PUMP_STATUS_PIN, DIO_RELAY_PIN_ON);
    }
    else
    {
        DIO_SetRelayPinValue(BLYNKCLIENT_RELAY_PIN, DIO_RELAY_PIN_OFF);

        Blynk.virtualWrite(BLYNKCLIENT_PUMP_STATUS_PIN, DIO_RELAY_PIN_OFF);
    }

    if (0U != Rte_IRead_BlynkClient_ActionFlags)
    {
        Rte_IRead_BlynkClient_ActionFlags = 0U;

        Blynk.virtualWrite(BLYNKCLIENT_PUMP_HEALTH_PIN, 1U);
    }
    else
    {
        /* do nothing */
    }
    
}
/********************************************************
* BlynkClient sync data at power on. 
********************************************************/
void blynkclient_InitSyncDatas(void)
{
    switch (BlynkClient_Data.SyncCounter)
    {
        case 1U:
        {
            Blynk.syncVirtual(V0);
            break;
        }
        case 2U:
        {
            break;
        }
        case 3U:
        {
            break;
        }
        default:
            break;
    }
}

/********************************************************
* BlynkClient chech connection status to the server function. 
********************************************************/
void blynkclient_CheckBlinkState(void)
{
   if(Blynk.connected())
   {
        Rte_IWrite_BlynkClient_ServerConnStatus = BLYNK_SERVER_STATUS_CONNECTED;
        BlynkClient_Data.State = BLYNKCLIENT_STATE_CONNECTED;
        /* Reset counter. */
        BlynkClient_Data.ReconnectCounter = 0U;
#ifdef SERIAL_PRINT_BLYNK
            BlynkClient_SerialPrint = "Blynk: Connected ";
            //Serial.println(BlynkClient_SerialPrint);
#endif
   }
   else
   {
        Rte_IWrite_BlynkClient_ServerConnStatus = BLYNK_SERVER_STATUS_NOT_CONNECTED;
        BlynkClient_Data.State = BLYNKCLIENT_STATE_NOT_CONNECTED;
#ifdef SERIAL_PRINT_BLYNK
            BlynkClient_SerialPrint = "Blynk: Not Conn ";
            Serial.println(BlynkClient_SerialPrint);
#endif

   }

}

BLYNK_WRITE(BLYNKCLIENT_PUMP_CONTROL_PIN)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    if (0U < (uint8)pinValue)
    {
        BlynkClient_Data.u8PumpFlag = 1U;
    }
    else
    {
        BlynkClient_Data.u8PumpFlag = 0U;
    }
    
    BlynkClient_SerialPrint = "Blynk: --------------Data received: " + String(pinValue);
    Serial.println(BlynkClient_SerialPrint);

}


/********************************************************************/
