#include "Node.h"

Node::Node(void)
{
}

Node::Node(string id){
	this->id = id;
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
