#include "cmain.h"

uint16_t adcVal[2];
static uint8_t adcValIndex = 0;

extern uint32_t g_milliseconds;

void Transmit(USART_TypeDef* uartx, uint8_t data)
{
	while (!LL_USART_IsActiveFlag_TXE(uartx));
	LL_USART_ClearFlag_TC(uartx);
	LL_USART_TransmitData8(uartx, data);
	while (!LL_USART_IsActiveFlag_TC(uartx));
}
void Transmit(USART_TypeDef* uartx, uint8_t* data, uint32_t byteCount)
{
	for (uint32_t i = 0; i < byteCount; i++)
		Transmit(uartx, data[i]);
}

extern "C"
{
void ADC1_IT_Callback()
{
	if (LL_ADC_IsActiveFlag_EOC(ADC1))
	{
		adcVal[adcValIndex++] = LL_ADC_REG_ReadConversionData12(ADC1);
		LL_ADC_ClearFlag_EOC(ADC1);
	}
	if (LL_ADC_IsActiveFlag_EOS(ADC1))
	{
		adcValIndex=0;
		LL_ADC_ClearFlag_EOS(ADC1);
	}
}
}

void MainLoop()
{
	if (adcValIndex == 0)
		LL_ADC_REG_StartConversion(ADC1);

	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_10);
}

int main()
{
	volatile uint8_t buffer[32]{};
	volatile uint32_t pos = 0;
	Init();

	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_7);

	Transmit(USART3, (uint8_t*)"AT+GMR", 6);


	while(true)
	{
		if (g_milliseconds%1000==0)
			MainLoop();
		/*if (LL_USART_IsActiveFlag_RXNE(USART3))
		{
			buffer[pos] = LL_USART_ReceiveData8(USART3);
			Transmit(UART4, buffer[pos]);
			pos = (pos+1) & 0x1f;
		}
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_10);*/
	}
}

/*
 * interupt tiltás freertos
 * */



