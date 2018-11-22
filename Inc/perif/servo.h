#pragma once

#ifndef PERIF_SERVO_H_
#define PERIF_SERVO_H_

#include "cmain.h"
#include <functional>

namespace quad
{
enum TimerChannel:uint32_t
{
	CHANNEL1 = 0,
	CHANNEL2 = 1,
	CHANNEL3 = 2,
	CHANNEL4 = 3
};

struct ServoInitStruct
{
	TIM_TypeDef *timer;
	TimerChannel channel;
	float assemblyOffset;
};

class Servo
{
	TIM_TypeDef *m_timer;
	TimerChannel m_channel;
	float m_assemblyOffset;
	float_t m_state;

public:
	Servo(ServoInitStruct sis);

	void setState(float_t r);
	float_t getState();
	void Move(float_t delta);
	void Enable();
	void Disable();
};


}



#endif /* PERIF_SERVO_H_ */
