#include "NewGraph.h"


NewGraph::NewGraph(void)
{
}


NewGraph::~NewGraph(void)
{
}

NewNode::NewNode(void)
{
}

NewNode::NewNode(string id)
{
	this->id = id;
}

NewNode::~NewNode(void)
{
}

void NewGraph::draw(){
	this->nodes[this->rootNode].draw(this);
}

void NewNode::draw(NewGraph * graph){
	glMultMatrixf(&this->matrix[0]);
	this->appear->apply();
	for(unsigned int i = 0; i < this->primitives.size();i++){
		this->primitives.at(i)->tex_s=this->appear->s;
		this->primitives.at(i)->tex_t=this->appear->t;
		this->primitives.at(i)->draw();
	}
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);
	for(unsigned int i = 0; i < this->childs.size();i++){
		glPushMatrix();
		if(graph->nodes[this->childs.at(i)].inherited){
			graph->nodes[this->childs.at(i)].appear = this->appear;
		}
		graph->nodes[this->childs.at(i)].draw(graph);
		glPopMatrix();
		glColor4fv(currentColor);
	}
}