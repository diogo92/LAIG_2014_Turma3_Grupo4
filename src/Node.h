#pragma once

#include <vector>
#include "VisualObject.h"

using std::vector;

class Node
{
public:
	Node(void);
	~Node(void);
	float matrix[16];
	char * id;
	vector<Node *> descendants;
	vector<VisualObject> primitives;
};

