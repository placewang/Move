#include "MotorStep.h"
#include "MotorMove.h"
#include "MotorIo.h"
#include "CanCommand.h"

volatile MotorParameter LMt_Move_1={0};
volatile MotorParameter LMt_Move_2={0};
volatile MotorParameter LMt_Move_3={0};
volatile MotorParameter LMt_Move_4={0};

volatile MotorParameter RMt_Move_1={0};
volatile MotorParameter RMt_Move_2={0};
volatile MotorParameter RMt_Move_3={0};
volatile MotorParameter RMt_Move_4={0};

volatile MotorRunParameter MotorRunPr1;
volatile MotorRunParameter MotorRunPr2;
volatile MotorRunParameter MotorRunPr3;
volatile MotorRunParameter MotorRunPr4;
volatile MotorRunParameter MotorRunPr5;
volatile MotorRunParameter MotorRunPr6;
volatile MotorRunParameter MotorRunPr7;
volatile MotorRunParameter MotorRunPr8;

/*
电机初始化
*/
uint32_t runspeed=100*5*10;
uint32_t restspeed=100*50*1;
uint16_t runcurrent=200;   
int32_t pos1=200;
int32_t pos2=2600;
void MotorInit(void)
{
    volatile MotorRunParameter * mtp[9]={NULL,&MotorRunPr1,&MotorRunPr2,&MotorRunPr3,&MotorRunPr4,\
                                         &MotorRunPr5,&MotorRunPr6,&MotorRunPr7,&MotorRunPr8};
                                    
    for(int i=1;i<9;i++)                                       
    {
        mtp[i]->RunSpeed=runspeed;
        mtp[i]->RestSpeed=restspeed;
        mtp[i]->RunCurrent=runcurrent/2; 
        mtp[i]->Pos1=pos1;
        mtp[i]->Pos2=pos2;
        mtp[i]->offset=-30;
    }
}    

/*
回零计时
*/
void MotorHomeTimeCount(void)
{
    LMt_Move_1.HomeTimeOut++;
    LMt_Move_2.HomeTimeOut++;
    LMt_Move_3.HomeTimeOut++;
    LMt_Move_4.HomeTimeOut++;    
    
    RMt_Move_1.HomeTimeOut++;
    RMt_Move_2.HomeTimeOut++;
    RMt_Move_3.HomeTimeOut++;
    RMt_Move_4.HomeTimeOut++;     
    
}
/*
左电机状态获取装载
    num:电机编号
    sta:状态码
*/
signed char L_MotorStateGet(unsigned char num,unsigned char sta)
{
    switch(num)
    {
        case 1:
          LMt_Move_1.MoveSta=sta;    
          break;
        case 2:
          LMt_Move_2.MoveSta=sta;   
          break;
        case 3:
          LMt_Move_3.MoveSta=sta; 
          break;
        case 4:
          LMt_Move_4.MoveSta=sta;    
          break;
        case 0:
          LMt_Move_1.MoveSta=sta;  
          LMt_Move_2.MoveSta=sta;
          LMt_Move_3.MoveSta=sta;
          LMt_Move_4.MoveSta=sta;          
          break;
        default:
          break;        
    }
    return 0;
}
/*
右电机状态获取装载
    num:电机编号
    sta:状态码
*/
signed char R_MotorStateGet(unsigned char num,unsigned char sta)
{
    switch(num)
    {
        case 1:
          RMt_Move_1.MoveSta=sta;    
          break;
        case 2:
          RMt_Move_2.MoveSta=sta;   
          break;
        case 3:
          RMt_Move_3.MoveSta=sta; 
          break;
        case 4:
          RMt_Move_4.MoveSta=sta;    
          break; 
        case 0:
          RMt_Move_1.MoveSta=sta;  
          RMt_Move_2.MoveSta=sta;
          RMt_Move_3.MoveSta=sta;  
          RMt_Move_4.MoveSta=sta;          
            break; 
        default:
            break;        
    }
    return 0;
}
/*
左右模块检测电机停止状态设置锁定电流
*/
void MotorClockCurrentSet_loop(void)
{
    if(RMt_Move_1.MoveSta==0&&RMt_Move_2.MoveSta==0 \
       &&RMt_Move_3.MoveSta==0&&RMt_Move_4.MoveSta==0)
    {
        MotorCurrentSet(0,MotorRunPr5.RunCurrent/4);
    }
    else
    {
        MotorCurrentSet(0,MotorRunPr5.RunCurrent);
    }
    if(LMt_Move_1.MoveSta==0&&LMt_Move_2.MoveSta==0 \
       &&LMt_Move_3.MoveSta==0&&LMt_Move_4.MoveSta==0)
    {
           MotorCurrentSet(1,MotorRunPr1.RunCurrent/4);
    }
    else
    {
           MotorCurrentSet(1,MotorRunPr1.RunCurrent);
    }
}    
/*
左电机复位找零点
num:   电机编号
speed  回零速度
offset 偏移量
Dr:    回零方向
*/

signed char L_MotorRest(uint8_t num,uint16_t speed, int32_t  offset,uint8_t Dr)
{
    uint8_t mtsta[5]={0,MOTOR_IN1_STATE(),MOTOR_IN2_STATE(),MOTOR_IN3_STATE(),MOTOR_IN4_STATE()};
    volatile    MotorParameter *mtp[5]={NULL,&LMt_Move_1,&LMt_Move_2,&LMt_Move_3,&LMt_Move_4};
    volatile    MotorRunParameter *Mflag[5]={NULL,&MotorRunPr1,&MotorRunPr2,\
                                        &MotorRunPr3,&MotorRunPr4,};       
    if(num>4)
    {
        return -1;
    }
    if(num!=0)
    {
        if(!mtsta[num])
        {
        
           Mflag[num]->RunningFlag=HomeEnd;
           return 0;     
        }
        if(mtp[num]->HomeSta==0)
        {
            mtp[num]->HomeTimeOut=0;            
            mtp[num]->HomeSta=1;  
        }
        if(offset !=0)
        {
            mtp[num]->HomeOffset=offset;
            mtp[num]->HomeSta=2;
        }    
        L_MotorMovePos(num,speed,((pos2)+800),Dr);         
    }
    else
    {
        for(int i=1;i<5;i++)
        {
            if(!mtsta[i])
            {
                Mflag[i]->RunningFlag=HomeEnd;
                continue;     
            }
            mtp[i]->HomeSta=1;     
            mtp[i]->HomeTimeOut=0;            
            if(offset !=0)
            {
               mtp[i]->HomeOffset=offset;
               mtp[i]->HomeSta=2;   
            }
            L_MotorMovePos(i,speed,((pos2)+800),Dr); 
         }
      } 
    return 0;
}
/*
右电机复位找零点
num:   电机编号
speed  回零速度
offset 偏移量
Dr:    回零方向
*/

signed char R_MotorRest(uint8_t num,uint16_t speed,int32_t offset,uint8_t Dr)
{
    uint8_t mtsta_R[5]={0,MOTOR_IN5_STATE(),MOTOR_IN6_STATE(),MOTOR_IN7_STATE(),MOTOR_IN8_STATE()};
    volatile MotorParameter *mtp[5]={NULL,&RMt_Move_1,&RMt_Move_2,&RMt_Move_3,&RMt_Move_4};
    volatile MotorRunParameter *Mflag[5]={NULL,&MotorRunPr5,&MotorRunPr6,&MotorRunPr7,&MotorRunPr8};      
    if(num>4)
    {
        return -1;
    }
    if(num!=0)
    {
        if(!mtsta_R[num])
        {
            Mflag[num]->RunningFlag=HomeEnd;
            return 0;
        }
        if(mtp[num]->HomeSta==0)
        {
            mtp[num]->HomeTimeOut=0;            
            mtp[num]->HomeSta=1;  
        }
        if(offset !=0)
        {
            mtp[num]->HomeOffset=offset;
            mtp[num]->HomeSta=2;
        } 
        R_MotorMovePos(num,speed,((pos2)+800),Dr);        
    }
    else
    {
        for(int i=1;i<5;i++)
        {
            if(!mtsta_R[i])
            {
                Mflag[i]->RunningFlag=HomeEnd;
                continue;
            }
            mtp[i]->HomeSta=1;     
            mtp[i]->HomeTimeOut=0;            
            if(offset !=0)
            {
                mtp[i]->HomeOffset=offset;
                mtp[i]->HomeSta=2;   
            }            
            R_MotorMovePos(i,speed,((pos2)+800),Dr);         }
    }
    return 0;
}

/*
左耙子位置移动\
num:   电机编号
speed  回零速度
pos    移懂量
mode:  1:相对/0:绝对
*/

signed char L_MoveTargetPos(uint8_t num,uint16_t speed,int32_t pos,uint8_t mode)
{
   volatile MotorParameter *Mtp[5]={NULL,&LMt_Move_1,&LMt_Move_2,&LMt_Move_3,&LMt_Move_4};
   int32_t AbsoluteVal=0;
//   int32_t PosVal=0;
   int32_t  Encoder=0;
   
    if(num>4)
    {
        return -1;
    }
  
    if(num!=0)
    {  
        Mtp[num]->WorkSta=1;
        Mtp[num]->HomeTimeOut=0;  
        if(mode)
        {
            AbsoluteVal=pos<0?(-pos):pos;
            L_MotorMovePos(num,speed,AbsoluteVal,pos<0?0:1);
        }
        else
        {
//            Encoder=Mtp[num]->MotEncoder<0?(-Mtp[num]->MotEncoder):Mtp[num]->MotEncoder;
            Encoder=pos-(Mtp[num]->MotEncoder); 
            AbsoluteVal=Encoder<0?-Encoder:Encoder;
            L_MotorMovePos(num,speed,AbsoluteVal,Mtp[num]->MotEncoder>pos?0:1);
        }            
    }        
    else
    {        
        for(int i=1;i<5;i++)
        {    
            Mtp[i]->HomeTimeOut=0;
            Mtp[i]->WorkSta=1;
           if(mode)
           {
                AbsoluteVal=pos<0?(-pos):pos;
                L_MotorMovePos(i,speed,AbsoluteVal,pos<0?0:1);
           }
           else
           {
//                Encoder=Mtp[i]->MotEncoder<0?(-Mtp[i]->MotEncoder):Mtp[i]->MotEncoder;
                  Encoder=pos-(Mtp[i]->MotEncoder); 
                  AbsoluteVal=Encoder<0?-Encoder:Encoder;
                  L_MotorMovePos(i,speed,AbsoluteVal,Mtp[i]->MotEncoder>pos?0:1);
           } 
        }
    }
    return 0;
}
/*
右耙子位置移动\
num:   电机编号
speed  回零速度
pos    移懂量
mode:    回零方向
*/

signed char R_MoveTargetPos(uint8_t num,uint16_t speed,int32_t pos,uint8_t mode)
{
   volatile MotorParameter *Mtp[5]={NULL,&RMt_Move_1,&RMt_Move_2,&RMt_Move_3,&RMt_Move_4};
   int32_t AbsoluteVal=0;
//   int32_t PosVal=0;
   int32_t  Encoder=0;   
    if(num>4)
    {
        return -1;
    }
    
    if(num!=0)
    {  
        Mtp[num]->WorkSta=1;
        Mtp[num]->HomeTimeOut=0;    
        if(mode)
        {
            AbsoluteVal=pos<0?(-pos):pos;
            R_MotorMovePos(num,speed,AbsoluteVal,pos<0?0:1);
        }
        else
        {
//            Encoder=Mtp[num]->MotEncoder<0?(-Mtp[num]->MotEncoder):Mtp[num]->MotEncoder;;
            Encoder=pos-(Mtp[num]->MotEncoder); 
            AbsoluteVal=Encoder<0?-Encoder:Encoder;
            R_MotorMovePos(num,speed,AbsoluteVal,Mtp[num]->MotEncoder>pos?0:1);
        }   
    }        
    else
    {        
        for(int i=1;i<5;i++)
        {    

            Mtp[i]->HomeTimeOut=0;
            Mtp[i]->WorkSta=1;
           if(mode)
           {
                AbsoluteVal=pos<0?(-pos):pos;
                R_MotorMovePos(i,speed,AbsoluteVal,pos<0?0:1);
           }
           else
           {
//                Encoder=Mtp[i]->MotEncoder<0?(-Mtp[i]->MotEncoder):Mtp[i]->MotEncoder;
                Encoder=pos-(Mtp[i]->MotEncoder); 
                AbsoluteVal=Encoder<0?-Encoder:Encoder;
                R_MotorMovePos(i,speed,AbsoluteVal,Mtp[i]->MotEncoder>pos?0:1);
           }             
        }
    }

    return 0;
}



/*
电机回零任务
*/
void MotorHomeZeroTask_Loop(void)
{
    uint8_t mtsta[5]={0,MOTOR_IN1_STATE(),MOTOR_IN2_STATE(),MOTOR_IN3_STATE(),MOTOR_IN4_STATE()};
    uint8_t mtsta_R[5]={0,MOTOR_IN5_STATE(),MOTOR_IN6_STATE(),MOTOR_IN7_STATE(),MOTOR_IN8_STATE()};    
    volatile    MotorParameter *Home_L[5]={NULL,&LMt_Move_1,&LMt_Move_2,&LMt_Move_3,&LMt_Move_4};
    volatile    MotorParameter *Home_R[5]={NULL,&RMt_Move_1,&RMt_Move_2,&RMt_Move_3,&RMt_Move_4};
    
    uint32_t offset=0;    
    uint32_t speed=1000;
    uint8_t  time=50;
    
    for(int num=1;num<5;num++)
    {
        if(Home_L[num]->HomeSta==1&&!mtsta[num])
        {   
            L_ComparativeOutputStop(num); 
            Home_L[num]->HomeSta=0;
            Home_L[num]->MotEncoder=0;
       
        }
         //走偏移量
        else if(Home_L[num]->HomeSta==2&&!mtsta[num])
        {
            L_ComparativeOutputStop(num);             
            Home_L[num]->MotEncoder=0;            
            offset= Home_L[num]->HomeOffset<0?-(Home_L[num]->HomeOffset):Home_L[num]->HomeOffset;
            L_MotorMovePos(num,speed/2,offset,Home_L[num]->HomeOffset<0?0:1); 
            Home_L[num]->HomeSta=3;            
        }
        //偏移量走完
        else if(Home_L[num]->HomeSta==3&&Home_L[num]->MoveSta==0)
        {
             Home_L[num]->HomeSta=0;   
        }            
        //回零超时
        else if(Home_L[num]->HomeSta==1&&mtsta[num]&&Home_L[num]->HomeTimeOut>10*10*time)
        {
           Home_L[num]->HomeTimeOut=0;      
           L_ComparativeOutputStop(num); 
           Home_L[num]->HomeSta=0;
           SetRuningFlag(num,HomeEr); 
           
        }
        /***********************************************************************************************/
        if(Home_R[num]->HomeSta==1&&!mtsta_R[num])
        {   
            R_ComparativeOutputStop(num); 
            Home_R[num]->MotEncoder=0;    
            Home_R[num]->HomeSta=0;
       
        }
         //走偏移量
        else if(Home_R[num]->HomeSta==2&&!mtsta_R[num])
        {
            R_ComparativeOutputStop(num); 
            Home_R[num]->MotEncoder=0;     
            offset= Home_R[num]->HomeOffset<0?-(Home_R[num]->HomeOffset):Home_R[num]->HomeOffset;
            R_MotorMovePos(num,speed/2,offset,Home_R[num]->HomeOffset<0?0:1); 
            Home_R[num]->HomeSta=3;   
     
        }    
        //偏移量走完
        else if(Home_R[num]->HomeSta==3&&Home_R[num]->MoveSta==0)  
        {
              Home_R[num]->HomeSta=0;        
        }
        //回零超时
        else if(Home_R[num]->HomeSta==1&&mtsta_R[num]&&Home_R[num]->HomeTimeOut>10*10*time)
        {
           Home_R[num]->HomeTimeOut=0;      
           R_ComparativeOutputStop(num); 
           Home_R[num]->HomeSta=0;
           SetRuningFlag(num+3,HomeEr);  
        }
    }

}








