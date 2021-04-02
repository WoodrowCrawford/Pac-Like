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
	if (!begin|| !finish)
	{
		//return an empty list
		return path;
	}

	//Set the start nodes color to be green

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
		//Sort the items in the open list by the g score
		for (int i = 0; i < openList.size(); i++)
		{
			currentNode->gScore;

			//Set the iterator to be the first item in the open list
			currentNode = openList[0];

			//Check if the iterator is pointing to the goal node
			if (currentNode == finish)
			{
				//Return the new path found
				return path;
				 

			}
			//end if statement


			//Pop the first item off the open list
			openList.pop_back();
			
			//Add the first item to the closed list
			closedList.push_front(currentNode);


		//Loop through all of the edges for the iterator
			for (int j = 0; j < currentNode->connections.size(); j++)
			{
				//Create a node pointer to store the other end of the edge
				Node* otheredge = nullptr;

				//Check if the iterator is on the second end of the node
				if (currentNode == currentNode->connections[j].connectedNode2)
				{
					//Set the edge end pointer to be the first end of the node
					otheredge == currentNode->connections[j].connectedNode1;
					
					//Otherwise if the iterator is on the first end of the node...
					if (currentNode == currentNode->connections[j].connectedNode1)
					{
						//set the edge end pointer to be the second end of the node
						otheredge == currentNode->connections[j].connectedNode2;
					}
					// end if statement
				
					//Check if node at the end of the edge is in the closed list
					if (otheredge == closedList[i])
					{
						//Create an int and set it to be the g score of the iterator plus the cost of the edge
						int gScore = currentNode->gScore + otheredge->connections[j].cost;

						//Check if the node at the end ofthe edge is in the open list
						if (otheredge == openList[i])
						{
							//Mark the node as visited by changing its color
							 
							//Set the nodes g score to be the g score calculated earlier
							currentNode->gScore = gScore;
						 
							//Set the nodes previous to be the iterator
							currentNode->previous = currentNode;
							
							//Add the node to the open list
							openList.push_front(currentNode);


							//Otherwise if the g score is less than the node at the end of the edge's g score...
							if (gScore < otheredge->gScore)
							{
								
								//Mark the node as visited by changing its color
								 
								//Set its g score to be the g score calculated earlier
								otheredge->gScore = gScore;
							
								//Set its previous to be the current node
								otheredge->previous = currentNode;

							}
						
						}


					}


				}
			
			
			}


		}
	}
	
	return path;
}
 

bool NodeGraph::CheckList(Node* node, std::deque<Node*> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (node == path[i])
		{
			return true;
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
	drawNode(node);
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
