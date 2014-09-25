#include "Sphere.h"
#include "math.h"
Sphere::Sphere(double raio, int slices, int stacks) {
	lados = slices;
	this->raio=raio;
	andares = stacks;

}



void Sphere::draw() {

	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
	glPushMatrix();
	gluSphere(obj,raio,lados,andares);
	glPopMatrix();
}


