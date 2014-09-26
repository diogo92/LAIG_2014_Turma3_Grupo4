#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "VisualObject.h"

using std::vector;

class Node
{
public:
	Node(void);
	Node(char * id);
	Node(char * id, float matrix[16]);
	~Node(void);
	float matrix[16];
	char * id;
	vector<int> descendants;
	vector<VisualObject> primitives;
};

#endif
