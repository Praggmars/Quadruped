#include "perif/leds.h"
#include "perif/uart.h"
#include "quad/walkscript.h"
#include "stm32l4xx_it.h"
#include "cmain.h"
#include <cmath>

void PushUps(quad::Quadruped &q)
{
	static float time = 0.0f;

	time = fmodf(time + 0.02f, mth::pi*2.0f);
	float lift = sinf(time)*0.1f - 0.35f;

	q.getLegRF().setPosition(mth::float3(0.9f, lift, 0.9f));
	q.getLegLF().setPosition(mth::float3(-0.9f, lift, 0.9f));
	q.getLegRB().setPosition(mth::float3(0.9f, lift, -0.9f));
	q.getLegLB().setPosition(mth::float3(-0.9f, lift, -0.9f));
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

	//q.EnableLegs();
	/*while(true)
	{
		float sh = 0.7f, kn = 1.3f;
		q.getLegLF().setJointStates(mth::float3(mth::pi*0.25f, sh, kn));
		q.getLegLB().setJointStates(mth::float3(-mth::pi*0.25f, sh, kn));
		q.getLegRF().setJointStates(mth::float3(-mth::pi*0.25f, 0.0f, kn));
		q.getLegRB().setJointStates(mth::float3(mth::pi*0.25f, sh, kn));
	}*/

	uint8_t ledVar = 0;
	uint32_t counter = 0;
	while(true)
	{
		if (TryUpdate())
		{
			LL_ADC_REG_StartConversion(ADC1);

			walkm.Update(0.02f);
			if (++counter == 25)
			{
				counter = 0;
				ledVar++;
				quad::LED1SetTo((ledVar & 3) == 0);
				quad::LED2SetTo(ledVar & 1);
				quad::LED3SetTo((ledVar & 3) == 2);
			}
		}
	}
}




