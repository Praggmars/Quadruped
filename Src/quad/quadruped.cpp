#include <quad/quadruped.h>

namespace quad
{
Quadruped::Quadruped()
:m_legs({CreateLegRF(),CreateLegLF(),CreateLegRB(),CreateLegLB()})
{}
Leg& Quadruped::getLegRF()
{
	return m_legs[LID_RF];
}
Leg& Quadruped::getLegLF()
{
	return m_legs[LID_LF];
}
Leg& Quadruped::getLegRB()
{
	return m_legs[LID_RB];
}
Leg& Quadruped::getLegLB()
{
	return m_legs[LID_LB];
}
Leg& Quadruped::getLeg(uint32_t index)
{
	return m_legs[index];
}
std::array<Leg, 4>& Quadruped::getLegs()
{
	return m_legs;
}

} /* namespace quad */
