#include "adc_angle.h"

void get_adc_angle(ADC_HandleTypeDef* hadc,float* angle){

		HAL_ADC_Start(hadc);     //启动ADC转换
		HAL_ADC_PollForConversion(hadc,5);   //等待转换完成，50为最大等待时间，单位为ms
	 
		uint16_t ADC_Value;
	 if(HAL_IS_BIT_SET(HAL_ADC_GetState(hadc), HAL_ADC_STATE_REG_EOC))
	 {
		ADC_Value = HAL_ADC_GetValue(hadc);   //获取AD值
	 }
		*angle = ADC_Value*360.0/4095.0;


}
