#ifndef __MOTORIOSTEP__H
#define	__MOTORIOSTEP__H

#define TIM1COUNTCYCLE    0.000005    //��������



/*
�Ӽ���״̬��־
*/
enum PulseSpeedFlag
{
	CompletionAcceleration=1, //������ɣ�����Ŀ���ٶȣ�
    AverageVelocity=5,        //����    
	StartUpSpeed=3,           //��ʼ����
	CompleteDeceleration=2,   //������ɣ����ͣ��
	StartSlowDown=4,          //��ʼ���� 
};




/*
����Ӽ���
���Բ���
*/
typedef struct
{
	unsigned char  StateFlag;                  //����״̬��־�ο� ö��PulseSpeedFlag	   
    unsigned char  DecelerationFactor;
    unsigned int   nowfrequency;               //��ǰƵ��    

    unsigned short AccelerationIn;             //���ٶȼ��
    unsigned short DecelerationIn;             //���ٶȼ��

    unsigned int   PulseCount;                 //�������
	unsigned int   PulseTargetCount;           //Ŀ��������
	unsigned int   TargetSpeed;                //Ŀ���ٶ�		
}AccelerationDeceleration;



extern unsigned int nowcount[8]; 
extern AccelerationDeceleration  L_MotorParameter[4];



signed char TIMxxComparisonInterrupt(void);
signed char L_ComparativeOutputStop(unsigned Tnum);
signed char R_ComparativeOutputStop(unsigned Tnum);
signed char L_MotorMovePos(unsigned char mtnum,unsigned int speed,signed int pos,unsigned char );
signed char R_MotorMovePos(unsigned char mtnum,unsigned int speed,signed int pos,unsigned char );
signed char L_MotorSpeedDecision(unsigned char ,AccelerationDeceleration* );
#endif



