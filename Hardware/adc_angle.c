#include "adc_angle.h"

void get_adc_angle(ADC_HandleTypeDef* hadc,float* angle){

		HAL_ADC_Start(hadc);     //����ADCת��
		HAL_ADC_PollForConversion(hadc,5);   //�ȴ�ת����ɣ�50Ϊ���ȴ�ʱ�䣬��λΪms
	 
		uint16_t ADC_Value;
	 if(HAL_IS_BIT_SET(HAL_ADC_GetState(hadc), HAL_ADC_STATE_REG_EOC))
	 {
		ADC_Value = HAL_ADC_GetValue(hadc);   //��ȡADֵ
	 }
		*angle = ADC_Value*360.0/4095.0;


}
