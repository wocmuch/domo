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
    pid_t pid_pos; //Ã¿¸ö¶æÂÖ×ªÏòµÄÎ»ÖÃ»·
    pid_t pid_speed;  //Ã¿¸ö¶æÂÖµÄËÙ¶È»·
    float speed;      //ÔËĞĞËÙ¶È
    float rpm;        //×ª¶àÉÙÈ¦
} Speed_wheel;



void Wheel_Init(void);

void setSingleMotor_speed(uint8_t _mNum, float _mspeed);  //ÉèÖÃµ¥¸öÂÖ×ÓËÙ¶È------Çı¶¯ÂÖ
//ÉèÖÃµ×ÅÌÂÖ×ÓËÙ¶È
void setMotors_speed(float speedM1, float speedM2);
void setMotors_location(float locationM1,float locationM2);//Ã¿¸ö¶ÂÖµÄËÙ¶È Õıspeed´ú±íÇ°½ø ¸º´ú±íºóÍË
void setSingleMotor_location(uint8_t _mNum, float _mlocation);

#endif
