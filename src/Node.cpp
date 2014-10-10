#include "Node.h"

Node::Node(void)
{
}

Node::Node(string id){
	this->id = id;
	this->tex_s=1;
	this->tex_t=1;
}

Node::~Node(void)
{
	for(unsigned int i=0;i<primitives.size();i++)
		delete (primitives.at(i));
}

void Node::draw(){
	for(unsigned int i = 0; i < this->primitives.size();i++){
		this->primitives.at(i)->tex_s=this->tex_s;
		this->primitives.at(i)->tex_t=this->tex_t;
		this->primitives.at(i)->draw();
	}
}
