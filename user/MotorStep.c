#include "tim.h"
#include "MotorStep.h"
#include "MotorIo.h"
#include "MotorMove.h"

AccelerationDeceleration  L_MotorParameter[4]={0};
AccelerationDeceleration  R_MotorParameter[4]={0};

/*
左比较输出启动（比较中断）
Snum：启动通道
*/
signed char L_ComparativeOutputStar(unsigned Snum)
{
	unsigned int  CH1val=0,CH2val=0,CH3val=0,CH4val=0;
	switch (Snum)
	{
		case 1:
            CH1val=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);
            __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0xffffffff&(CH1val+1));
            HAL_TIM_OC_Start_IT(&htim5,TIM_CHANNEL_1);
			break;
		case 2:
            CH2val=HAL_TIM_ReadCapturedValue(&htim16,TIM_CHANNEL_1);
            __HAL_TIM_SetCompare(&htim16,TIM_CHANNEL_1,0xffff&(CH2val+1));
            HAL_TIM_OC_Start_IT(&htim16,TIM_CHANNEL_1);  
			break;
		case 3:
            CH3val=HAL_TIM_ReadCapturedValue(&htim14,TIM_CHANNEL_1);
            __HAL_TIM_SetCompare(&htim14,TIM_CHANNEL_1,0xffff&(CH3val+1));
            HAL_TIM_OC_Start_IT(&htim14,TIM_CHANNEL_1);  
			break;
		case 4:
            CH4val=HAL_TIM_ReadCapturedValue(&htim13,TIM_CHANNEL_1);
            __HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1,0xffff&(CH4val+1));
            HAL_TIM_OC_Start_IT(&htim13,TIM_CHANNEL_1);    
			break;
		case 0:
            CH1val=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);	
            CH2val=HAL_TIM_ReadCapturedValue(&htim16,TIM_CHANNEL_1);
			CH3val=HAL_TIM_ReadCapturedValue(&htim14,TIM_CHANNEL_1);
            CH4val=HAL_TIM_ReadCapturedValue(&htim13,TIM_CHANNEL_1);
            __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0xffffffff&(CH1val+1));
            HAL_TIM_OC_Start_IT(&htim5,TIM_CHANNEL_1);   
            __HAL_TIM_SetCompare(&htim16,TIM_CHANNEL_1,0xffff&(CH2val+1));
            HAL_TIM_OC_Start_IT(&htim16,TIM_CHANNEL_1);  
            __HAL_TIM_SetCompare(&htim14,TIM_CHANNEL_1,0xffff&(CH3val+1));
            HAL_TIM_OC_Start_IT(&htim14,TIM_CHANNEL_1); 
            __HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1,0xffff&(CH4val+1));
            HAL_TIM_OC_Start_IT(&htim13,TIM_CHANNEL_1);         
            break;		
		default:
				break;		
	}
	return 0;
}



/*
右比较输出启动（比较中断）
Snum：启动通道
*/
signed char R_ComparativeOutputStar(unsigned Snum)
{
	unsigned int  CH1val=0,CH2val=0,CH3val=0,CH4val=0;
	switch (Snum)
	{
		case 1:
            CH1val=HAL_TIM_ReadCapturedValue(&htim12,TIM_CHANNEL_2);
            __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,0xffff&(CH1val+1));
            HAL_TIM_OC_Start_IT(&htim12,TIM_CHANNEL_2);  
			break;
		case 2:
            CH2val=HAL_TIM_ReadCapturedValue(&htim19,TIM_CHANNEL_2);
            __HAL_TIM_SetCompare(&htim19,TIM_CHANNEL_2,0xffff&(CH2val+1));
            HAL_TIM_OC_Start_IT(&htim19,TIM_CHANNEL_2);  
			break;
		case 3:
            CH3val=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);
            __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,0xffff&(CH3val+1));
            HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_2);
			break;
		case 4:
            CH4val=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_4);
            __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0xffff&(CH4val+1));
            HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_4);   
			break;
		case 0:
            CH1val=HAL_TIM_ReadCapturedValue(&htim12,TIM_CHANNEL_2);	
            CH2val=HAL_TIM_ReadCapturedValue(&htim19,TIM_CHANNEL_2);
			CH3val=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);
            CH4val=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_4);
            __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,0xffff&(CH1val+1));
            HAL_TIM_OC_Start_IT(&htim12,TIM_CHANNEL_2); 
            __HAL_TIM_SetCompare(&htim19,TIM_CHANNEL_2,0xffff&(CH2val+1));
            HAL_TIM_OC_Start_IT(&htim19,TIM_CHANNEL_2);
            __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,0xffff&(CH3val+1));
            HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_2);
            __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0xffff&(CH4val+1));
            HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_4);         
            break;		
		default:
				break;		
	}
	return 0;
}





/*
左比较输出停止（比较中断）
num：启动通道
*/
signed char L_ComparativeOutputStop(unsigned Tnum)
{

	switch (Tnum)
	{
		case 1:
			HAL_TIM_OC_Stop_IT(&htim5,TIM_CHANNEL_1);
			break;
		case 2:
			HAL_TIM_OC_Stop_IT(&htim16,TIM_CHANNEL_1);
			break;
		case 3:
			HAL_TIM_OC_Stop_IT(&htim14,TIM_CHANNEL_1);
			break;
		case 4:
			HAL_TIM_OC_Stop_IT(&htim13,TIM_CHANNEL_1);
			break;
		case 0:
			HAL_TIM_OC_Stop_IT(&htim5,TIM_CHANNEL_1);
			HAL_TIM_OC_Stop_IT(&htim16,TIM_CHANNEL_1);
			HAL_TIM_OC_Stop_IT(&htim14,TIM_CHANNEL_1);
			HAL_TIM_OC_Stop_IT(&htim13,TIM_CHANNEL_1);		
			break;		
		default:
				break;		
	}
    L_MotorStateGet(Tnum,0);
	return 0;
}



/*
右比较输出停止（比较中断）
num：启动通道
*/
signed char R_ComparativeOutputStop(unsigned Tnum)
{
	switch (Tnum)
	{
		case 1:
			HAL_TIM_OC_Stop_IT(&htim12,TIM_CHANNEL_2);
			break;
		case 2:
			HAL_TIM_OC_Stop_IT(&htim19,TIM_CHANNEL_2);
			break;
		case 3:
			HAL_TIM_OC_Stop_IT(&htim2,TIM_CHANNEL_2);
			break;
		case 4:
			HAL_TIM_OC_Stop_IT(&htim3,TIM_CHANNEL_4);
			break;
		case 0:
			HAL_TIM_OC_Stop_IT(&htim12,TIM_CHANNEL_2);
			HAL_TIM_OC_Stop_IT(&htim19,TIM_CHANNEL_2);
			HAL_TIM_OC_Stop_IT(&htim2,TIM_CHANNEL_2);
			HAL_TIM_OC_Stop_IT(&htim3,TIM_CHANNEL_4);		
			break;		
		default:
				break;		
	}
    R_MotorStateGet(Tnum,0); 
	return 0;
}








/*
电机以给定的步数移动步进电机
mtnum  电机编号0:全部电机（4个）
speed  最大速度(PWM_HZ)
pos    移动的位置（脉冲数）
Dr     方向
*/
signed char L_MotorMovePos(unsigned char mtnum,unsigned int speed,signed int pos,uint8_t Dr)
{
    float tval=0.0,tval2=0.0;  
    if(pos==0||speed>1000*10||mtnum>4||(Dr!=1&&Dr!=0))
        return 0;
    //最小速度仅做到10HZ
    if(speed<10)
        speed=10;

    if(mtnum!=0)
    {
        tval=1/(float)speed;
        tval2=tval/(float)TIM1COUNTCYCLE;
        L_MotorParameter[mtnum-1].TargetSpeed= ((unsigned int)tval2)/2;
        if(speed>=10*100)  //启动速度换算    
        {
            L_MotorParameter[mtnum-1].nowfrequency=100;        
        }
        else
        {            
            L_MotorParameter[mtnum-1].nowfrequency=(((unsigned int)tval2)/2)*2;              
        }       
        L_MotorParameter[mtnum-1].PulseCount=0;
        L_MotorParameter[mtnum-1].PulseTargetCount=pos;
        L_MotorParameter[mtnum-1].StateFlag=StartUpSpeed;
        MotorDirSet(mtnum,Dr);
        MotorCurrentSwitch(mtnum,1);
        //移动步数无法构成加减速过程（直接运行）
        if(pos<15)
        {    
            L_MotorParameter[mtnum-1].StateFlag=CompletionAcceleration;
        } 
        L_MotorParameter[mtnum-1].DecelerationFactor=(pos/5)/200;
        if( L_MotorParameter[mtnum-1].DecelerationFactor==0)
        {
             L_MotorParameter[mtnum-1].DecelerationFactor=8;
        }
        else
        {
            L_MotorParameter[mtnum-1].DecelerationFactor+=8;
        }
      
        if(speed>=10&&speed<=20*100)
        {
            L_MotorParameter[mtnum-1].AccelerationIn=20;
            L_MotorParameter[mtnum-1].DecelerationIn=((speed/pos)+1);         
        }
         else if(speed>20*100&&speed<=100*100)
        {
            L_MotorParameter[mtnum-1].AccelerationIn=1;
            L_MotorParameter[mtnum-1].DecelerationIn=((speed/pos)+5);         
        }        
        //预刷新
        L_MotorStateGet(mtnum,L_MotorParameter[mtnum-1].StateFlag);          
        L_ComparativeOutputStar(mtnum);  
    }    
    else       
    {
        for(int i=0;i<4;i++)
        {
            tval=1/(float)speed;
            tval2=tval/(float)TIM1COUNTCYCLE;
            L_MotorParameter[i].TargetSpeed= ((unsigned int)tval2)/2;   
            if(speed>=10*100)  //启动速度换算    
            {
                L_MotorParameter[i].nowfrequency=100;        
            }
            else
            {            
                L_MotorParameter[i].nowfrequency=(((unsigned int)tval2)/2)*2;              
            }                       
            L_MotorParameter[i].PulseCount=0;
            L_MotorParameter[i].PulseTargetCount=pos;
            L_MotorParameter[i].StateFlag=StartUpSpeed;  
            MotorDirSet(i+1,Dr); 
            MotorCurrentSwitch(i+1,1);
            if(pos<15)
            {    
                L_MotorParameter[i].StateFlag=CompleteDeceleration;
            } 
            L_MotorParameter[i].DecelerationFactor=(pos/5)/200;
            if( L_MotorParameter[i].DecelerationFactor==0)
            {
                 L_MotorParameter[i].DecelerationFactor=8;
            }
            else
            {
                L_MotorParameter[i].DecelerationFactor+=8;
            }
            if(speed>=10&&speed<=20*100)
            {
                L_MotorParameter[i].AccelerationIn=20;
                L_MotorParameter[i].DecelerationIn=((speed/pos)+1);         
            }
             else if(speed>20*100&&speed<=100*100)
            {
                L_MotorParameter[i].AccelerationIn=1;
                L_MotorParameter[i].DecelerationIn=((speed/pos)+10);          
            } 
               
        }
        //预刷新电机状态
        L_MotorStateGet(mtnum,L_MotorParameter[1].StateFlag);          
        L_ComparativeOutputStar(0);      
       
    }

  return 0;      
    
}





/*
电机以给定的步数移动步进电机
mtnum  电机编号0:全部电机（4个）
speed  最大速度(PWM_HZ)
pos    移动的位置（脉冲数）
Dr     方向
*/
signed char R_MotorMovePos(unsigned char mtnum,unsigned int speed,signed int pos,uint8_t Dr)
{
    float tval=0.0,tval2=0.0;  
    if(pos==0||speed>1000*10||mtnum>4||(Dr!=1&&Dr!=0))
        return 0;
    //最小速度仅做到10HZ
    if(speed<10)
        speed=10;

    if(mtnum!=0)
    {
        tval=1/(float)speed;
        tval2=tval/(float)TIM1COUNTCYCLE;
        R_MotorParameter[mtnum-1].TargetSpeed= ((unsigned int)tval2)/2;
        if(speed>=10*100)  //启动速度换算    
        {
            R_MotorParameter[mtnum-1].nowfrequency=100;        
        }
        else
        {            
            R_MotorParameter[mtnum-1].nowfrequency=(((unsigned int)tval2)/2)*2;              
        }       
        R_MotorParameter[mtnum-1].PulseCount=0;
        R_MotorParameter[mtnum-1].PulseTargetCount=pos;
        R_MotorParameter[mtnum-1].StateFlag=StartUpSpeed;
        MotorDirSet(mtnum+4,Dr);
        MotorCurrentSwitch(mtnum+4,1);
        //移动步数无法构成加减速过程（直接运行）
        if(pos<15)
        {    
            R_MotorParameter[mtnum-1].StateFlag=CompletionAcceleration;
        } 
        R_MotorParameter[mtnum-1].DecelerationFactor=(pos/5)/200;
        if( R_MotorParameter[mtnum-1].DecelerationFactor==0)
        {
             R_MotorParameter[mtnum-1].DecelerationFactor=8;
        }
        else
        {
            R_MotorParameter[mtnum-1].DecelerationFactor+=8;
        }
      
        if(speed>=10&&speed<=20*100)
        {
            R_MotorParameter[mtnum-1].AccelerationIn=20;
            R_MotorParameter[mtnum-1].DecelerationIn=((speed/pos)+1);         
        }
         else if(speed>20*100&&speed<=100*100)
        {
            R_MotorParameter[mtnum-1].AccelerationIn=1;
            R_MotorParameter[mtnum-1].DecelerationIn=((speed/pos)+5);         
        }
        R_MotorStateGet(mtnum,L_MotorParameter[mtnum-1].StateFlag);        
        R_ComparativeOutputStar(mtnum);     
    } 
    else       
    {
        for(int i=0;i<4;i++)
        {
            tval=1/(float)speed;
            tval2=tval/(float)TIM1COUNTCYCLE;
            R_MotorParameter[i].TargetSpeed= ((unsigned int)tval2)/2;   
            if(speed>=10*100)  //启动速度换算    
            {
                R_MotorParameter[i].nowfrequency=100;        
            }
            else
            {            
                R_MotorParameter[i].nowfrequency=(((unsigned int)tval2)/2)*2;              
            }                       
            R_MotorParameter[i].PulseCount=0;
            R_MotorParameter[i].PulseTargetCount=pos;
            R_MotorParameter[i].StateFlag=StartUpSpeed;  
            MotorDirSet(i+5,Dr); 
            MotorCurrentSwitch(i+5,1);
            if(pos<15)
            {    
                R_MotorParameter[i].StateFlag=CompleteDeceleration;
            } 
            R_MotorParameter[i].DecelerationFactor=(pos/5)/200;
            if( R_MotorParameter[i].DecelerationFactor==0)
            {
                 R_MotorParameter[i].DecelerationFactor=8;
            }
            else
            {
                R_MotorParameter[i].DecelerationFactor+=8;
            }
            if(speed>=10&&speed<=20*100)
            {
                R_MotorParameter[i].AccelerationIn=20;
                R_MotorParameter[i].DecelerationIn=((speed/pos)+1);         
            }
             else if(speed>20*100&&speed<=100*100)
            {
                R_MotorParameter[i].AccelerationIn=1;
                R_MotorParameter[i].DecelerationIn=((speed/pos)+10);         
            }                
        }
        R_MotorStateGet(mtnum,StartUpSpeed);         
        R_ComparativeOutputStar(0);       
    }
    return 0;
}



/*
速度过程决策
*/
signed char L_MotorSpeedDecision(uint8_t Mnum,AccelerationDeceleration* Mst)
{
        switch(Mst->StateFlag)
        {
            case StartUpSpeed:
                //启动      
                Mst->StateFlag=CompletionAcceleration;
            
                break;
            case CompletionAcceleration:
               if(Mst->PulseCount%2==0)  
               {  
                   Mst->nowfrequency-=Mst->AccelerationIn;
               }
               if(Mst->nowfrequency<=Mst->TargetSpeed)
               {
                    Mst->StateFlag=AverageVelocity;
               }
               if((Mst->PulseCount/2)>=Mst->PulseTargetCount/3)
               {
                      Mst->StateFlag=AverageVelocity;
               }                    
               break;
            case AverageVelocity: 
               if((Mst->PulseCount/2)>=(Mst->PulseTargetCount/Mst->DecelerationFactor)*(Mst->DecelerationFactor-1))
               {
                      Mst->StateFlag=StartSlowDown;      
               }
               break;             
            case StartSlowDown:
               if((Mst->PulseCount/2)>=Mst->PulseTargetCount)
               {
                    Mst->StateFlag=CompleteDeceleration;
               }             
               else if((Mst->PulseCount%2)==0&&Mst->nowfrequency<100)
               {
                   Mst->nowfrequency+=Mst->DecelerationIn;
               }                  
               break;
            case CompleteDeceleration:
                    //停止
                    Mst->StateFlag=0;
                    L_ComparativeOutputStop(Mnum);
                break;  
            default:
                break;
        }
        L_MotorStateGet(Mnum,Mst->StateFlag);
        return 0;
}


/*
速度过程决策
*/
signed char R_MotorSpeedDecision(uint8_t Mnum,AccelerationDeceleration* Mst)
{
        switch(Mst->StateFlag)
        {
            case StartUpSpeed:
                //启动      
                Mst->StateFlag=CompletionAcceleration;
                break;
            case CompletionAcceleration:
               if(Mst->PulseCount%2==0)  
               {  
                   Mst->nowfrequency-=Mst->AccelerationIn;
               }
               if(Mst->nowfrequency<=Mst->TargetSpeed)
               {
                    Mst->StateFlag=AverageVelocity;
               }
               if((Mst->PulseCount/2)>=Mst->PulseTargetCount/3)
               {
                      Mst->StateFlag=AverageVelocity;
               }                    
               break;
            case AverageVelocity: 
               if((Mst->PulseCount/2)>=(Mst->PulseTargetCount/Mst->DecelerationFactor)*(Mst->DecelerationFactor-1))
               {
                      Mst->StateFlag=StartSlowDown;      
               }
               break;             
            case StartSlowDown:
               if((Mst->PulseCount/2)>=Mst->PulseTargetCount)
               {
                    Mst->StateFlag=CompleteDeceleration;
               }             
               else if((Mst->PulseCount%2)==0&&Mst->nowfrequency<100)
               {
                   Mst->nowfrequency+=Mst->DecelerationIn;
               }                  
               break;
            case CompleteDeceleration:
                    //停止
                    Mst->StateFlag=0;
                    R_ComparativeOutputStop(Mnum);
                break;  
            default:
                break;
        }
        R_MotorStateGet(Mnum,Mst->StateFlag);
   return 0;
}



/*
比较中断处理函数(pwm频率计数值设置)
*/
	
signed char TIMxxComparisonInterrupt(void)
{
   uint32_t CPTime5=0,CPTime13=0,CPTime19=0,CPTime3=0,CPTime16=0,CPTime2=0;

//Time12    Mt_5

    if(TIM12->DIER&0x0004&&__HAL_TIM_GET_FLAG(&htim12,TIM_FLAG_CC2))
	{
        R_MotorParameter[0].PulseCount++;   
        if(HAL_GPIO_ReadPin(MOTOR5DIR_Port,MOTOR5DIR_Pin)&&R_MotorParameter[0].PulseCount%2==0)
        {
             RMt_Move_1.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR5DIR_Port,MOTOR5DIR_Pin)&&R_MotorParameter[0].PulseCount%2==0)
        {
           RMt_Move_1.MotEncoder++;  
        }   
        R_MotorSpeedDecision(1,&R_MotorParameter[0]);          
        CPTime2=HAL_TIM_ReadCapturedValue(&htim12,TIM_CHANNEL_2);
        CPTime2+=R_MotorParameter[0].nowfrequency;
        __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,0xffff&CPTime2);
        __HAL_TIM_CLEAR_IT(&htim12,TIM_IT_CC2);
    }    
    //Time2   Mt_7
	if(TIM2->DIER&0x0004&&__HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_CC2))
	{
        R_MotorParameter[2].PulseCount++;   
        if(HAL_GPIO_ReadPin(MOTOR7DIR_Port,MOTOR7DIR_Pin)&&R_MotorParameter[2].PulseCount%2==0)
        {
             RMt_Move_3.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR7DIR_Port,MOTOR7DIR_Pin)&&R_MotorParameter[2].PulseCount%2==0)
        {
           RMt_Move_3.MotEncoder++;  
        }  
        R_MotorSpeedDecision(3,&R_MotorParameter[2]);          
        CPTime2=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);
        CPTime2+=R_MotorParameter[2].nowfrequency;
        __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,0xffff&CPTime2);
        __HAL_TIM_CLEAR_IT(&htim2,TIM_IT_CC2); 
    }  
    //Time14 Mt_3
	if(TIM14->DIER&0x0002&&__HAL_TIM_GET_FLAG(&htim14,TIM_FLAG_CC1))
	{    
        L_MotorParameter[2].PulseCount++;
        if(HAL_GPIO_ReadPin(MOTOR3DIR_Port,MOTOR3DIR_Pin)&&L_MotorParameter[2].PulseCount%2==0)
        {
             LMt_Move_3.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR3DIR_Port,MOTOR3DIR_Pin)&&L_MotorParameter[2].PulseCount%2==0)
        {
           LMt_Move_3.MotEncoder++;  
        }          
        L_MotorSpeedDecision(3,&L_MotorParameter[2]);  
        CPTime3=HAL_TIM_ReadCapturedValue(&htim14,TIM_CHANNEL_1);
        CPTime3+=L_MotorParameter[2].nowfrequency;        
        __HAL_TIM_SetCompare(&htim14,TIM_CHANNEL_1,0xffff&CPTime3);
        __HAL_TIM_CLEAR_IT(&htim14,TIM_IT_CC1);    
    }
    //Time3   Mt_8
	if(TIM3->DIER&0x0010&&__HAL_TIM_GET_FLAG(&htim3,TIM_FLAG_CC4))
	{    
        R_MotorParameter[3].PulseCount++;   
        if(HAL_GPIO_ReadPin(MOTOR8DIR_Port,MOTOR8DIR_Pin)&&R_MotorParameter[3].PulseCount%2==0)
        {
             RMt_Move_4.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR8DIR_Port,MOTOR8DIR_Pin)&&R_MotorParameter[3].PulseCount%2==0)
        {
           RMt_Move_4.MotEncoder++;  
        }  
        R_MotorSpeedDecision(4,&R_MotorParameter[3]);       
        CPTime3=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_4);
        CPTime3+=R_MotorParameter[3].nowfrequency;
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0xffff&CPTime3);
        __HAL_TIM_CLEAR_IT(&htim3,TIM_IT_CC4);
    } 
//Time5    Mt_1
	if(TIM5->DIER&0x0002&&__HAL_TIM_GET_FLAG(&htim5,TIM_FLAG_CC1))
	{    
        L_MotorParameter[0].PulseCount++;  
        if(HAL_GPIO_ReadPin(MOTOR1DIR_Port,MOTOR1DIR_Pin)&&L_MotorParameter[0].PulseCount%2==0)
        {
             LMt_Move_1.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR1DIR_Port,MOTOR1DIR_Pin)&&L_MotorParameter[0].PulseCount%2==0)
        {
           LMt_Move_1.MotEncoder++;  
        }    
        L_MotorSpeedDecision(1,&L_MotorParameter[0]);
        CPTime5=HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);
        CPTime5+=L_MotorParameter[0].nowfrequency;
        __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0xffffffff&CPTime5);
        __HAL_TIM_CLEAR_IT(&htim5,TIM_IT_CC1);
     
    }
//Time13    //Mt_4
	if(TIM13->DIER&0x0002&&__HAL_TIM_GET_FLAG(&htim13,TIM_FLAG_CC1))
	{    
        L_MotorParameter[3].PulseCount++;
        if(HAL_GPIO_ReadPin(MOTOR4DIR_Port,MOTOR4DIR_Pin)&&L_MotorParameter[3].PulseCount%2==0)
        {
             LMt_Move_4.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR4DIR_Port,MOTOR4DIR_Pin)&&L_MotorParameter[3].PulseCount%2==0)
        {
           LMt_Move_4.MotEncoder++;  
        }          
        L_MotorSpeedDecision(4,&L_MotorParameter[3]);         
        CPTime13=HAL_TIM_ReadCapturedValue(&htim13,TIM_CHANNEL_1);
        CPTime13+=L_MotorParameter[3].nowfrequency;
        __HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1,0xffff&CPTime13);
        __HAL_TIM_CLEAR_IT(&htim13,TIM_IT_CC1);
    }
//Time16 Mt_2
	if(TIM16->DIER&0x0002&&__HAL_TIM_GET_FLAG(&htim16,TIM_FLAG_CC1))
	{    
        L_MotorParameter[1].PulseCount++;   
        if(HAL_GPIO_ReadPin(MOTOR2DIR_Port,MOTOR2DIR_Pin)&&L_MotorParameter[1].PulseCount%2==0)
        {
             LMt_Move_2.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR2DIR_Port,MOTOR2DIR_Pin)&&L_MotorParameter[1].PulseCount%2==0)
        {
           LMt_Move_2.MotEncoder++;  
        }   
        L_MotorSpeedDecision(2,&L_MotorParameter[1]);
        CPTime16=HAL_TIM_ReadCapturedValue(&htim16,TIM_CHANNEL_1);
        CPTime16+=L_MotorParameter[1].nowfrequency;
        __HAL_TIM_SetCompare(&htim16,TIM_CHANNEL_1,0xffff&CPTime16);
       __HAL_TIM_CLEAR_IT(&htim16,TIM_IT_CC1); 
    }    
//Time19 Mt_6
	if(TIM19->DIER&0x0004&&__HAL_TIM_GET_FLAG(&htim19,TIM_FLAG_CC2))
	{    
        R_MotorParameter[1].PulseCount++;
        if(HAL_GPIO_ReadPin(MOTOR6DIR_Port,MOTOR6DIR_Pin)&&R_MotorParameter[1].PulseCount%2==0)
        {
             RMt_Move_2.MotEncoder--;
        }
        else if(!HAL_GPIO_ReadPin(MOTOR6DIR_Port,MOTOR6DIR_Pin)&&R_MotorParameter[1].PulseCount%2==0)
        {
           RMt_Move_2.MotEncoder++;  
        }          
        R_MotorSpeedDecision(2,&R_MotorParameter[1]);          
        CPTime19=HAL_TIM_ReadCapturedValue(&htim19,TIM_CHANNEL_2);
        CPTime19+=R_MotorParameter[1].nowfrequency;
        __HAL_TIM_SetCompare(&htim19,TIM_CHANNEL_2,0xffff&CPTime19);
        __HAL_TIM_CLEAR_IT(&htim19,TIM_IT_CC2);
    }
    return 0;
}




