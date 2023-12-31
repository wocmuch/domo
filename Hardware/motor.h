#ifndef _MOTER_H
#define _MOTER_H

#include "pid.h"


#define M1 1
#define M2 2
#define M3 3
#define M4 4

#define M5 5
#define M6 6
#define M7 7
#define M8 8
#define MAll 9


typedef struct
{
    int id;
    pid_t pid_pos; //每个舵轮转向的位置环
    pid_t pid_speed;  //每个舵轮的速度环
    float speed;      //运行速度
    float rpm;        //转多少圈
} Speed_wheel;



void Wheel_Init(void);

void setSingleMotor_speed(uint8_t _mNum, float _mspeed);  //设置单个轮子速度------驱动轮
//设置底盘轮子速度
void setMotors_speed(float speedM1, float speedM2);
void setMotors_location(float locationM1,float locationM2);//每个堵值乃俣� 正speed代表前进 负代表后退
void setSingleMotor_location(uint8_t _mNum, float _mlocation);

#endif
