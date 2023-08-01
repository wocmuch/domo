#ifndef __DUOJI_YUNTAI_H__
#define __DUOJI_YUNTAI_H__

#include "main.h"
#include "tim.h"


void duoji_yuntai_init();

void set_yuntai_angle(float angle1,float angle2);

void Trans(uint8_t *receive_buff, float *angle1_target, float *angle2_target);

void xy2angle(float *usart_x,float * usart_y,float *angle1_target,float *angle2_target);

void duoji_trans_pid(float *usart_x,float * usart_y,float *angle1,float *angle2);
#endif
