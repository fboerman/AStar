#ifndef _ASTAR_
#define _ASTAR_

#include <string>
#include <list>
#include <vector>
#include <map>
#include <math.h>

//T: Node class or struct. needs to have the follow functions:
//std::vector<float> GetPosition() which returns the position of the node in xy plane
//std::vector<T*>* GetNeighbors() which returns a pointer to a vector of pointers to neighbouring nodes
//std::string ID() which returns an unique ID for this node

template <typename T> struct Node;

template <typename T> struct Node
{
	T* payload;
	Node<T>* parent;
	float  heuristic;
	float distanceToBegin;
};

float CalcDistance(std::vector<float> p1, std::vector<float> p2)
{
	return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
}

//creates a wrapper Node struct around a given parent
template <typename T> Node<T>* CreateNode(T* payload, Node<T>* parent, T* begin, T* goal)
{
	Node<T>* n = new Node<T>;
	n->parent = parent;
	n->payload = payload;

	std::vector<float> pgoal = goal->GetPosition();
	std::vector<float> ppayload = payload->GetPosition();

	if (parent == nullptr)
	{
		n->distanceToBegin = 0;
	}
	else
	{
		std::vector<float> pparent = parent->payload->GetPosition();
		n->distanceToBegin = parent->distanceToBegin + CalcDistance(ppayload, parent->payload->GetPosition());
	}
	
	n->heuristic = CalcDistance(ppayload, pgoal);
	
	return n;
}


template <typename T> class Graph
{
public:
	//constructor and deconstructor
	inline Graph();
	inline ~Graph();

	//add a node to the graph
	inline void AddNode(T* N);

	//Calculate Astar algorithm
	inline std::vector<T*> Astar(T* begin, T* goal);

private:
	std::list<T*> _Nodes = std::list<T*>();
	std::list<Node<T>*> _open = std::list<Node<T>*>();
	std::list<Node<T>*> _closed = std::list<Node<T>*>();
};

template <typename T> Graph<T>::Graph()
{

}

template <typename T> Graph<T>::~Graph()
{

}

template <typename T> void Graph<T>::AddNode(T* N)
{
	_Nodes.push_back(N);
}

//check if node is on the list, return it if it is return nullptr otherwise
template <typename T> Node<T>* IsNodeOnList(std::list<Node<T>*> list, std::string ID)
{
	for (std::list<Node<T>*>::iterator it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->payload->ID() == ID)
		{
			return (*it);
		}
	}

	return nullptr;
}


template <typename T> std::vector<T*> Graph<T>::Astar(T* begin, T* goal)
{
	//clear all the old data
	while (!_closed.empty()) delete _closed.front(), _closed.pop_front();
	while (!_open.empty()) delete _open.front(), _open.pop_front();
	//clear the lists
	_open.clear();
	_closed.clear();

	//select the begin node as the current
	Node<T>* selected = CreateNode<T>(begin, nullptr, begin, goal);
	//add it to the open list
	_open.push_back(selected);
	while (1)
	{
		//switch the current selected to the closed list
		//first find it, than erase it, than add it to the closed
		std::list<Node<T>*>::iterator it = _open.begin();
		for (; it != _open.end(); it++)
		{
			if ((*it)->payload->ID() == selected->payload->ID())
			{
				break;
			}
		}
		_open.erase(it);
		_closed.push_back(selected);
		//check if the goal has been reached
		if (selected->payload->ID() == goal->ID())
		{
			//goal has been reached so stop the search
			break;
		}

		//get all the adjacent nodes for the current selected 
		//if they are on closed list, ignore
		//if they are on open list, check to see if current path to that node is better, ifso change parent and recalculate cost
		std::vector<T*>* nbhrs = selected->payload->GetNeighbors();
		for (unsigned int i = 0; i < nbhrs->size(); i++)
		{
			//check if neighbor is on the closed list
			if (IsNodeOnList<T>(_closed, (*nbhrs)[i]->ID()) != nullptr)
			{
				//ignore it
				continue;
			}
			//check if neighbor is on the open list
			Node<T>* N = IsNodeOnList<T>(_open, (*nbhrs)[i]->ID());
			if (N != nullptr)
			{
				//check if the current path to the square is better

				//calculate distance between the two nodes
				float dist = CalcDistance(N->payload->GetPosition(), selected->payload->GetPosition());

				//check the reachability
				if (selected->distanceToBegin + dist < N->distanceToBegin)
				{
					//it is shorter so update the parent and set the new value for distance
					N->parent = selected;
					N->distanceToBegin = selected->distanceToBegin + dist;
				}
			}
			else //not on open list
			{
				//add it with selected as parent
				_open.push_back(CreateNode((*nbhrs)[i], selected, begin, goal));
			}
		}

		//find the lowest cost node to be the next selected
		selected = (*_open.begin());
		for (std::list<Node<T>*>::iterator it = _open.begin(); it != _open.end(); it++)
		{
			if (((*it)->heuristic + (*it)->distanceToBegin) < (selected->heuristic + selected->distanceToBegin))
			{
				selected = *it;
			}
		}
		

	}

	//retrieve the found path and build a vector of pointers of it
	std::vector<T*> path = std::vector<T*>();
	Node<T>* N = _closed.back();
	while (1)
	{
		path.insert(path.begin(), N->payload);
		N = N->parent;
		if (N == nullptr)
		{
			break;
		}
	}

	//return this path and were done!
	return path;
}
#endif