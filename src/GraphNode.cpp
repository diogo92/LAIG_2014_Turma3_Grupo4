#include "GraphNode.h"


GraphNode::GraphNode(void)
{
}


GraphNode::~GraphNode(void)
{
}

void GraphNode::draw(){
	glMultMatrixf(&this->atualNode->matrix[0]);
	this->appear->apply();
	this->atualNode->draw();
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);
	typedef std::map<std::string, GraphNode *>::iterator it_type;
	for(it_type iterator = this->descendants.begin(); iterator != this->descendants.end(); iterator++) {
		glPushMatrix();
		if(iterator->second->inherited)
			iterator->second->appear=this->appear;
		iterator->second->draw();
		glPopMatrix();
		glColor4fv(currentColor);
	}
}
