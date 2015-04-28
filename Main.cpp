#include "Main.h"

ANode::ANode(std::string ID, float p[2])
{
	_ID = ID;
	_p.push_back(p[0]);
	_p.push_back(p[1]);
}

ANode::~ANode()
{

}

void ANode::AddNeighbor(ANode* N)
{
	_neighbors.push_back(N);
}

std::vector<float> ANode::GetPosition()
{
	return _p;
}

std::vector<ANode*>* ANode::GetNeighbors()
{
	return &_neighbors;
}

std::string ANode::ID()
{
	return _ID;
}

void test1(Graph<ANode>* g)
{
	//declare all the nodes
	float p[2] = { 0, 10 };
	ANode A = ANode("A", p);
	p[0] = 10;
	p[1] = 15;
	ANode B = ANode("B", p);
	p[0] = 10;
	p[1] = 5;
	ANode C = ANode("C", p);
	p[0] = 20;
	p[1] = 10;
	ANode D = ANode("D", p);
	p[0] = 7;
	p[1] = 0;
	ANode E = ANode("E", p);
	p[0] = 15;
	p[1] = 0;
	ANode F = ANode("F", p);

	//declare the links between them
	A.AddNeighbor(&B);
	A.AddNeighbor(&C);
	B.AddNeighbor(&A);
	B.AddNeighbor(&C);
	B.AddNeighbor(&D);
	C.AddNeighbor(&A);
	C.AddNeighbor(&B);
	C.AddNeighbor(&E);
	C.AddNeighbor(&F);
	D.AddNeighbor(&B);
	E.AddNeighbor(&C);
	F.AddNeighbor(&C);

	//add the nodes to the graph
	g->AddNode(&A);
	g->AddNode(&B);
	g->AddNode(&C);
	g->AddNode(&D);
	g->AddNode(&E);
	g->AddNode(&F);

	//calculate a path
	std::vector<ANode*> path = g->Astar(&E, &D);

	//print the path
	for (std::vector<ANode*>::iterator it = path.begin(); it != path.end(); it++)
	{
		if ((*it) != path.back())
		{
			std::cout << (*it)->ID() << " -> ";
		}
		else
		{
			std::cout << (*it)->ID() << std::endl;
		}
	}
}

void test2(Graph<ANode>* g)
{
	//declare all the nodes
	float p[2] = { 0, 20 };
	ANode A = ANode("A", p);
	p[0] = 10;
	p[1] = 10;
	ANode B = ANode("B", p);
	p[0] = 10;
	p[1] = 30;
	ANode C = ANode("C", p);
	p[0] = 15;
	p[1] = 20;
	ANode D = ANode("D", p);
	p[0] = 25;
	p[1] = 20;
	ANode E = ANode("E", p);
	p[0] = 20;
	p[1] = 10;
	ANode F = ANode("F", p);
	p[0] = 10;
	p[1] = 0;
	ANode G = ANode("G", p);
	p[0] = 20;
	p[1] = 40;
	ANode H = ANode("H", p);
	p[0] = 30;
	p[1] = 10;
	ANode I = ANode("I", p);
	p[0] = 20;
	p[1] = 0;
	ANode J = ANode("J", p);

	//declare the links
	A.AddNeighbor(&B);
	A.AddNeighbor(&C);
	B.AddNeighbor(&A);
	B.AddNeighbor(&D);
	B.AddNeighbor(&G);
	C.AddNeighbor(&A);
	C.AddNeighbor(&D);
	D.AddNeighbor(&C);
	D.AddNeighbor(&B);
	D.AddNeighbor(&F);
	D.AddNeighbor(&H);
	D.AddNeighbor(&E);
	E.AddNeighbor(&D);
	E.AddNeighbor(&H);
	E.AddNeighbor(&I);
	F.AddNeighbor(&D);
	F.AddNeighbor(&I);
	F.AddNeighbor(&J);
	G.AddNeighbor(&B);
	G.AddNeighbor(&J);
	H.AddNeighbor(&D);
	H.AddNeighbor(&E);
	I.AddNeighbor(&E);
	I.AddNeighbor(&F);
	J.AddNeighbor(&F);
	J.AddNeighbor(&G);

	//add the nodes to the graph
	g->AddNode(&A);
	g->AddNode(&B);
	g->AddNode(&C);
	g->AddNode(&D);
	g->AddNode(&E);
	g->AddNode(&F);
	g->AddNode(&G);
	g->AddNode(&H);
	g->AddNode(&I);
	g->AddNode(&J);

	//calculate a path
	std::vector<ANode*> path = g->Astar(&A, &I);

	//print the path
	for (std::vector<ANode*>::iterator it = path.begin(); it != path.end(); it++)
	{
		if ((*it) != path.back())
		{
			std::cout << (*it)->ID() << " -> ";
		}
		else
		{
			std::cout << (*it)->ID() << std::endl;
		}
	}
}

int main()
{
	//test 1
	Graph<ANode> g1 = Graph<ANode>();
	std::cout << "Test1" << std::endl;
	test1(&g1);

	//test2
	Graph<ANode> g2 = Graph<ANode>();
	std::cout << "Test2" << std::endl;
	test2(&g2);
}