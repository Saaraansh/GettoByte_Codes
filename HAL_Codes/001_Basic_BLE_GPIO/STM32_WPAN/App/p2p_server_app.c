/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/p2p_server_app.c
  * @author  MCD Application Team
  * @brief   Peer to peer Server Application
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "p2p_server_app.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
 typedef struct{
    uint8_t             Device_Led_Selection;
    uint8_t             Led;

 }P2P_LedCharValue_t;

typedef struct
{
  uint8_t               Notification_Status; /* used to check if P2P Server is enabled to Notify */
  P2P_LedCharValue_t    LedControl;
  uint16_t              ConnectionHandle;
} P2P_Server_App_Context_t;

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/**
 * START of Section BLE_APP_CONTEXT
 */

PLACE_IN_SECTION("BLE_APP_CONTEXT") static P2P_Server_App_Context_t P2P_Server_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

static void P2PS_Send_Notification(void);
static void P2PS_APP_LED_context_Init(void);

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void P2PS_STM_App_Notification(P2PS_STM_App_Notification_evt_t *pNotification)
{
/* USER CODE BEGIN P2PS_STM_App_Notification_1 */

/* USER CODE END P2PS_STM_App_Notification_1 */
  switch(pNotification->P2P_Evt_Opcode)
  {
/* USER CODE BEGIN P2PS_STM_App_Notification_P2P_Evt_Opcode */

/* USER CODE END P2PS_STM_App_Notification_P2P_Evt_Opcode */

    case P2PS_STM__NOTIFY_ENABLED_EVT:
/* USER CODE BEGIN P2PS_STM__NOTIFY_ENABLED_EVT */

        P2P_Server_App_Context.Notification_Status = 1;
        APP_DBG_MSG("-- P2P APPLICATION SERVER : NOTIFICATION ENABLED\n");
        APP_DBG_MSG(" \n\r");

/* USER CODE END P2PS_STM__NOTIFY_ENABLED_EVT */
      break;

    case P2PS_STM_NOTIFY_DISABLED_EVT:
/* USER CODE BEGIN P2PS_STM_NOTIFY_DISABLED_EVT */

        P2P_Server_App_Context.Notification_Status = 0;
        APP_DBG_MSG("-- P2P APPLICATION SERVER : NOTIFICATION DISABLED\n");
        APP_DBG_MSG(" \n\r");

/* USER CODE END P2PS_STM_NOTIFY_DISABLED_EVT */
      break;

    case P2PS_STM_WRITE_EVT:
/* USER CODE BEGIN P2PS_STM_WRITE_EVT */

        if(pNotification->DataTransfered.pPayload[0] == 0x00)
        {
          if(pNotification->DataTransfered.pPayload[1] == 0x01)
          {
        	HAL_GPIO_WritePin(Led_Red_1_GPIO_Port, Led_Red_1_Pin, SET);
        	HAL_GPIO_WritePin(Led_Red_2_GPIO_Port, Led_Red_2_Pin, SET);
        	HAL_Delay(1000);
        	HAL_GPIO_WritePin(Led_Red_1_GPIO_Port, Led_Red_1_Pin, RESET);
        	HAL_GPIO_WritePin(Led_Red_2_GPIO_Port, Led_Red_2_Pin, RESET);
        	HAL_Delay(1000);
            APP_DBG_MSG("-- P2P APPLICATION SERVER  : LED RED Toggle\n");
            APP_DBG_MSG(" \n\r");
            P2P_Server_App_Context.LedControl.Led = 0x01;
            P2PS_STM_App_Update_Char(P2P_NOTIFY_CHAR_UUID, (uint8_t *)&P2P_Server_App_Context.LedControl.Led);
          }
          if(pNotification->DataTransfered.pPayload[1] == 0x02)
          {
        	HAL_GPIO_WritePin(Led_Blue_1_GPIO_Port, Led_Blue_1_Pin, SET);
        	HAL_GPIO_WritePin(Led_Blue_2_GPIO_Port, Led_Blue_2_Pin, SET);
        	HAL_Delay(1000);
        	HAL_GPIO_WritePin(Led_Blue_1_GPIO_Port, Led_Blue_1_Pin, RESET);
        	HAL_GPIO_WritePin(Led_Blue_2_GPIO_Port, Led_Blue_2_Pin, RESET);
        	HAL_Delay(1000);
            APP_DBG_MSG("-- P2P APPLICATION SERVER  : LED BLUE Toggle\n");
            APP_DBG_MSG(" \n\r");
            P2P_Server_App_Context.LedControl.Led = 0x02;
            P2PS_STM_App_Update_Char(P2P_NOTIFY_CHAR_UUID, (uint8_t *)&P2P_Server_App_Context.LedControl.Led);
          }
          if(pNotification->DataTransfered.pPayload[1] == 0x03)
          {
        	HAL_GPIO_WritePin(Led_Green_1_GPIO_Port, Led_Green_1_Pin, SET);
        	HAL_GPIO_WritePin(Led_Green_2_GPIO_Port, Led_Green_2_Pin, SET);
        	HAL_Delay(1000);
        	HAL_GPIO_WritePin(Led_Green_1_GPIO_Port, Led_Green_1_Pin, RESET);
        	HAL_GPIO_WritePin(Led_Green_2_GPIO_Port, Led_Green_2_Pin, RESET);
        	HAL_Delay(1000);
            APP_DBG_MSG("-- P2P APPLICATION SERVER  : LED GREEN Toggle\n");
            APP_DBG_MSG(" \n\r");
            P2P_Server_App_Context.LedControl.Led = 0x03;
            P2PS_STM_App_Update_Char(P2P_NOTIFY_CHAR_UUID, (uint8_t *)&P2P_Server_App_Context.LedControl.Led);
          }
          if(pNotification->DataTransfered.pPayload[1] == 0x00)
          {
            HAL_GPIO_WritePin(Led_Red_1_GPIO_Port, Led_Red_1_Pin, SET);
            HAL_GPIO_WritePin(Led_Red_2_GPIO_Port, Led_Red_2_Pin, SET);
            HAL_GPIO_WritePin(Led_Blue_1_GPIO_Port, Led_Blue_1_Pin, SET);
            HAL_GPIO_WritePin(Led_Blue_2_GPIO_Port, Led_Blue_2_Pin, SET);
            HAL_GPIO_WritePin(Led_Green_1_GPIO_Port, Led_Green_1_Pin, SET);
           	HAL_GPIO_WritePin(Led_Green_2_GPIO_Port, Led_Green_2_Pin, SET);
           	HAL_Delay(1000);
        	HAL_GPIO_WritePin(Led_Red_1_GPIO_Port, Led_Red_1_Pin, RESET);
          	HAL_GPIO_WritePin(Led_Red_2_GPIO_Port, Led_Red_2_Pin, RESET);
          	HAL_GPIO_WritePin(Led_Blue_1_GPIO_Port, Led_Blue_1_Pin, RESET);
          	HAL_GPIO_WritePin(Led_Blue_2_GPIO_Port, Led_Blue_2_Pin, RESET);
          	HAL_GPIO_WritePin(Led_Green_1_GPIO_Port, Led_Green_1_Pin, RESET);
          	HAL_GPIO_WritePin(Led_Green_2_GPIO_Port, Led_Green_2_Pin, RESET);
          	HAL_Delay(1000);
            APP_DBG_MSG("-- P2P APPLICATION SERVER  : All LEDs Toggle\n");
            APP_DBG_MSG(" \n\r");
            P2P_Server_App_Context.LedControl.Led = 0x00;
            P2PS_STM_App_Update_Char(P2P_NOTIFY_CHAR_UUID, (uint8_t *)&P2P_Server_App_Context.LedControl.Led);
          }
        }

/* USER CODE END P2PS_STM_WRITE_EVT */
      break;

    default:
/* USER CODE BEGIN P2PS_STM_App_Notification_default */

/* USER CODE END P2PS_STM_App_Notification_default */
      break;
  }
/* USER CODE BEGIN P2PS_STM_App_Notification_2 */

/* USER CODE END P2PS_STM_App_Notification_2 */
  return;
}

void P2PS_APP_Notification(P2PS_APP_ConnHandle_Not_evt_t *pNotification)
{
/* USER CODE BEGIN P2PS_APP_Notification_1 */

/* USER CODE END P2PS_APP_Notification_1 */
  switch(pNotification->P2P_Evt_Opcode)
  {
/* USER CODE BEGIN P2PS_APP_Notification_P2P_Evt_Opcode */

/* USER CODE END P2PS_APP_Notification_P2P_Evt_Opcode */
  case PEER_CONN_HANDLE_EVT :
/* USER CODE BEGIN PEER_CONN_HANDLE_EVT */

/* USER CODE END PEER_CONN_HANDLE_EVT */
    break;

    case PEER_DISCON_HANDLE_EVT :
/* USER CODE BEGIN PEER_DISCON_HANDLE_EVT */

/* USER CODE END PEER_DISCON_HANDLE_EVT */
    break;

    default:
/* USER CODE BEGIN P2PS_APP_Notification_default */

/* USER CODE END P2PS_APP_Notification_default */
      break;
  }
/* USER CODE BEGIN P2PS_APP_Notification_2 */

/* USER CODE END P2PS_APP_Notification_2 */
  return;
}

void P2PS_APP_Init(void)
{
/* USER CODE BEGIN P2PS_APP_Init */
	P2P_Server_App_Context.Notification_Status=0;
/* USER CODE END P2PS_APP_Init */
  return;
}

/* USER CODE BEGIN FD */


/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/

/* USER CODE END FD_LOCAL_FUNCTIONS*/
