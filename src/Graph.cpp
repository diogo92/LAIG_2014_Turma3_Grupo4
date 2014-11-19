#include "Graph.h"


Graph::Graph(void)
{
}


Graph::~Graph(void)
{
}

Node::Node(void)
{
	this->atualAnim = 0;
}

Node::Node(string id)
{
	this->id = id;
	this->atualAnim = 0;
}

Node::~Node(void)
{
}

void Graph::draw(){
	this->nodes[this->rootNode].draw(this);
}

void Node::animsTransforms(){
	this->anims.at(this->atualAnim)->apply();
}

void Graph::setAppearances(){
	this->nodes[this->rootNode].setAppearances(this);
}

void Node::setAppearances(Graph * graph){
	float currentColor[4];
		glGetFloatv(GL_CURRENT_COLOR,currentColor);
		for(unsigned int i = 0; i < this->childs.size();i++){
			glPushMatrix();
			if(graph->nodes[this->childs.at(i)].inherited){
				graph->nodes[this->childs.at(i)].appear = this->appear;
			}
			graph->nodes[this->childs.at(i)].setAppearances(graph);
			glPopMatrix();
			glColor4fv(currentColor);
		}
}

void Node::draw2(Graph * graph){
	glMultMatrixf(&this->matrix[0]);
	this->appear->apply();
	if(displayList){
		glCallList(this->dispList);
	}
	for(unsigned int i = 0; i < this->childs.size();i++){
		glPushMatrix();
			graph->nodes[this->childs.at(i)].draw2(graph);
		glPopMatrix();
	}
}

void Node::draw(Graph * graph){
	glMultMatrixf(&this->matrix[0]);
	this->appear->apply();
	if(displayList){
		glCallList(this->dispList);
		for(unsigned int i = 0; i < this->childs.size();i++){
			glPushMatrix();
				graph->nodes[this->childs.at(i)].draw2(graph);
			glPopMatrix();
		}
	}
	else{
		glPushMatrix();
		animsTransforms();
		for(unsigned int i = 0; i < this->primitives.size();i++){
			glPushMatrix();
			this->primitives.at(i)->tex_s=this->appear->s;
			this->primitives.at(i)->tex_t=this->appear->t;
			this->primitives.at(i)->draw();
			glPopMatrix();
		}
		for(unsigned int i = 0; i < this->childs.size();i++){
			glPushMatrix();
			graph->nodes[this->childs.at(i)].draw(graph);
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void Node::updateAnim(unsigned long t){
		if(this->anims.at(this->atualAnim)->ended){
			this->atualAnim++;
		}
		if(this->atualAnim >= this->anims.size()){
			this->atualAnim = 0;
			for(unsigned int i = 0; i < this->anims.size(); i++){
				this->anims.at(i)->ended = false;
				this->anims.at(i)->reset();
			}
		}
		this->anims.at(this->atualAnim)->update(t);
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
		for(unsigned int i = 0; i < this->childs.size();i++){
			glPushMatrix();
			if(!graph->nodes[this->childs.at(i)].displayList){
				graph->nodes[this->childs.at(i)].draw(graph);
			}
			glPopMatrix();
		}
		glEndList();
	}
}