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

Node::Node(char * id){
	this->id = id;
	for(int i = 0; i < 16; i++){
		matrix[i] = 0;
		if(i % 5 == 0){
			matrix[i] = 1;
		}
	}
}

Node::Node(char * id, float matrix[16]){
	this->id = id;
	for(int i = 0; i < 16; i++){
		this->matrix[i] = matrix[i];
	}
}

Node::~Node(void)
{
}
