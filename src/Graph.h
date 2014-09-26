#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.h"

class Graph
{
public:
	Graph(void);
	~Graph(void);
	vector<Node> nodes;
	Node * root;
};

#endif