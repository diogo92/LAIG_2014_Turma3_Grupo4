#include "Sphere.h"
#include "math.h"
Sphere::Sphere(double raio, int slices, int stacks) {
	this->lados = slices;
	this->raio=raio;
	this->andares = stacks;
	this->obj = gluNewQuadric();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);  


	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
}

Sphere::~Sphere(){
	gluDeleteQuadric(this->obj);
}

void Sphere::draw() {
		glMatrixMode(GL_TEXTURE);
		
		glLoadIdentity();
		glScalef(1/this->tex_s,1/this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);
	gluSphere(obj,raio,lados,andares);
		glMatrixMode(GL_TEXTURE);
		
		glScalef(this->tex_s,this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);
}


