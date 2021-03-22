#pragma once
#include "Actor.h"
#include "Maze.h"


class PowerUp :	public Actor
{
public:

	PowerUp(float x, float y, float collisionRadius, int color, Maze* maze);
	~PowerUp();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

private:
	Maze* m_maze;


};

