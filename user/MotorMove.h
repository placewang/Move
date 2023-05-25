#ifndef __MOTORIOMOVE__H
#define	__MOTORIOMOVE__H
#include "main.h"



/*
�������״̬��־
*/
enum WorkFlag
{
    HomeEnd=1,       //�������
    HomeEr=4,   //���㳬ʱ
    SetOut=2,        //ȥ��ֹλ
    Work=3,        //����ֹλ    
};

/*
������Բ���
*/
typedef struct
{
    unsigned char  MoveSta;      //����˶�״̬
    unsigned char  HomeSta;      //�������״̬
    unsigned char  WorkSta;      //�������״̬
    unsigned short HomeTimeOut;  //�����ʱ
    signed int     HomeOffset;   //���������
    signed int     MotEncoder;   //���������
}MotorParameter;

/*
������в���
*/
typedef struct
{
    unsigned char  RunningFlag;  //����״̬��־
    unsigned short RunCurrent;   //���е���
    unsigned int   RunSpeed;     //�����ٶ�
    unsigned int   RestSpeed;    //��λ�ٶ�
    signed int     offset;       //����ƫ����  
    signed int     Pos1;         //��ֹλ��(׼��)
    signed int     Pos2;         //��λ��(����)    
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



