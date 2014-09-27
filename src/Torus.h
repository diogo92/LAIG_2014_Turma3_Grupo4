#ifndef TORUS_H
#define TORUS_H

#include "VisualObject.h"
#include "Vertice.h"
#include <vector>

class Torus : public VisualObject {
	
	int lados;
	int loops;
	double raioInterior;
	double raioExterior;
	double angulo;
	vector<Vertice> vertices;
	vector<Vertice> normal;
	vector<Vertice> tex;
	public:
		Torus(double raioInterior, double raioExterior, double lados, int loops);
		~Torus(){};
	    void draw();
		void calcVertices(int i,int j);
};
	



#endif
