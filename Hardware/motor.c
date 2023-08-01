#include "motor.h"
#include "can.h"
#include "bsp_can.h"
const int offsetm1 = 1; //����˳ʱ��
const int offsetm2 = -1; //������ʱ��


Speed_wheel S_wheel[2]= {0};				//������

void Limit(float *a, float MAX)
{
    if (*a > MAX)
        *a = MAX;
    if (*a < -MAX)
        *a = -MAX;
}
void Wheel_Init(void)
{
    PID_struct_init(&S_wheel[0].pid_speed,POSITION_PID, 15000, 2000,
                    450.0f, 0.00f, 10.0);
    PID_struct_init(&S_wheel[0].pid_pos,POSITION_PID, 20000, 2000,
                    4.5f, 0.0f, 0.f);

    PID_struct_init(&S_wheel[1].pid_speed,POSITION_PID, 15000, 2000,
                    450.0f, 0.00f, 10.0);
    PID_struct_init(&S_wheel[1].pid_pos,POSITION_PID, 20000, 2000,
                    4.5f, 0.0f, 0.f);

}

//���õ��������ٶ�------������
void setSingleMotor_speed(uint8_t _mNum, float _mspeed)
{
    //�޷�
    //Limit(&_mspeed, ABS_MAX);
    //�ж����ĸ�����
    switch(_mNum)
    {
    case M1:
        pid_calc(&S_wheel[0].pid_speed, motor_can1[0].speed_rpm/36.0, _mspeed);
        break;
    case M2:
        pid_calc(&S_wheel[1].pid_speed, motor_can1[1].speed_rpm/36.0,-_mspeed);
        break;
    default:
        break;
    }
}

void setSingleMotor_location(uint8_t _mNum, float _mlocation)
{
    //�޷�
    //Limit(&_mspeed, ABS_MAX);
    //�ж����ĸ�����
    switch(_mNum)
    {
    case M1:
				pid_calc(&S_wheel[0].pid_pos,motor_can1[0].total_angle/819.2,_mlocation);
        pid_calc(&S_wheel[0].pid_speed, motor_can1[0].speed_rpm/36.0,S_wheel[0].pid_pos.pos_out);
        break;
    case M2:
				pid_calc(&S_wheel[1].pid_pos,motor_can1[1].total_angle/819.2,_mlocation);
        pid_calc(&S_wheel[1].pid_speed, motor_can1[1].speed_rpm/36.0,S_wheel[1].pid_pos.pos_out);
        break;
    default:
        break;
    }
}

void setMotors_location(float locationM1,float locationM2){
		setSingleMotor_location(M1, locationM1);
    setSingleMotor_location(M2, -locationM2);

    set_motor_A(&hcan1,
                S_wheel[0].pid_speed.pos_out,
                S_wheel[1].pid_speed.pos_out,
                0,
                0);


}

void setMotors_speed(float speedM1, float speedM2) //ÿ����ֵ��ٶ� ��speed����ǰ�� ���������
{
    setSingleMotor_speed(M1, speedM1);
    setSingleMotor_speed(M2, speedM2);

    set_motor_A(&hcan1,
                S_wheel[0].pid_speed.pos_out,
                S_wheel[1].pid_speed.pos_out,
                0,
                0);

}







