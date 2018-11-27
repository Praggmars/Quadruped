#include "perif/leds.h"
#include "cmain.h"

namespace quad
{
void LED1On()
{
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_10);
}
void LED1Off()
{
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10);
}
void LED1Toggle()
{
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_10);
}
void LED1SetTo(bool on)
{
	if (on)
		LED1On();
	else
		LED1Off();
}

void LED2On()
{
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_11);
}
void LED2Off()
{
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_11);
}
void LED2Toggle()
{
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_11);
}
void LED2SetTo(bool on)
{
	if (on)
		LED2On();
	else
		LED2Off();
}

void LED3On()
{
	LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
}
void LED3Off()
{
	LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);
}
void LED3Toggle()
{
	LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_3);
}
void LED3SetTo(bool on)
{
	if (on)
		LED3On();
	else
		LED3Off();
}

void LEDAccuOn()
{
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
}
void LEDAccuOff()
{
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
}
void LEDAccuToggle()
{
	LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_12);
}
void LEDAccuSetTo(bool on)
{
	if (on)
		LEDAccuOn();
	else
		LEDAccuOff();
}
}
