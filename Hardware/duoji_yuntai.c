#include "duoji_yuntai.h"
//摄像头与平面的距离 单位mm
#define distance 100
#define pi 3.1415926
#include "usart.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "pid.h"

pid_t duoji_x;
pid_t duoji_y;
void duoji_yuntai_init(){
	
		HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
		PID_struct_init(&duoji_x,DELTA_PID,10,10,
						0.5f,0,0);
		PID_struct_init(&duoji_y,DELTA_PID,10,10,
						0.5f,0,0);
		set_yuntai_angle (0.f,135.f);

}
//angle1 范围-90---90 
//angle2 范围-135--135
void set_yuntai_angle(float angle1,float angle2)
{
     
			
			__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,(uint32_t)((angle1+90)*1.11+50));//180°舵机
      __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,(uint32_t)((angle2+135)*0.741+50)); //270°舵机            

}
void Trans(uint8_t *receive_buff, float *usart_x, float *usart_y)
{
	
	
			 HAL_UART_Receive(&huart3,receive_buff,20,0xff);

    if (receive_buff[0] != ':')
    {
        return;
    }
		
    /*在字符串 str 中从第二个字符开始解析数据，并尝试匹配格式 "%f,%f:"。如果成功解析两个浮点数并且字符串的格式是正确的（以逗号结尾），则返回值将是2*/
    if (sscanf(receive_buff + 1, "%f,%f:", usart_x,usart_y) != 2)
    {
        return;
    }
		
		float angle1_target=0;
		float angle2_target=0;
		xy2angle(usart_x,usart_y,&angle1_target,&angle2_target);
//		printf("%f,%f\n",usart_x,usart_y);
//		*angle1_target=atan(usart_x/distance)*180.0/pi;
//		*angle2_target=atan(usart_y/distance)*180.0/pi;
		
		
    memset(receive_buff,0,20);
}
void xy2angle(float *usart_x,float * usart_y,float *angle1_target,float *angle2_target){
		*angle1_target=atan(*usart_x/distance)*180.0/pi;
		*angle2_target=atan(*usart_y/distance)*180.0/pi;
		printf("%f,%f\n",*angle1_target,*angle2_target);
}

void duoji_trans_pid(float *usart_x,float * usart_y,float *angle1,float *angle2){
	static int i=0;
	pid_calc(&duoji_x,*usart_x,0);
	pid_calc(&duoji_y,*usart_y,0);
	set_yuntai_angle(*angle1+duoji_y.delta_out,*angle2+duoji_x.delta_out);
	
}





