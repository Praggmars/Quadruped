#pragma once
#ifndef WALKSCRIPT_H_
#define WALKSCRIPT_H_

#include "quad/quadruped.h"
#include "util/fifo.h"

namespace quad
{
struct QuadAction
{
	uint32_t legID;
	mth::float2 goalPos;
	float_t rot;
};

class WalkScript
{
	float_t m_maxTurnAtOnce;
	float_t m_bellyy;
	float_t m_legLift;
	float_t m_legXPos;
	float_t m_legZRetracted;
	float_t m_legStretchHalf;
	bool m_rightBalanced;
	util::fifo<QuadAction, 64> m_script;

private:
	void AddPathElementLegMovement(LegID legid, mth::float2 pos);
	void AddPathElementBodyMovement(mth::float2 pos, float_t turn);
	void AddLegTurnRightBalanced(mth::float2x2 rotmat);
	void AddLegTurnLeftBalanced(mth::float2x2 rotmat);
	void AddLegBodyElementsTurn(float_t angle);
	void AddLegWalkStraightRightBalanced(float_t ratio);
	void AddLegWalkStraightLeftBalanced(float_t ratio);
	void AddLegBodyElementsWalkStraight(float_t distance);

public:
	WalkScript();
	void AddPathElementTurn(float_t angle);
	void AddPathElementWalkStraight(float_t distance);
	void AddPathElementCircle(float_t circleR, float_t rotation);
	void Clear();
	bool NextAction(QuadAction& action);
	mth::float3 getLegRFStartPos();
	mth::float3 getLegLFStartPos();
	mth::float3 getLegRBStartPos();
	mth::float3 getLegLBStartPos();
	float_t getBellyY();
	float_t LegY(float_t t);
};

class WalkManager
{
	float_t m_time;
	float_t m_speed;
	WalkScript m_script;
	Quadruped *m_quad;
	QuadAction m_action;
	QuadAction m_prevAction;
	bool m_running;

private:
	void MoveBody(float_t deltaTime);
	void MoveLeg();
	void ReceiveNextAction();
	float_t FinishPreviousAction(float_t timeLeft);
	void ExecuteAction(float_t deltaTime);

public:
	void Init(Quadruped *quadruped);
	void Update(float_t deltaTime);
	WalkScript& getWalkScript();
};
}

#endif /* WALKSCRIPT_H_ */
