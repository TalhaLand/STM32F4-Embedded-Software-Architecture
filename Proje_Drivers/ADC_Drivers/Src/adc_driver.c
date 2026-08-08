/*
 * adc_driver.c
 *
 *  Created on: 31 Tem 2026
 *      Author: Mansu
 */


#include "adc_driver.h"

DMA_Transfer_Status_t globalTransferStatus  = DMA_Transfer_not_yet_start;

void ADC_Initializaiton(ADC_Info_t *adcInfo, ADC_HandleTypeDef *hadc)
{
	adcInfo->hadc = hadc;


	adcInfo->ADCErrorStatus = ADC_no_error;

	for(int i = 0; i < Num_of_adc_channel; i++)
	{
		adcInfo->ADC_convertedData[i] 	= 0;
		adcInfo->ADC_VoltageData[i] 	= 0;
		adcInfo->adcRawSum[i] 			= 0;
	}

	adcInfo->adcSampleCount 			= 0;

	adcInfo->DMATransferStatus 			= globalTransferStatus;

		if(HAL_ADC_Start_DMA(adcInfo->hadc, (uint32_t*)adcInfo->ADC_convertedData, Num_of_adc_channel) != HAL_OK)
		{
			adcInfo->ADCErrorStatus = ADC_Init_Start_error;
		}
	{

	}


}


void ADC_DMA_Conversion(ADC_Info_t *adcInfo)
{
	adcInfo->DMATransferStatus = globalTransferStatus;

	if(adcInfo->DMATransferStatus == DMA_Transfer_Completed)
	{
		globalTransferStatus = DMA_Transfer_Not_Completed;

		for(int i = 0; i< Num_of_adc_channel; i++)
		{
			adcInfo->adcRawSum[i] += adcInfo->ADC_convertedData[i];

		}

		adcInfo->adcSampleCount +=1;

		if(adcInfo->adcSampleCount > ADC_Average_Count)
		{
			adcInfo->adcSampleCount =0;

			for(int i = 0; i< Num_of_adc_channel; i++)
			{
				adcInfo->adcAverageData[i] = adcInfo->adcRawSum[i] / ADC_Average_Count;

				adcInfo->adcRawSum[i] = 0;
			}
			adcInfo->RealVDDA = 			__LL_ADC_CALC_VREFANALOG_VOLTAGE(adcInfo->adcAverageData[ADC_Channel_Vref], Digital_Scale);

			adcInfo->temperatura =		__LL_ADC_CALC_TEMPERATURE(adcInfo->RealVDDA, adcInfo->adcAverageData[ADC_Channel_Temp],Digital_Scale);

			for(int i = 0; i < Num_of_adc_channel; i++)
			{
				adcInfo->ADC_VoltageData[i] = (float)__LL_ADC_CALC_DATA_TO_VOLTAGE(adcInfo->RealVDDA, adcInfo->adcAverageData[i], Digital_Scale) / 1000.0;

			}

			//adcInfo->VBAT = 			adcInfo->ADC_VoltageData[]

			adcInfo->potPercentage	=	MAP_Voltage_to_Percentage(adcInfo->ADC_VoltageData[ADC_Channel_0], 0.0, 3.3, 0, 100);

		}


	}
}


uint8_t MAP_Voltage_to_Percentage(float voltage, float InMin, float Inmax, uint8_t outMin, uint8_t outMax)
{
	uint8_t percenstage = 0;
	percenstage = ((voltage - InMin) * (outMax-outMin) / (Inmax- InMin) + outMin);

	return percenstage;
}

__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{	//ADC tamamlandıgında üretiyor
  //DMA Transfer Status Completed
	globalTransferStatus = DMA_Transfer_Completed;
}

__weak void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	 //DMA Transfer Status not Completed
	globalTransferStatus = DMA_Transfer_Not_Completed;

}
