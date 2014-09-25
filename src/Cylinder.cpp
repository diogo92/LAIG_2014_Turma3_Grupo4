#include "Cylinder.h"

Cylinder::Cylinder(double raioBase, double raioTopo, double altura, int slices, int stacks) {
	lados = slices;
	andares = stacks;
	this->raioTopo=raioTopo;
	this->raioBase=raioBase;
	this->altura=altura;

}
void Cylinder::draw() 
{
	GLUquadricObj *obj = gluNewQuadric();
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
	GLUquadricObj *disk = gluNewQuadric();
	gluQuadricOrientation(disk,GLU_OUTSIDE);
	gluQuadricTexture(disk,GLU_TRUE);
	gluDisk(disk,0,raioTopo,lados,1);
	glPopMatrix();
}

void Cylinder::drawBase(){
	glPushMatrix();
	glRotated(180,1,0,0);
	GLUquadricObj *disk = gluNewQuadric();
	gluQuadricOrientation(disk,GLU_OUTSIDE);
	gluQuadricTexture(disk,GLU_TRUE);
	gluDisk(disk,0,raioBase,lados,1);
	glPopMatrix();
}

