#include "NodeGraph.h"
#include <raylib.h>
#include <deque>



std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)

	//Makes a path using A* (A star)
	std::deque<Node*> path;

	//Creates an open and closed list
	std::deque<Node*> openList;
	std::deque<Node*> closedList;

	
	//Check if the start or the goal pointer is null
	if (!start || !end)
	{
		//return path
		return path;
	}

	//Create a node pointer that will act as an iterator for the graph
	Node* currentNode = start;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the f score
		for (int i = 0;  i < openList.size(); i++)
		{
			openList[currentNode->fScore];
		}

		//Set the iterator to be the first item in the open list
		openList.push_front(currentNode);

		//Check if the iterator is pointing to the end node
		if (currentNode == end)
		{
			//Return the new path found
			return path;
		}

		//Pop the first item off the open list
		openList.pop_front();

		//Add the first item to the closed list
		closedList.push_front(currentNode);


		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* edge = end;

			//Check if the iterator is on the second end of the node
			if (currentNode == edge->previous)
			{
				//Set the edge end pointer to be the first end of the node
				edge == currentNode->previous;
			}

			//Otherwise if the iterator is on the first end of the node
			else if  (currentNode == edge)
			{
				//set the edge end pointer to be the second end of the node
				edge == currentNode->previous;
			}

			//Check if node at the end of the edge is in the closed list
		    if (closedList.front() == edge)
			{
				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float gScore = currentNode->gScore + currentNode->connections.size();

				//Create a float and set it to be the h score of the node at the end of the edge
				float hScore = edge->hScore;

				//Create a float for the f score and set it to be the g score combined with the h score
				float fScore = gScore + hScore;


				//Check if the node at the end of the edge is in the open list
				if (openList.front() == edge)
				{
					//Set the nodes g score to be the g score calculated earlier
					edge->gScore = gScore;

					//Set the nodes h score to be the h score calculated earlier
					edge->hScore = hScore;

					//Set the nodes f score to be the f score calculated earlier
					edge->fScore = fScore;

					//Set the nodes previous to be the iterator
					edge->previous = currentNode;
					
					//Add the node to the open list
					openList.push_front(edge);
				}

				//Otherwise if the f score is less than the node at the end of the edge's f score
				else if (fScore < edge->previous->fScore)
				{
					edge->visited;
					//Set its g score to be the g score calculated earlier
					edge->gScore = gScore;

					//Set the nodes h score to be the h score calculated earlier
					edge->hScore = hScore;

					//Set its f score to be the f score calculated earlier
					edge->fScore = fScore;

					//Set its previous to be the current node
					edge->previous = currentNode;
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
