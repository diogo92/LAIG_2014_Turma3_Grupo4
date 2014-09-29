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

Node::Node(string id){
	this->id = id;
	for(int i = 0; i < 16; i++){
		matrix[i] = 0;
		if(i % 5 == 0){
			matrix[i] = 1;
		}
	}
}

Node::Node(string id, float matrix[16]){
	this->id = id;
	for(unsigned int i = 0; i < 16; i++){
		this->matrix[i] = matrix[i];
	}
}

Node::~Node(void)
{
	for(unsigned int i=0;i<primitives.size();i++)
		delete (primitives.at(i));
}

void Node::draw(){
	for(unsigned int i = 0; i < this->primitives.size();i++){
		this->primitives.at(i)->draw();
	}
	for(unsigned int i = 0; i < this->descendants.size();i++){
		this->descendants.at(i)->draw();
	}
}
