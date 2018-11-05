#pragma once
#ifndef QUAD_QUADRUPED_H_
#define QUAD_QUADRUPED_H_

#include <quad/leg.h>
#include <array>

namespace quad {

class Quadruped {
	std::array<Leg, 4> m_legs;

public:
	Quadruped();

	Leg& getLegRF();
	Leg& getLegLF();
	Leg& getLegRB();
	Leg& getLegLB();
	Leg& getLeg(uint32_t index);
	std::array<Leg, 4>& getLegs();
};

} /* namespace quad */

#endif /* QUAD_QUADRUPED_H_ */
