#include "Sphere.h"
#include "math.h"
Sphere::Sphere(double raio, int slices, int stacks) {
	this->lados = slices;
	this->raio=raio;
	this->andares = stacks;
	this->obj = gluNewQuadric();
	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
}

Sphere::~Sphere(){
	gluDeleteQuadric(this->obj);
}

void Sphere::draw() {
	glPushMatrix();
	gluSphere(obj,raio,lados,andares);
	glPopMatrix();
}


