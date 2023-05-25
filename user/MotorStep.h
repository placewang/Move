#ifndef __MOTORIOSTEP__H
#define	__MOTORIOSTEP__H

#define TIM1COUNTCYCLE    0.000005    //计数周期



/*
加减速状态标志
*/
enum PulseSpeedFlag
{
	CompletionAcceleration=1, //加速完成（到达目标速度）
    AverageVelocity=5,        //均速    
	StartUpSpeed=3,           //开始加速
	CompleteDeceleration=2,   //减速完成（电机停）
	StartSlowDown=4,          //开始减速 
};




/*
电机加减速
属性参数
*/
typedef struct
{
	unsigned char  StateFlag;                  //过程状态标志参考 枚举PulseSpeedFlag	   
    unsigned char  DecelerationFactor;
    unsigned int   nowfrequency;               //当前频率    

    unsigned short AccelerationIn;             //加速度间隔
    unsigned short DecelerationIn;             //减速度间隔

    unsigned int   PulseCount;                 //脉冲计数
	unsigned int   PulseTargetCount;           //目标脉冲数
	unsigned int   TargetSpeed;                //目标速度		
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



