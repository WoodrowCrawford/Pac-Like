#include "PowerUp.h"
#include "raylib.h"



PowerUp::PowerUp(float x, float y, float collisionRadius, int color, Maze* maze)
{
	x = x;
	y = y;
	collisionRadius = 1;
	color = ColorToInt(PURPLE);
	m_maze = maze;
}

PowerUp::~PowerUp()
{
	
}

void PowerUp::update(float deltaTime)
{
	Actor::update(deltaTime);
}

void PowerUp::draw()
{
	Actor::draw();
}

void PowerUp::onCollision(Actor* other)
{
}
