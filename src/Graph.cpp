#include "Graph.h"


Graph::Graph(void)
{
}


Graph::~Graph(void)
{
}

Node::Node(void)
{
}

Node::Node(string id)
{
	this->id = id;
}

Node::~Node(void)
{
}

void Graph::draw(){
	this->nodes[this->rootNode].draw(this);
}

void Node::draw(Graph * graph){
	glMultMatrixf(&this->matrix[0]);
	this->appear->apply();
	if(displayList)
		glCallList(this->dispList);
	else{
		for(unsigned int i = 0; i < this->primitives.size();i++){
			glPushMatrix();
			this->primitives.at(i)->tex_s=this->appear->s;
			this->primitives.at(i)->tex_t=this->appear->t;
			this->primitives.at(i)->draw();
			glPopMatrix();
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
}

void Node::update(unsigned long t){
	for(int i=0;i< this->primitives.size();i++){
		this->primitives.at(i)->update(t);
	}
}
void Node::checkList(Graph * graph){
	if(displayList){
		this->dispList=glGenLists(1);
		glNewList(dispList,GL_COMPILE);
		for(unsigned int i = 0; i < this->primitives.size();i++){
			glPushMatrix();
			this->primitives.at(i)->tex_s=this->appear->s;
			this->primitives.at(i)->tex_t=this->appear->t;
			this->primitives.at(i)->draw();
			glPopMatrix();
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
		glEndList();
	}
}