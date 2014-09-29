#include "GraphNode.h"


GraphNode::GraphNode(void)
{
}


GraphNode::~GraphNode(void)
{
}

void GraphNode::draw(){
	this->atualNode->draw();
	typedef std::map<std::string, GraphNode *>::iterator it_type;
	for(it_type iterator = this->descendants.begin(); iterator != this->descendants.end(); iterator++) {
		iterator->second->draw();
	}
}
