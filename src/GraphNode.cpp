#include "GraphNode.h"


GraphNode::GraphNode(void)
{
}


GraphNode::~GraphNode(void)
{
}

void GraphNode::draw(){
	glMultMatrixf(&this->atualNode->matrix[0]);
	this->atualNode->draw();
	typedef std::map<std::string, GraphNode *>::iterator it_type;
	for(it_type iterator = this->descendants.begin(); iterator != this->descendants.end(); iterator++) {
		glPushMatrix();
		iterator->second->draw();
		glPopMatrix();
	}
}
