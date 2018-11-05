#pragma once

#ifndef PERIF_SERVO_H_
#define PERIF_SERVO_H_

#include "cmain.h"
#include <functional>

namespace quad
{
class Servo
{
	float_t m_state;
	std::function<void(float_t)> m_pwm;

public:
	Servo(std::function<void(float_t)> pwm);
	void setState(float_t r);
	float_t getState();
	void Move(float_t delta);
};

Servo CreateServoRFbase();
Servo CreateServoLFbase();
Servo CreateServoRBbase();
Servo CreateServoLBbase();
Servo CreateServoRFshoulder();
Servo CreateServoLFshoulder();
Servo CreateServoRBshoulder();
Servo CreateServoLBshoulder();
Servo CreateServoRFknee();
Servo CreateServoLFknee();
Servo CreateServoRBknee();
Servo CreateServoLBknee();

}



#endif /* PERIF_SERVO_H_ */
