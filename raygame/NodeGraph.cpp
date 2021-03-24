#include "NodeGraph.h"
#include <raylib.h>
#include <deque>










std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)\

	//Makes a path using A* (A star)
	std::deque<Node*> path;
	std::deque<Node*> openList;
	std::deque<Node*> closedList;

	
	if (!start || !end)
	{
		return path;
	}
	Node* currentNode = start;
	
	openList.push_front(start);
	
	while (!openList.empty())
	{
		for (int i = 0; i < currentNode->fScore; i++)
		{
			currentNode->fScore;
		}
		openList.push_front(currentNode);
		
		if (currentNode == end)
		{
			return path;
		}

		openList.pop_front();
		closedList.push_front(currentNode);

		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			Node* goal = end;
			Edge* cost = nullptr;
			if (goal == end->previous->previous)
			{
				goal = goal->previous;
			}
			else if (goal = end->previous)
			{
				goal = end->previous->previous;
			}

			if (goal = closedList[i])
			{
				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float gScore = goal->gScore + cost->cost;

				//Create a float and set it to be the h score of the node at the end of the edge
				float hScore = cost->cost;
				 
				//Create a float for the f score and set it to be the g score combined with the h score
				float fScore = gScore + hScore;

				if (goal = openList[i])
				{
					
					//Set the nodes g score to be the g score calculated earlier
					goal->gScore = gScore;

					//Set the nodes h score to be the h score calculated earlier
					goal->hScore = hScore;

					//Set the nodes f score to be the f score calculated earlier
					goal->fScore = fScore;

					//Set the nodes previous to be the iterator
					goal->previous = currentNode;

					//Add the node to the open list
					goal = openList[i];
				}

				else if (fScore < goal->fScore)
				{

					//Set its g score to be the g score calculated earlier
					gScore = goal->gScore;

					//Set the nodes h score to be the h score calculated earlier
					hScore = goal->hScore;

					//Set its f score to be the f score calculated earlier
					fScore = goal->fScore;
					 
					//Set its previous to be the current node
					goal->previous = currentNode;
				}
			}
			
		}

	}
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}
