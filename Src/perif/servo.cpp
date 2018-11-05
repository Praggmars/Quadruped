#include "perif/servo.h"

static const float_t g_PI = 3.14159265358f;

namespace quad
{
uint32_t DegToCompareValue(float_t deg, TIM_TypeDef* tim)
{
	uint32_t arr = LL_TIM_GetAutoReload(tim);
	return (arr + arr*deg / g_PI) / 20;
}
void Quad_LegRFbase(float_t deg)
{
	LL_TIM_OC_SetCompareCH4(TIM1, DegToCompareValue(deg, TIM1));
}
void Quad_LegLFbase(float_t deg)
{
	LL_TIM_OC_SetCompareCH3(TIM2, DegToCompareValue(deg, TIM2));
}
void Quad_LegRBbase(float_t deg)
{
	LL_TIM_OC_SetCompareCH1(TIM1, DegToCompareValue(deg, TIM1));
}
void Quad_LegLBbase(float_t deg)
{
	LL_TIM_OC_SetCompareCH4(TIM2, DegToCompareValue(deg, TIM2));
}
void Quad_LegRFknee(float_t deg)
{
	LL_TIM_OC_SetCompareCH2(TIM1, DegToCompareValue(deg, TIM1));
}
void Quad_LegLFknee(float_t deg)
{
	LL_TIM_OC_SetCompareCH1(TIM2, DegToCompareValue(deg, TIM2));
}
void Quad_LegRBknee(float_t deg)
{
	LL_TIM_OC_SetCompareCH3(TIM3, DegToCompareValue(deg, TIM3));
}
void Quad_LegLBknee(float_t deg)
{
	LL_TIM_OC_SetCompareCH1(TIM3, DegToCompareValue(deg, TIM3));
}
void Quad_LegRFshoulder(float_t deg)
{
	LL_TIM_OC_SetCompareCH3(TIM1, DegToCompareValue(deg, TIM1));
}
void Quad_LegLFshoulder(float_t deg)
{
	LL_TIM_OC_SetCompareCH2(TIM2, DegToCompareValue(deg, TIM2));
}
void Quad_LegRBshoulder(float_t deg)
{
	LL_TIM_OC_SetCompareCH4(TIM3, DegToCompareValue(deg, TIM3));
}
void Quad_LegLBshoulder(float_t deg)
{
	LL_TIM_OC_SetCompareCH2(TIM3, DegToCompareValue(deg, TIM3));
}

Servo CreateServoRFbase()
{
	return Servo(Quad_LegRFbase);
}
Servo CreateServoLFbase()
{
	return Servo(Quad_LegLFbase);
}
Servo CreateServoRBbase()
{
	return Servo(Quad_LegRBbase);
}
Servo CreateServoLBbase()
{
	return Servo(Quad_LegLBbase);
}
Servo CreateServoRFknee()
{
	return Servo(Quad_LegRFknee);
}
Servo CreateServoLFknee()
{
	return Servo(Quad_LegLFknee);
}
Servo CreateServoRBknee()
{
	return Servo(Quad_LegRBknee);
}
Servo CreateServoLBknee()
{
	return Servo(Quad_LegLBknee);
}
Servo CreateServoRFshoulder()
{
	return Servo(Quad_LegRFshoulder);
}
Servo CreateServoLFshoulder()
{
	return Servo(Quad_LegLFshoulder);
}
Servo CreateServoRBshoulder()
{
	return Servo(Quad_LegRBshoulder);
}
Servo CreateServoLBshoulder()
{
	return Servo(Quad_LegLBshoulder);
}


Servo::Servo(std::function<void(float_t)> pwm):m_state(0.0f), m_pwm(pwm){}

void Servo::setState(float_t r)
{
	m_state = r;
	if (m_state < -g_PI)
		m_state = -g_PI;
	else if (m_state > g_PI)
		m_state = g_PI;
	m_pwm(m_state);
}
float_t Servo::getState()
{
	return m_state;
}
void Servo::Move(float_t delta)
{
	setState(m_state + delta);
}


}
