#ifndef __MOTORIO__H
#define	__MOTORIO__H

#define MOTOR_2000MA	1600
#define MOTOR_1000MA	800 


#define MOTOR1DIR_Pin 	GPIO_PIN_5
#define MOTOR2DIR_Pin 	GPIO_PIN_1
#define MOTOR3DIR_Pin 	GPIO_PIN_8
#define MOTOR4DIR_Pin 	GPIO_PIN_14

#define MOTOR5DIR_Pin 	GPIO_PIN_10
#define MOTOR6DIR_Pin 	GPIO_PIN_2
#define MOTOR7DIR_Pin 	GPIO_PIN_5
#define MOTOR8DIR_Pin 	GPIO_PIN_8

#define MOTOR1DIR_Port  GPIOC
#define MOTOR2DIR_Port  GPIOB
#define MOTOR3DIR_Port  GPIOE
#define MOTOR4DIR_Port  GPIOB

#define MOTOR5DIR_Port  GPIOC
#define MOTOR6DIR_Port  GPIOD
#define MOTOR7DIR_Port  GPIOB
#define MOTOR8DIR_Port  GPIOB

#define MOTOREN_Port    GPIOF
#define MOTOREN_Pin  	GPIO_PIN_6

#define MOTO_TQ1_Pin 	GPIO_PIN_0
#define MOTO_TQ2_Pin 	GPIO_PIN_2
#define MOTO_TQ3_Pin 	GPIO_PIN_9
#define MOTO_TQ4_Pin 	GPIO_PIN_15
#define MOTO_TQ5_Pin 	GPIO_PIN_12
#define MOTO_TQ6_Pin 	GPIO_PIN_4
#define MOTO_TQ7_Pin 	GPIO_PIN_6
#define MOTO_TQ8_Pin 	GPIO_PIN_9

#define MOTO_TQ1_Port   GPIOB
#define MOTO_TQ2_Port   GPIOB
#define MOTO_TQ3_Port   GPIOE
#define MOTO_TQ4_Port   GPIOB
#define MOTO_TQ5_Port   GPIOC
#define MOTO_TQ6_Port   GPIOB
#define MOTO_TQ7_Port   GPIOB
#define MOTO_TQ8_Port   GPIOB

#define MOTOR_IN1_PIN  GPIO_PIN_1  
#define MOTOR_IN2_PIN  GPIO_PIN_3  
#define MOTOR_IN3_PIN  GPIO_PIN_2  
#define MOTOR_IN4_PIN  GPIO_PIN_1  
#define MOTOR_IN5_PIN  GPIO_PIN_13  
#define MOTOR_IN6_PIN  GPIO_PIN_14  
#define MOTOR_IN7_PIN  GPIO_PIN_15  
#define MOTOR_IN8_PIN  GPIO_PIN_0  

#define MOTOR_IN1_PORT GPIOA 
#define MOTOR_IN2_PORT GPIOC 
#define MOTOR_IN3_PORT GPIOC 
#define MOTOR_IN4_PORT GPIOC 
#define MOTOR_IN5_PORT GPIOC 
#define MOTOR_IN6_PORT GPIOC 
#define MOTOR_IN7_PORT GPIOC 
#define MOTOR_IN8_PORT GPIOC 

//°æºÅID
#define ID3_Pin 	GPIO_PIN_9
#define ID2_Pin 	GPIO_PIN_8
#define ID1_Pin 	GPIO_PIN_7
#define ID0_Pin 	GPIO_PIN_6

#define ID3_PORT    GPIOC
#define ID2_PORT    GPIOC
#define ID1_PORT    GPIOC
#define ID0_PORT    GPIOC

#define ID3_STATE()             HAL_GPIO_ReadPin(ID3_PORT,ID3_Pin)
#define ID2_STATE()             HAL_GPIO_ReadPin(ID2_PORT,ID2_Pin)
#define ID1_STATE()             HAL_GPIO_ReadPin(ID1_PORT,ID1_Pin)
#define ID0_STATE()             HAL_GPIO_ReadPin(ID0_PORT,ID0_Pin)


#define MOTOREN_NO()       		    HAL_GPIO_WritePin(MOTOREN_Port, MOTOREN_Pin, GPIO_PIN_SET)
#define MOTOREN_OFF()       		HAL_GPIO_WritePin(MOTOREN_Port, MOTOREN_Pin, GPIO_PIN_RESET)


#define MOTOR_IN1_STATE()             HAL_GPIO_ReadPin(MOTOR_IN1_PORT,MOTOR_IN1_PIN)
#define MOTOR_IN2_STATE()             HAL_GPIO_ReadPin(MOTOR_IN2_PORT,MOTOR_IN2_PIN)
#define MOTOR_IN3_STATE()             HAL_GPIO_ReadPin(MOTOR_IN3_PORT,MOTOR_IN3_PIN)
#define MOTOR_IN4_STATE()             HAL_GPIO_ReadPin(MOTOR_IN4_PORT,MOTOR_IN4_PIN)
#define MOTOR_IN5_STATE()             HAL_GPIO_ReadPin(MOTOR_IN5_PORT,MOTOR_IN5_PIN)
#define MOTOR_IN6_STATE()             HAL_GPIO_ReadPin(MOTOR_IN6_PORT,MOTOR_IN6_PIN)
#define MOTOR_IN7_STATE()             HAL_GPIO_ReadPin(MOTOR_IN7_PORT,MOTOR_IN7_PIN)
#define MOTOR_IN8_STATE()             HAL_GPIO_ReadPin(MOTOR_IN8_PORT,MOTOR_IN8_PIN)

signed char MotorCurrentSwitch(unsigned char num,char Dr);
signed char MotorCurrentSet(unsigned char Munm,unsigned int Cval);
signed char MotorDirSet(unsigned char Munm,char Dr);
unsigned int GetCanRevID(unsigned int BaseID);
#endif

