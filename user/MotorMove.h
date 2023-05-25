#ifndef __MOTORIOMOVE__H
#define	__MOTORIOMOVE__H
#include "main.h"



/*
电机工作状态标志
*/
enum WorkFlag
{
    HomeEnd=1,       //回零完成
    HomeEr=4,   //回零超时
    SetOut=2,        //去休止位
    Work=3,        //到休止位    
};

/*
电机属性参数
*/
typedef struct
{
    unsigned char  MoveSta;      //电机运动状态
    unsigned char  HomeSta;      //电机回零状态
    unsigned char  WorkSta;      //电机工作状态
    unsigned short HomeTimeOut;  //回零计时
    signed int     HomeOffset;   //回零便宜量
    signed int     MotEncoder;   //软件编码器
}MotorParameter;

/*
电机运行参数
*/
typedef struct
{
    unsigned char  RunningFlag;  //运行状态标志
    unsigned short RunCurrent;   //运行电流
    unsigned int   RunSpeed;     //运行速度
    unsigned int   RestSpeed;    //复位速度
    signed int     offset;       //回零偏移量  
    signed int     Pos1;         //休止位置(准备)
    signed int     Pos2;         //耙位置(工作)    
}MotorRunParameter;


signed char L_MotorStateGet(unsigned char num,unsigned char sta);
signed char R_MotorStateGet(unsigned char num,unsigned char sta);

signed char L_MotorRest(uint8_t num,uint16_t speed,int32_t offset,uint8_t Dr);
signed char R_MotorRest(uint8_t num,uint16_t speed,int32_t offset,uint8_t Dr);
signed char L_MoveTargetPos(uint8_t num,uint16_t speed,int32_t pos,uint8_t);
signed char R_MoveTargetPos(uint8_t num,uint16_t speed,int32_t pos,uint8_t );
void MotorClockCurrentSet_loop(void);
void MotorHomeZeroTask_Loop(void);
void MotorInit(void);

extern volatile MotorParameter LMt_Move_1;
extern volatile MotorParameter LMt_Move_2;
extern volatile MotorParameter LMt_Move_3;
extern volatile MotorParameter LMt_Move_4;

extern volatile MotorParameter RMt_Move_1;
extern volatile MotorParameter RMt_Move_2;
extern volatile MotorParameter RMt_Move_3;
extern volatile MotorParameter RMt_Move_4;

extern volatile MotorRunParameter MotorRunPr1;
extern volatile MotorRunParameter MotorRunPr2;
extern volatile MotorRunParameter MotorRunPr3;
extern volatile MotorRunParameter MotorRunPr4;
extern volatile MotorRunParameter MotorRunPr5;
extern volatile MotorRunParameter MotorRunPr6;
extern volatile MotorRunParameter MotorRunPr7;
extern volatile MotorRunParameter MotorRunPr8;


extern uint32_t runspeed;
extern uint32_t restspeed;
extern uint16_t runcurrent;   
extern int32_t pos1;
extern int32_t pos2; 

#endif



