#ifndef COMPILER_SWITCH_H
#define COMPILER_SWITCH_H 1
/* This header shall be included in everi software component.
    This header includes defines which are used as compiler switches. */

#define SERIAL_PRINT_TASKMGR                    1U /* If this define exist serial prints are working for TaskMgr module */
#define SERIAL_PRINT_RELAYMGR                   1U /* If this define exist serial prints are working for Relaymgr module */
#define SERIAL_PRINT_DIO                        1U /* If this define exist serial prints are working for DIO module */
#define SERIAL_PRINT_WIFIMGR                    1U /* If this define exist serial prints are working for WifiMgr module */


/* If this define exist then IO pin is seted to LOW in order to activate relay/heating. */
/* Comment/delete define for reqular active on HIGH relay*/
#define RELAY_TYPE_ACTIVE_ON_LOW            1U

#ifdef RELAY_TYPE_ACTIVE_ON_LOW
#define RELAY_DEFAULT_INIT_VALUE            HIGH
#else
#define RELAY_DEFAULT_INIT_VALUE            LOW
#endif

/* Some other defines used by all the modules */
#define TRUE                    1U
#define FALSE                   0U

#define WIFI_STATUS_INIT                0U
#define WIFI_STATUS_CONNECTED           1U
#define WIFI_STATUS_NOT_CONNECTED       2U



#define BLYNK_SERVER_STATUS_INIT                0U
#define BLYNK_SERVER_STATUS_CONNECTED           1U
#define BLYNK_SERVER_STATUS_NOT_CONNECTED       2U

#define BLYNKCLIENT_PUMP_CONTROL_PIN            V0
#define BLYNKCLIENT_PUMP_STATUS_PIN             V1
#define BLYNKCLIENT_PUMP_HEALTH_PIN             V2

/***************** Configuration *****************/
/// Blynk configuration ///
#define BLYNK_TEMPLATE_ID "T*******g"       /* add your template ID */
#define BLYNK_DEVICE_NAME "WaterPump"       /* add your device name */
const char Blynk_Auth_Token[] = "Q3*****************N";     /* add your Authentication token */


const char WiFi_Name[] = "o*****0";            /* add yourWiFi name (SSID) */  
const char WiFi_Password[] = "4********F7";    /* add yourWiFi password */

#endif