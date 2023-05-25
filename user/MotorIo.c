#include "gpio.h"
#include "dac.h"
#include "MotorIo.h"

/*
板子ID获取
BaseID:基准ID
*/

uint32_t GetCanRevID(uint32_t BaseID)
{
    uint32_t getid=0;
    getid|=ID0_STATE()<<0;
    getid|=ID1_STATE()<<1;
    getid|=ID2_STATE()<<2;
    getid|=ID3_STATE()<<3;    
    return (BaseID+getid);
}

/*
电机方向设置
Mnum:电机编号
Dr： 设置反向
*/
signed char MotorDirSet(unsigned char Munm,char Dr)
{
    GPIO_TypeDef *prot[8]= {MOTOR1DIR_Port,MOTOR2DIR_Port,MOTOR3DIR_Port,MOTOR4DIR_Port, \
                            MOTOR5DIR_Port,MOTOR6DIR_Port,MOTOR7DIR_Port ,MOTOR8DIR_Port \
                            };
   uint16_t Pin[8]={MOTOR1DIR_Pin,MOTOR2DIR_Pin,MOTOR3DIR_Pin,MOTOR4DIR_Pin,\
                     MOTOR5DIR_Pin,MOTOR6DIR_Pin,MOTOR7DIR_Pin,MOTOR8DIR_Pin       
                   };     
    if(Munm>8||(Dr!=1&&Dr!=0))
    {
        return -1;
    }
    if(Dr)
    {
        HAL_GPIO_WritePin(prot[Munm-1],Pin[Munm-1] ,GPIO_PIN_RESET);
    }
    else        
    {
        HAL_GPIO_WritePin(prot[Munm-1],Pin[Munm-1] ,GPIO_PIN_SET);
    }       
    return 1;
}
/*
电流设置
		Mnum:1(1-4),0(5-8)
        Cval:电流值			
*/
#define DAC_VDDA	3300L
signed char MotorCurrentSet(unsigned char Munm,unsigned int Cval)
{
	long val;
	val = Cval * 4095L / DAC_VDDA;
    if(Munm==1)
    {
        HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1,DAC_ALIGN_8B_R,val);
        HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
    }
    else if(Munm==0)
    {
        HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_2,DAC_ALIGN_8B_R,val);
        HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);    
    }
    return 1;
}

/*
电机电流开关
*/
signed char MotorCurrentSwitch(unsigned char num,char Dr)
{
     GPIO_TypeDef *PORT[8]={MOTO_TQ1_Port,MOTO_TQ2_Port,MOTO_TQ3_Port,MOTO_TQ4_Port,\
                            MOTO_TQ5_Port,MOTO_TQ6_Port,MOTO_TQ7_Port,MOTO_TQ8_Port        
                            };  
     uint16_t PIN[8]={MOTO_TQ1_Pin,MOTO_TQ2_Pin,MOTO_TQ3_Pin,MOTO_TQ4_Pin,\
                      MOTO_TQ5_Pin,MOTO_TQ6_Pin,MOTO_TQ7_Pin,MOTO_TQ8_Pin
                    }; 
    if(num>8||(Dr!=1&&Dr!=0))
	{
			return -1;
	}
    if(Dr)
    {
        HAL_GPIO_WritePin(PORT[num-1],PIN[num-1] ,GPIO_PIN_RESET);
    }
    else        
    {
        HAL_GPIO_WritePin(PORT[num-1],PIN[num-1] ,GPIO_PIN_SET);
    }       
    return 1;    
}


