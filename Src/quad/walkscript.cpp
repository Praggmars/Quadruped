#include "quad/walkscript.h"
#include <cmath>

#define MIN(a, b) a<b?a:b
#define MAX(a, b) a>b?a:b

namespace quad
{
void WalkScript::AddPathElementLegMovement(LegID legid, mth::float2 pos)
{
	QuadAction qa;
	qa.legID = legid;
	qa.goalPos = pos;
	m_script.push(qa);
}
void WalkScript::AddPathElementBodyMovement(mth::float2 pos, float_t turn)
{
	QuadAction qa;
	qa.legID = -1;
	qa.goalPos = pos;
	qa.rot = turn;
	m_script.push(qa);
}

void WalkScript::AddLegTurnRightBalanced(mth::float2x2 rotmat)
{
	AddPathElementLegMovement(LID_LB, rotmat * mth::float2(-m_legXPos, -(m_legZRetracted + m_legStretchHalf)));
	AddPathElementLegMovement(LID_LF, rotmat * mth::float2(-m_legXPos, m_legZRetracted + m_legStretchHalf));
	AddPathElementLegMovement(LID_RF, rotmat * mth::float2(m_legXPos, m_legZRetracted + m_legStretchHalf));
	AddPathElementLegMovement(LID_RB, rotmat * mth::float2(m_legXPos, -(m_legZRetracted + m_legStretchHalf)));
}
void WalkScript::AddLegTurnLeftBalanced(mth::float2x2 rotmat)
{
	AddPathElementLegMovement(LID_RB, rotmat * mth::float2(m_legXPos, -(m_legZRetracted + m_legStretchHalf)));
	AddPathElementLegMovement(LID_RF, rotmat * mth::float2(m_legXPos, m_legZRetracted + m_legStretchHalf));
	AddPathElementLegMovement(LID_LF, rotmat * mth::float2(-m_legXPos, m_legZRetracted + m_legStretchHalf));
	AddPathElementLegMovement(LID_LB, rotmat * mth::float2(-m_legXPos, -(m_legZRetracted + m_legStretchHalf)));
}
void WalkScript::AddLegBodyElementsTurn(float_t angle)
{
	float_t ratio = MIN(fabsf(angle) / m_maxTurnAtOnce, 1.0f);
	if (angle < 0.0f)
		ratio = -ratio;
	mth::float2x2 rotmat = mth::float2x2::Rotation(-ratio * m_maxTurnAtOnce);
	if (m_rightBalanced)
		AddLegTurnRightBalanced(rotmat);
	else
		AddLegTurnLeftBalanced(rotmat);
	m_rightBalanced = angle > 0.0f;
	AddPathElementBodyMovement(mth::float2(), m_maxTurnAtOnce * ratio);
}

void WalkScript::AddLegWalkStraightRightBalanced(float_t ratio)
{
	AddPathElementLegMovement(LID_LB, mth::float2(-m_legXPos, -m_legZRetracted - (1.0f - ratio)*m_legStretchHalf));
	AddPathElementLegMovement(LID_LF, mth::float2(-m_legXPos, m_legZRetracted + 2.0f*m_legStretchHalf - (1.0f - ratio)*m_legStretchHalf));
	m_rightBalanced = false;
}
void WalkScript::AddLegWalkStraightLeftBalanced(float_t ratio)
{
	AddPathElementLegMovement(LID_RB, mth::float2(m_legXPos, -m_legZRetracted - (1.0f - ratio)*m_legStretchHalf));
	AddPathElementLegMovement(LID_RF, mth::float2(m_legXPos, m_legZRetracted + 2.0f*m_legStretchHalf - (1.0f - ratio)*m_legStretchHalf));
	m_rightBalanced = true;
}
void WalkScript::AddLegBodyElementsWalkStraight(float_t distance)
{
	float_t ratio = MIN(distance / m_legStretchHalf, 1.0f);
	if (m_rightBalanced)
		AddLegWalkStraightRightBalanced(ratio);
	else
		AddLegWalkStraightLeftBalanced(ratio);
	AddPathElementBodyMovement(mth::float2(0.0f, m_legStretchHalf*ratio), 0.0f);
}

WalkScript::WalkScript() :
	m_maxTurnAtOnce(mth::pi*0.25f),
	m_bellyy(0.3f),
	m_legLift(0.2f),
	m_legXPos(0.9f),
	m_legZRetracted(0.4f),
	m_legStretchHalf(0.5f),
	m_rightBalanced(true) {}

void WalkScript::AddPathElementTurn(float_t angle)
{
	float_t angleabs = fabsf(angle);
	while (angleabs > 0.0f)
	{
		AddLegBodyElementsTurn(angle);
		angleabs -= m_maxTurnAtOnce;
		if (angle > 0.0f)
			angle -= m_maxTurnAtOnce;
		else
			angle += m_maxTurnAtOnce;
	}
}

void WalkScript::AddPathElementWalkStraight(float_t distance)
{
	while (distance > 0.0f)
	{
		AddLegBodyElementsWalkStraight(distance);
		distance -= m_legStretchHalf;
	}
}

void WalkScript::Clear()
{
	m_script.clear();
}

void WalkScript::AddPathElementCircle(float_t circleR, float_t rotation)
{
	float_t rotabs = fabsf(rotation);
	float_t rotpermove = m_legStretchHalf / circleR;
	mth::float2x2 rotmat = mth::float2x2::Rotation(rotpermove);
	QuadAction qa;
	while (rotabs > 0.0f)
	{
		if (m_rightBalanced)
		{
			m_rightBalanced = false;
		}
		else
		{
			m_rightBalanced = true;
		}
		qa.goalPos = rotmat * mth::float2(0.0f, m_legStretchHalf);

		rotabs -= rotpermove;
		if (rotation > 0.0f)
			rotation -= rotpermove;
		else
			rotation += rotpermove;
	}
}
bool WalkScript::NextAction(QuadAction& action)
{
	return m_script.pop(action);
}
mth::float3 WalkScript::getLegRFStartPos()
{
	return { m_legXPos, -m_bellyy, m_legZRetracted + m_legStretchHalf };
}
mth::float3 WalkScript::getLegLFStartPos()
{
	return { -m_legXPos, -m_bellyy, m_legZRetracted + m_legStretchHalf };
}
mth::float3 WalkScript::getLegRBStartPos()
{
	return { m_legXPos, -m_bellyy, -(m_legZRetracted + m_legStretchHalf) };
}
mth::float3 WalkScript::getLegLBStartPos()
{
	return mth::float3({ -m_legXPos, -m_bellyy, -(m_legZRetracted + m_legStretchHalf) });
}
float_t WalkScript::getBellyY()
{
	return m_bellyy;
}
float_t WalkScript::LegY(float_t t)
{
	t = 2.0f*t - 1.0f;
	return -m_bellyy + (1.0f - t * t)*m_legLift;
}


void WalkManager::Init(Quadruped *quadruped)
{
	m_script.Clear();
	m_quad = quadruped;
	m_time = 0.0f;
	m_speed = 1.0f;
	m_running = false;
	m_quad->getLegRF().setPosition(m_script.getLegRFStartPos());
	m_quad->getLegRB().setPosition(m_script.getLegRBStartPos());
	m_quad->getLegLF().setPosition(m_script.getLegLFStartPos());
	m_quad->getLegLB().setPosition(m_script.getLegLBStartPos());
}

void WalkManager::MoveBody(float_t deltaTime)
{
	mth::float3 delta = { -deltaTime * m_action.goalPos.x, 0.0f, deltaTime * m_action.goalPos.y };
	delta = mth::float3x3::RotationY(m_action.rot)*delta;
	for (Leg& l : m_quad->getLegs())
		l.setPosition(mth::float3x3::RotationY(-deltaTime * m_action.rot)*(-delta + l.getPosition()));
}
void WalkManager::MoveLeg()
{
	mth::float3 pos = { m_prevAction.goalPos.x + (m_action.goalPos.x - m_prevAction.goalPos.x)*m_time,
		0.0f, m_prevAction.goalPos.y + (m_action.goalPos.y - m_prevAction.goalPos.y)*m_time };
	pos.Normalize();
	pos *= (1.0f - m_time)*m_prevAction.goalPos.Length() + m_time * m_action.goalPos.Length();
	pos.y = m_script.LegY(m_time);
	m_quad->getLeg(m_action.legID).setPosition(pos);
}
void WalkManager::ReceiveNextAction()
{
	m_running = m_script.NextAction(m_action);
	if (m_running)
	{
		if (m_action.legID >= 0)
		{
			mth::float3 prevPos = m_quad->getLeg(m_action.legID).getPosition();
			m_prevAction.goalPos.x = prevPos.x;
			m_prevAction.goalPos.y = prevPos.z;
		}
	}
}
float_t WalkManager::FinishPreviousAction(float_t timeLeft)
{
	if (m_action.legID < 0)
		MoveBody(timeLeft);
	else
		m_quad->getLeg(m_action.legID).setPosition({ m_action.goalPos.x, -m_script.getBellyY(), m_action.goalPos.y });
	ReceiveNextAction();
	m_time = fmodf(m_time, 1.0f);
	return m_time;
}
void WalkManager::ExecuteAction(float_t deltaTime)
{
	m_time += deltaTime;
	if (m_time >= 1.0f)
		deltaTime = FinishPreviousAction(1.0f - (m_time - deltaTime));
	if (m_action.legID < 0)
		MoveBody(deltaTime);
	else
		MoveLeg();
}
void WalkManager::Update(float_t deltaTime)
{
	if (!m_running)
	{
		m_script.AddPathElementWalkStraight(2.0f);
		m_script.AddPathElementTurn(-mth::pi*0.5f);

		ReceiveNextAction();
		m_time = 0.0f;
	}
	if (m_running)
		ExecuteAction(deltaTime * m_speed);
}
WalkScript& WalkManager::getWalkScript()
{
	return m_script;
}

}
