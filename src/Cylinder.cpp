#include "Cylinder.h"

Cylinder::Cylinder(double raioBase, double raioTopo, double altura, int slices, int stacks) {
	lados = slices;
	andares = stacks;
	this->raioTopo=raioTopo;
	this->raioBase=raioBase;
	this->altura=altura;
	this->obj = gluNewQuadric();
	this->diskTop = gluNewQuadric();
	this->diskBot = gluNewQuadric();

}

Cylinder::~Cylinder(){
	gluDeleteQuadric(this->obj);
	gluDeleteQuadric(this->diskTop);
	gluDeleteQuadric(this->diskBot);
}
void Cylinder::draw() 
{
	
	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
	glPushMatrix();
	gluCylinder(obj, raioBase, raioTopo, altura, lados, andares);
	if(raioTopo>0){
		glPushMatrix();
		drawTop();
		glPopMatrix();
	}
	if(raioBase>0){
		glPushMatrix();
		drawBase();
		glPopMatrix();
	glPopMatrix();
	}
	
	
}

void Cylinder::drawTop(){
	glPushMatrix();
	glTranslated(0,0,altura);
	gluQuadricOrientation(diskTop,GLU_OUTSIDE);
	gluQuadricTexture(diskTop,GLU_TRUE);
	gluDisk(diskTop,0,raioTopo,lados,1);
	glPopMatrix();
}

void Cylinder::drawBase(){
	glPushMatrix();
	glRotated(180,1,0,0);
	gluQuadricOrientation(diskBot,GLU_OUTSIDE);
	gluQuadricTexture(diskBot,GLU_TRUE);
	gluDisk(diskBot,0,raioBase,lados,1);
	glPopMatrix();
}

