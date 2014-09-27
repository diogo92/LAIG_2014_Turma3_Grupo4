#ifndef CYLINDER_H
#define CYLINDER_H

#include "VisualObject.h"

class Cylinder : public VisualObject {
	
	int lados;
	int andares;
	double raioBase;
	double raioTopo;
	double altura;
	GLUquadricObj *obj;
	GLUquadricObj *diskBot;
	GLUquadricObj *diskTop;
	public:
		Cylinder(double raioBase, double raioTopo, double altura, int slices, int stacks);
		~Cylinder();
	    void draw();
		void drawTop();
		void drawBase();
};
	



#endif
