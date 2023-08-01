#ifndef __BSP_CAN
#define __BSP_CAN

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#elif defined STM32F1
#include "stm32f1xx_hal.h"
#endif


#include "mytype.h"
#include "can.h"

/*CAN发送或是接收的ID*/
typedef enum {

    CAN_Motor_ALL_ID = 0x200,
    CAN_Motor1_ID = 0x201,
    CAN_Motor2_ID = 0x202,
    CAN_Motor3_ID = 0x203,
    CAN_Motor4_ID = 0x204,

    CAN_Motor_ALL_ID2 = 0x1FF,
    CAN_Motor5_ID = 0x205,
    CAN_Motor6_ID = 0x206,
    CAN_Motor7_ID = 0x207,
    CAN_Motor8_ID = 0x208,

} CAN_Message_ID;

#define FILTER_BUF_LEN        5
/*接收到的电机的参数结构体*/
typedef struct {
    int16_t speed_rpm;  //转速
    float real_current;
    int16_t given_current;  // 扭矩
    uint8_t temperature;
    uint16_t angle;             //abs angle range:[0,8191] 角度范围[0,8191]
    uint16_t last_angle;        //abs angle range:[0,8191]
    uint16_t offset_angle;
    int32_t round_cnt;        //电机转的圈数
    int32_t total_angle;    //当前总角度 圈数
    u8 buf_idx;
    u16 angle_buf[FILTER_BUF_LEN];
    u16 fited_angle;     //修正角度？
    u32 msg_cnt;          //?
} motor_measure_t;

/* Extern  ------------------------------------------------------------------*/
extern motor_measure_t motor_can1[];
extern motor_measure_t motor_can2[];


void my_can_filter_init_recv_all(CAN_HandleTypeDef *_hcan);

void can_filter_recv_special(CAN_HandleTypeDef *_hcan);

void get_motor_measure(motor_measure_t *ptr, uint8_t Rx_Data[]);

int32_t get_total_angle(motor_measure_t *p);

void get_motor_offset(motor_measure_t *ptr, uint8_t Data[]);

void can_receive_onetime(CAN_HandleTypeDef *_hcan, int time);

void set_motor_A(CAN_HandleTypeDef *_hcan, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);

void set_motor_B(CAN_HandleTypeDef *_hcan, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);

void set_motor(CAN_HandleTypeDef *_hcan,
               int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4,
               int16_t iq5, int16_t iq6, int16_t iq7, int16_t iq8);

#endif
