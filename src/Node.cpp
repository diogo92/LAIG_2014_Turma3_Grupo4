#include "Node.h"

Node::Node(void)
{
	for(int i = 0; i < 16; i++){
		matrix[i] = 0;
		if(i % 5 == 0){
			matrix[i] = 1;
		}
	}
}


Node::~Node(void)
{
}
