#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "VisualObject.h"

using std::vector;
using std::string;

class Node
{
public:
	Node(void);
	Node(string id);
	Node(string id, float matrix[16]);
	~Node(void);
	void draw();
	float matrix[16];
	string id;
	vector<Node *> descendants;
	vector<VisualObject *> primitives;
};

#endif
