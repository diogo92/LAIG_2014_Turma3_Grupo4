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
	~Node(void);
	void draw();
	string id;
	vector<VisualObject *> primitives;
	float matrix[4][4];
};

#endif
