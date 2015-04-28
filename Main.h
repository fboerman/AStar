#ifndef _MAINH_
#define _MAIN_

#include "Astar.h"
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iostream>

class ANode
{
public:
	ANode(std::string ID, float p[2]);
	~ANode();

	void AddNeighbor(ANode* N);

	std::vector<float> GetPosition();

	std::vector<ANode*>* GetNeighbors();

	std::string ID();

private:
	std::vector<ANode*> _neighbors;
	std::string _ID;
	std::vector<float> _p;
};
#endif