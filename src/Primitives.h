#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H


#include <vector>
#include "VisualObject.h"
#include "math.h"
#include "Vertice.h"


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
		void drawList();
};

class Rectangle: public VisualObject {
	public:
		Rectangle(double x1, double y1, double x2, double y2);
		double coordX1, coordY1;
		double coordX2, coordY2;
		void draw();
		void drawList();
};

class Sphere: public VisualObject {
	int lados;
	int andares;
	float raio;
	GLUquadricObj *obj;
	public:
		Sphere(float raio, int slices, int stacks);
		~Sphere();
	    void draw();
		void drawList();
};

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
		void drawList();
		void calcVertices(int i,int j);
};

class Triangle: public VisualObject {
	public:
		Triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
		void draw(void);
		void drawList();
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