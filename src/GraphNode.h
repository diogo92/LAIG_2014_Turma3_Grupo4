#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Node.h"
#include <map>
#include <string>

using std::map;
using std::string;

class GraphNode
{
public:
	GraphNode(void);
	~GraphNode(void);
	Node * atualNode;
	string atualNodeID;
	map<string, GraphNode *> descendants;
	void draw();
	float matrix[16];
};

#endif