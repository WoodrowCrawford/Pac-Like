#pragma once
#include "Agent.h"
class PowerUp : public Agent
{
public:

	PowerUp(float x, float y, float collisionRadius, char icon);

	

private:

	float m_superPacPowerUp;

};

