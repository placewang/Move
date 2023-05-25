/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
#include "MotorIo.h"
#include "queue.h"

Queue Can1_revQueuebuff;	    			  //CAN1队列缓存
QUEUE_DATA_T CAN1Buff[CAN1LEN];				  //CAN1队列数区
QUEUE_DATA_T CAN1_recDataInfo;                //CAN1接收缓存
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */
    CAN_FilterTypeDef  sFilterConfig;	
  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 3;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.FilterBank  				 = 0 ;                     //过滤这里可设0-13
    sFilterConfig.FilterMode  				 = CAN_FILTERMODE_IDLIST ; //采用列表模式
    sFilterConfig.FilterScale 				 = CAN_FILTERSCALE_32BIT;  //采用32位掩
    sFilterConfig.FilterFIFOAssignment       = CAN_FILTER_FIFO0;       //采用FIFO0

    sFilterConfig.FilterIdHigh 		 =(GetCanRevID(CANIDBASE))<<5;     //设置过滤高位
    sFilterConfig.FilterIdLow  		 =0x0000;                          //设置过滤低位
    sFilterConfig.FilterMaskIdHigh = 0xFFFF;                           //设置过滤器掩码高
    sFilterConfig.FilterMaskIdLow  = 0xFFFF;                           //设置过滤器掩码低

    if(HAL_CAN_ConfigFilter(&hcan,&sFilterConfig) != HAL_OK)//初始化过滤器
    {				
        Error_Handler();
    }
    sFilterConfig.FilterBank  				 = 1;                      //过滤这里可设0-13
    sFilterConfig.FilterIdHigh 		 =(BROADCAST_CANID)<<5;            //设置过滤高位
    sFilterConfig.FilterIdLow  		 =0x0000;                          //设置过滤低位
    sFilterConfig.FilterMaskIdHigh = 0xFFFF;                           //设置过滤器掩码高
    sFilterConfig.FilterMaskIdLow  = 0xFFFF;                           //设置过滤器掩码低
    if(HAL_CAN_ConfigFilter(&hcan,&sFilterConfig) != HAL_OK)//初始化过滤器
    {				
        Error_Handler();
    }
    
    if(HAL_CAN_Start(&hcan) != HAL_OK)//打开can
    {		
            Error_Handler();
    }
    if(HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {	
            Error_Handler();
    }
	InitQueue(&Can1_revQueuebuff,CAN1Buff,CAN1LEN);                //接受队列初始    
  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspInit 0 */

  /* USER CODE END CAN_MspInit 0 */
    /* CAN clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN interrupt Init */
    HAL_NVIC_SetPriority(CAN_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN_RX0_IRQn);
  /* USER CODE BEGIN CAN_MspInit 1 */

  /* USER CODE END CAN_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspDeInit 0 */

  /* USER CODE END CAN_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN_RX0_IRQn);
  /* USER CODE BEGIN CAN_MspDeInit 1 */

  /* USER CODE END CAN_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*
CAN1消息发
	dataval:要发送的数据
	DLC:    数据大小或者长度
	Dev_num:设备接收CANID  
*/
void CAN1_Send_Msg(unsigned char * dataval,\
				   const unsigned int    DLC,\
				   const unsigned int    Dev_num)
{
    CAN_TxHeaderTypeDef   CAN1_TxHeader;
    uint32_t              CAN1_TxMailbox;
    CAN1_TxHeader.StdId =Dev_num;        //标准标识
    CAN1_TxHeader.IDE = 0;               //使用标准
    CAN1_TxHeader.RTR = 0;               //数据
    CAN1_TxHeader.DLC =DLC;                
	CAN1_TxHeader.TransmitGlobalTime = DISABLE;
    while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan)==0){;}
	if(HAL_CAN_AddTxMessage(&hcan, &CAN1_TxHeader, dataval, &CAN1_TxMailbox) != HAL_OK)
	{
			Error_Handler();
    }
  
}

/*
接收数据倒换缓存
	@CAN_RxHeaderTypeDef:固件库can接收结
	@CAN_RecvTypeDef: 缓存队列结构
	@pdata:数据
*/
void CanRevDataPermutation(CAN_RxHeaderTypeDef* rev, CAN_RecvTypeDef *val,unsigned char * pdata)
{
	int i=0;
		if(rev->IDE==0x00)
		{
			val->StdId=rev->StdId;
		}
		else if(rev->IDE==0x04)
		{
				val->StdId=rev->ExtId;
		}
		val->IDE=rev->IDE;
		val->RTR=rev->RTR;
		val->DLC=rev->DLC;
		for(i=0;i<rev->DLC;i++)
		{
			val->RxData[i]=pdata[i];
		}
}
//中断接收
void CanITRevFIF0(CAN_HandleTypeDef *hcan1)
{

    CAN_RxHeaderTypeDef RevBuff;
    uint8_t Pdata[8]={0};
    if((hcan1->Instance->IER & CAN_IT_RX_FIFO0_MSG_PENDING) != RESET)  
    { 
        while(1)
        {
            if ((hcan1->Instance->RF0R & CAN_RF0R_FMP0) == 0U)
            {
                break;
            }
            if(HAL_CAN_GetRxMessage(hcan1,CAN_RX_FIFO0, &RevBuff, Pdata)==HAL_OK)
            {
                CanRevDataPermutation(&RevBuff,&CAN1_recDataInfo,Pdata);
                EnQueue(&Can1_revQueuebuff,CAN1_recDataInfo);
            }								
        }
    }	
}
/* USER CODE END 1 */
