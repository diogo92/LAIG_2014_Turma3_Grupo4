#include "Node.h"

Node::Node(void)
{
	matrix[0] = 1;
	matrix[1] = 0;
	matrix[2] = 0;
	matrix[3] = 0;
	matrix[4] = 0;
	matrix[5] = 1;
	matrix[6] = 0;
	matrix[7] = 0;
	matrix[8] = 0;
	matrix[9] = 0;
	matrix[10] = 1;
	matrix[11] = 0;
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;
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
