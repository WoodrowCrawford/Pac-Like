#pragma once
#include "PathfindBehavior.h"
#include "Behavior.h"
#include "NodeGraph.h"

class Maze;

//Flee behavior used for the ghost.
//Used to run away from the player
class FleeBehavior :public PathfindBehavior ::Behavior
{
public:

	FleeBehavior(Maze* maze) : m_maze(maze) {}

	virtual void update(Agent* owner, float deltaTime) override;
	virtual void draw(Agent* owner) override;

	void updatePath(Agent* owner);
	void updatePath(Agent* owner, MathLibrary::Vector2 destination);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	int getColor() { return m_color; }
	void setColor(int color) { m_color = color; }


protected:
	virtual MathLibrary::Vector2 findDestination(Agent* owner);


private:

	Maze* m_maze;
	std::deque<NodeGraph::Node*> m_path;

	Actor* m_target = nullptr;
	bool m_needPath = true;
	int m_color = 0xFFFFFFFF;
};

