#include "Sphere.h"
#include "math.h"
Sphere::Sphere(float raio, int slices, int stacks) {
	this->lados = slices;
	this->raio=raio;
	this->andares = stacks;
	this->obj = gluNewQuadric();

	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
	gluQuadricNormals(obj,GLU_SMOOTH);
}

Sphere::~Sphere(){
	gluDeleteQuadric(this->obj);
}

void Sphere::draw() {
/*		glMatrixMode(GL_TEXTURE);
		
		glLoadIdentity();
		glScalef(1/this->tex_s,1/this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);*/
	gluSphere(obj,raio,lados,andares);
	/*	glMatrixMode(GL_TEXTURE);
		
		glScalef(this->tex_s,this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);*/
}


