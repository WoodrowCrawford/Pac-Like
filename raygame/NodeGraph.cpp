#include "NodeGraph.h"
#include <raylib.h>
#include <deque>










std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{

	std::deque<Node*> path;


	//Create a node pointer that points to the start node
	Node* begin = start;

	//Create a node pointer that points to the goal node
	Node* finish = end;

	//Check if the start or the goal pointer is null
	if (!begin || !finish)
	{
		//return an empty list
		return path;
	}

		//return an empty list
	//end if statement

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = nullptr;

	//Create an open list
	std::deque<Node*> openList;

	//Create a closed list
	std::deque<Node*> closedList;


	//Add start to the open list
	openList.push_front(start);



	//Loop while the open list is not empty
	while (!openList.size())
	{
		for (int i = 0; i < openList.size(); i++)
		{

			//Sort the items in the open list by the g score
			currentNode->gScore;

		//Set the iterator to be the first item in the open list
			currentNode = openList[0];


		//Check if the iterator is pointing to the goal node
			if (currentNode == finish)
			{
			
				//Return the new path found
				return path;
			}

			//Pop the first item off the open list
			openList.pop_back();

			//Add the first item to the closed list
			closedList.push_front(currentNode);

			for (int i = 0; i < currentNode->connections.size(); i++)
			{
				Node* otherEdge = nullptr;

				if (currentNode == currentNode->connections[i].target->connections[i].target)
				{
					//Set the edge end pointer to be the first end of the node
					otherEdge == currentNode->connections[i].target;
				}

				//Otherwise if the iterator is on the first end of the node...
				else if (currentNode == currentNode->connections[i].target)
				{
					//set the edge end pointer to be the second end of the node
					otherEdge == currentNode->connections[i].target->connections[i].target;
					
				}

				if (otherEdge == closedList[i])
				{
					int gScore = currentNode->gScore + otherEdge->connections[i].cost;
				

					if (otherEdge == openList[i])
					{
						currentNode->gScore = gScore;

						currentNode->previous = currentNode;

						openList.push_front(currentNode);
					}

					else if (gScore < otherEdge->gScore)
					{
						otherEdge->gScore = gScore;

						otherEdge->previous = currentNode;
					}
				}
			}
		}
	}



		


			

		

	return path;
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
