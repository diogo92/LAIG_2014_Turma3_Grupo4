#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "VisualObject.h"

class Rectangle: public VisualObject {
	public:
		Rectangle(double x1, double y1, double x2, double y2);
		double coordX1, coordY1;
		double coordX2, coordY2;
		void draw();
};


#endif