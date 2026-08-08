/*
 * adc_driver.h
 *
 *  Created on: 31 Tem 2026
 *      Author: Mansu
 */

#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

#include "main.h"

#define Num_of_adc_channel 		4		//ADC kanal Sayisi

#define ADC_Average_Count		64		//ornekleme miktari

#define VDDA					3300 	//mV cinsinden

#define Digital_Scale_6bits		0x3F	// 63
#define Digital_Scale_8bits		0xFF	// 255
#define Digital_Scale_10bits	0x3FF	// 1023
#define Digital_Scale_12bits	0xFFF   // 4095

#define Digital_Scale			Digital_Scale_12bits

typedef enum
{
	ADC_Channel_0 = 0,
	ADC_Channel_1 = 1,
	ADC_Channel_Temp = 2,
	ADC_Channel_Vref = 3,
	//ADC_Channel_VBAT = 4,

}ADC_Channel_name;


typedef enum
{
	DMA_Transfer_Not_Completed = 0,
	DMA_Transfer_Completed = 1,
	DMA_Transfer_not_yet_start = 2
}DMA_Transfer_Status_t;


typedef enum
{
	ADC_no_error = 0,
	ADC_Init_Start_error = 1

}ADC_error_t;


typedef struct
{
	ADC_HandleTypeDef		*hadc;

	uint16_t				ADC_convertedData[Num_of_adc_channel];

	uint32_t				adcRawSum[Num_of_adc_channel];

	uint16_t				adcAverageData[Num_of_adc_channel];
	uint8_t					adcSampleCount;

	float					ADC_VoltageData[Num_of_adc_channel];

	float					temperatura;

	float					RealVDDA;

	float					VBAT;

	DMA_Transfer_Status_t	DMATransferStatus;

	ADC_error_t				ADCErrorStatus;

	uint8_t potPercentage;
}ADC_Info_t;

void ADC_Initializaiton(ADC_Info_t *adcInfo, ADC_HandleTypeDef *hadc );

void ADC_DMA_Conversion(ADC_Info_t *adcInfo);

uint8_t MAP_Voltage_to_Percentage(float voltage, float InMin, float Inmax, uint8_t outMin, uint8_t outMax);


#endif /* INC_ADC_DRIVER_H_ */
