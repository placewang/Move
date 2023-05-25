#include "can.h"
#include "queue.h"
#include "MotorIo.h"
#include "MotorMove.h"

/*
电机运行状态赋值
num:电机编号（1-8）0:全部
flag:标志
*/

void  SetRuningFlag(uint8_t num,uint8_t flag)
{
    volatile  MotorRunParameter *Mflag[9]={NULL,&MotorRunPr1,&MotorRunPr2,\
                                        &MotorRunPr3,&MotorRunPr4,&MotorRunPr5,\
                                        &MotorRunPr6,&MotorRunPr7,&MotorRunPr8 };                              
                                          
    if(num!=0)
    {
        Mflag[num]->RunningFlag=flag;
    }
    else
    {
        for(int i=1;i<9;i++)
        {
            Mflag[i]->RunningFlag=flag;            
        }
    }
}

/*
设置电流
*/
int8_t  SetCurrent(uint8_t* dat)
{
    uint16_t val=0;
    val = dat[2];
    val|=dat[3]<<8;
    if(val>3300)
    {
        val=3300;
    }
    else if(val==0)
    {
      return 0;  
    }
    MotorRunPr1.RunCurrent=val/2;
    MotorRunPr5.RunCurrent=val/2;        
    return 1;
}


/*
回零
*/
int8_t HomeZero(uint8_t * pta)
{
    if(pta[2]==0)
    {
        L_MotorRest(0,MotorRunPr1.RestSpeed,MotorRunPr1.offset,pta[3]==0?0:1);
        R_MotorRest(0,MotorRunPr5.RestSpeed,MotorRunPr5.offset,pta[3]==0?0:1); 
        SetRuningFlag(0,HomeEnd);        
    }
    else if(pta[2]<=4&&pta[2]!=0)
    {
        L_MotorRest(pta[2],MotorRunPr1.RestSpeed,MotorRunPr1.offset,pta[3]==0?0:1);    
        SetRuningFlag(pta[2],HomeEnd);  
    }
    else if(pta[2]>4)
    {
        R_MotorRest(pta[2]-4,MotorRunPr5.RestSpeed,MotorRunPr5.offset,pta[3]==0?0:1);
        SetRuningFlag(pta[2],HomeEnd);      
    }
        
    return 0;
}
/*
走位置
*/
int8_t MovePos(uint8_t * ptm)
{
    if(ptm[2]==0&&ptm[3]==0)
    {
        L_MoveTargetPos(0,MotorRunPr1.RunSpeed,MotorRunPr1.Pos1,0);
        R_MoveTargetPos(0,MotorRunPr5.RunSpeed,MotorRunPr5.Pos1,0); 
        SetRuningFlag(0,SetOut);  
    }
    else if(ptm[2]==0&&ptm[3]!=0)
    {
        L_MoveTargetPos(0,MotorRunPr1.RunSpeed,MotorRunPr1.Pos2,0);
        R_MoveTargetPos(0,MotorRunPr5.RunSpeed,MotorRunPr5.Pos2,0);  
        SetRuningFlag(0,Work);      
    }
    //
    else if(ptm[2]<=4&&ptm[3]==0)
    {
        L_MoveTargetPos(ptm[2],MotorRunPr1.RunSpeed,MotorRunPr1.Pos1,0);
        SetRuningFlag(ptm[2],SetOut);          
    }
    else if(ptm[2]<=4&&ptm[3]!=0)
    {
        L_MoveTargetPos(ptm[2],MotorRunPr1.RunSpeed,MotorRunPr1.Pos2,0);
        SetRuningFlag(ptm[2],Work);      
    }    
    //
    else if(ptm[2]>4&&ptm[3]==0)
    {
        R_MoveTargetPos(ptm[2]-4,MotorRunPr5.RunSpeed,MotorRunPr5.Pos1,0); 
        SetRuningFlag(ptm[2],SetOut);      
    }
    else if(ptm[2]>4&&ptm[3]!=0)
    {
        R_MoveTargetPos(ptm[2]-4,MotorRunPr5.RunSpeed,MotorRunPr5.Pos2,0); 
        SetRuningFlag(ptm[2],Work);        
    }    
    return 0;
}
/*
传感器状态返回
*/
void SensorStatusReturn(void)
{
    uint8_t canval[3]={0x08,0x05,0};
    canval[2]|=MOTOR_IN1_STATE()<<0;
    canval[2]|=MOTOR_IN2_STATE()<<1;
    canval[2]|=MOTOR_IN3_STATE()<<2;
    canval[2]|=MOTOR_IN4_STATE()<<3;
    canval[2]|=MOTOR_IN5_STATE()<<4;
    canval[2]|=MOTOR_IN6_STATE()<<5;
    canval[2]|=MOTOR_IN7_STATE()<<6;
    canval[2]|=MOTOR_IN8_STATE()<<7;    
    CAN1_Send_Msg(canval,3,GetCanRevID(CANSendID));
}

/*
电流开关设置
*/
void CurrentSwitch(uint8_t * pcs)
{
    if(pcs[2]==0)
    {
        for(int i=1;i<9;i++)
        {
            MotorCurrentSwitch(i,pcs[3]!=0?1:0);
        }
    }
    else
    {
       MotorCurrentSwitch(pcs[2],pcs[3]!=0?1:0); 
    }
}
/*
电机状态上报
*/
int8_t MotorStaReport(void)
{
    volatile    MotorParameter *Motor[9]={NULL,&LMt_Move_1,&LMt_Move_2,&LMt_Move_3,&LMt_Move_4,\
                                               &RMt_Move_1,&RMt_Move_2,&RMt_Move_3,&RMt_Move_4};
    volatile  MotorRunParameter *Flag[9]={NULL,&MotorRunPr1,&MotorRunPr2,&MotorRunPr3,&MotorRunPr4,\
                                               &MotorRunPr5,&MotorRunPr6,&MotorRunPr7,&MotorRunPr8 }; 

    uint8_t staval[4]={0x08,0x0a};                                           
    for(int i=1;i<9;i++)                                            
    {
        if(Motor[i]->MoveSta==0&&Flag[i]->RunningFlag==HomeEnd)
        {
                staval[2]=i;
                staval[3]=0;
                CAN1_Send_Msg(staval,4,GetCanRevID(CANSendID ));
                SetRuningFlag(i,0);   
        }
        else if(Motor[i]->MoveSta==0&&Flag[i]->RunningFlag==HomeEr)
        {
                staval[2]=i;
                staval[3]=0x10;
                CAN1_Send_Msg(staval,4,GetCanRevID(CANSendID ));
                SetRuningFlag(i,0);   
        }        
        
        else if(Motor[i]->MoveSta==0&&Flag[i]->RunningFlag==Work)
        {
                staval[2]=i;
                staval[3]=0x02;
                CAN1_Send_Msg(staval,4,GetCanRevID(CANSendID ));
                SetRuningFlag(i,0);
        }
        else if(Motor[i]->MoveSta==0&&Flag[i]->RunningFlag==SetOut)
        {
                staval[2]=i;
                staval[3]=0x01;
                CAN1_Send_Msg(staval,4,GetCanRevID(CANSendID ));
                SetRuningFlag(i,0);
        }
    }                                                                                   
    return 0;
}

/*
can命令接收解析
*/
int8_t  CanCmdRevAnalysis(void)
{
    ElemType Dat={0};

    if(DeQueue(&Can1_revQueuebuff, &Dat))
    {
        //设置运行电流
        if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x01)
        {                
            
            runcurrent=*((uint16_t *)(&Dat.RxData[2]));
            MotorInit(); 
//            SetCurrent(Dat.RxData);
        }
        //传感器状态返回
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x05)
        {
            SensorStatusReturn();            
        }
        //电机禁能
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x02&&Dat.RxData[2]==0)
        {
           MOTOREN_OFF();   
        }
        //电机使能
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x02&&Dat.RxData[2]!=0)
        {
           MOTOREN_NO();   
        }   
        //电机回零
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x03&&Dat.RxData[2]<=8)
        {
            HomeZero(Dat.RxData);
        }      
        //走位置(工作模式)
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x04&&Dat.RxData[2]<=8)
        {            
            MovePos(Dat.RxData);
        }
        // 电机电流开关   
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x07&&Dat.RxData[2]<=8)
        {
            CurrentSwitch(Dat.RxData);        
        }
        //运行速度
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x06&&Dat.RxData[2]==0x01)
        {
            runspeed =Dat.RxData[3];
            runspeed|=Dat.RxData[4]<<8;
            MotorInit();
        }
        //复位速度
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x06&&Dat.RxData[2]==0x02)
        {
            restspeed =Dat.RxData[3];
            restspeed |=Dat.RxData[4]<<8;
            MotorInit();        
        }
        //休止位置
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x06&&Dat.RxData[2]==0x03)
        {
            pos1 =Dat.RxData[3];
            pos1|=Dat.RxData[4]<<8;
            pos1 |=Dat.RxData[5]<<16;
            pos1|=Dat.RxData[6]<<24;            
            MotorInit();                     
        }
        //耙子位置
        else if(Dat.RxData[0]==0x08&&Dat.RxData[1]==0x06&&Dat.RxData[2]==0x04)
        {
            pos2 =Dat.RxData[3];
            pos2|=Dat.RxData[4]<<8;
            pos2 |=Dat.RxData[5]<<16;
            pos2|=Dat.RxData[6]<<24;            
            MotorInit();                     
        }        
    }
    MotorStaReport();
    return 0;
}



