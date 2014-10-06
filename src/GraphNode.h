#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Node.h"
#include "Appearance.h"
#include <map>
#include <string>

using std::map;
using std::string;

class GraphNode
{
public:
	GraphNode(void);
	~GraphNode(void);
	Appearance * appear;
	Node * atualNode;
	string atualNodeID;
	map<string, GraphNode *> descendants;
	void draw();
	bool inherited;
};

#endif