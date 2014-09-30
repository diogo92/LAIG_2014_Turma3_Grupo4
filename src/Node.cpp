#include "Node.h"

Node::Node(void)
{
	for(unsigned int i = 0; i < 4; i++)
		for(unsigned int j = 0; j < 4; j++)
			if(i == j)
				this->matrix[i][j] = 1;
}

Node::Node(string id){
	this->id = id;
	for(unsigned int i = 0; i < 4; i++)
		for(unsigned int j = 0; j < 4; j++)
			if(i == j)
				this->matrix[i][j] = 1;
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
}
