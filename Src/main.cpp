#include "cmain.h"
#include "quad/walkscript.h"
#include <cmath>

uint16_t adcVal[2];
static uint8_t adcValIndex = 0;

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
uint8_t TryUpdate();
}

int main()
{
	Init();

	quad::Quadruped q;
	quad::WalkManager walkm;

	q.getLegRF().setPosition(mth::float3(0.9f, -0.35f, 0.9f));
	q.getLegLF().setPosition(mth::float3(-0.9f, -0.35f, 0.9f));
	q.getLegRB().setPosition(mth::float3(0.9f, -0.35f, -0.9f));
	q.getLegLB().setPosition(mth::float3(-0.9f, -0.35f, -0.9f));

	walkm.Init(&q);

	q.EnableLegs();

	uint32_t counter = 0;
	float time = 0.0f;
	while(true)
	{

		if (TryUpdate())
		{
			time = fmodf(time + 0.02f, mth::pi*2.0f);
			float lift = sinf(time)*0.1f - 0.35f;

			q.getLegRF().setPosition(mth::float3(0.9f, lift, 0.9f));
			q.getLegLF().setPosition(mth::float3(-0.9f, lift, 0.9f));
			q.getLegRB().setPosition(mth::float3(0.9f, lift, -0.9f));
			q.getLegLB().setPosition(mth::float3(-0.9f, lift, -0.9f));
			//walkm.Update(0.02f);
			if (++counter == 50)
			{
				counter = 0;
				//walkm.Update(1.0f);
				LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_10);
			}
		}

		/*for (volatile uint32_t i = 0; i < 10000000; i++);
		LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_10);
		for (volatile uint32_t i = 0; i < 10000000; i++);
		LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10);*/
	}
}




