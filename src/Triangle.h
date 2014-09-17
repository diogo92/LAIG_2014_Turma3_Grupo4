#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "VisualObject.h"
#include "Vertice.h"
#include <vector>

class Triangle: public VisualObject {
	public:
		Triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
		void draw(void);
	private:
		double coordX1, coordY1, coordZ1;
		double coordX2, coordY2, coordZ2;
		double coordX3, coordY3, coordZ3;
		double a,b,c,sinB,cosB;
		Vertice U;
		Vertice V;
		Vertice normal;
};

#endif
