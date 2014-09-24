#pragma once

#include "Node.h"

class Graph
{
public:
	Graph(void);
	~Graph(void);
	vector<Node> nodes;
	Node * root;
};

