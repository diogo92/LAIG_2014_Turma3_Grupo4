#include "Torus.h"
#include <math.h>

Torus::Torus(double raioInterior, double raioExterior, double lados, int loops){
	this->lados = lados;
	this->raioInterior=raioInterior;
	this->raioExterior=raioExterior;
	this->loops=loops;
	double param = -1;
	angulo =(2*acos(param));
	for(int i=0;i<lados;i++){
		for(int j=0;j<=loops;j++){
			calcVertices(i,j);
			calcVertices(i+1,j);
		}
	}
	
}
void Torus::draw() 
{
	glBegin(GL_TRIANGLE_STRIP);
	for(unsigned int i=0;i<vertices.size();i++){
		glTexCoord2f(tex[i].x,tex[i].y);
		glNormal3f(normal[i].x,normal[i].y,normal[i].z);
		glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
	}
	glEnd();
}

void Torus::calcVertices(int i,int j){
	float calcWrap = (j%loops)/(float)loops;
	float calcTex = (float)j/(float)loops;
	float angAux1 = angulo*calcWrap;
	float angAux2Wrap = ((float)(i%lados)+calcTex)/(float)lados;
	float angAuxTex = ((float)i+calcTex)/(float)lados;
	float angAux2 = angulo*angAux2Wrap;
	float sinAngAux1 = sin(angAux1);
	float cosAngAux1 = cos(angAux1);
	float sinAngAux2 = sin(angAux2);
	float cosAngAux2 = cos(angAux2);
	float y = raioInterior*sinAngAux1;
	float r = raioExterior + raioInterior*cosAngAux1;
	float x = sinAngAux2*r;
	float z = cosAngAux2*r;
	vertices.push_back(Vertice(x,y,z));
	normal.push_back(Vertice(sinAngAux2*cosAngAux1,sinAngAux1,cosAngAux2*cosAngAux1));
	tex.push_back(Vertice(calcTex, angAuxTex,0));
	
}

