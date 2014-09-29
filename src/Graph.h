#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.h"
#include "GraphNode.h"
#include <map>

using std::map;
using std::string;

class Graph
{
public:
	Graph(void);
	~Graph(void);
	map<string ,Node> nodes;
	string rootNodeID;
	map<string,GraphNode> graphNodes;
	GraphNode * rootNode;
	void draw();
};

#endif