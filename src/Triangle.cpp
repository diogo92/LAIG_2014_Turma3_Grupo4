#include "Triangle.h"
#include "math.h"


Triangle::Triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3){
	coordX1=x1;
	coordY1=y1;
	coordZ1=z1;
	coordX2=x2;
	coordY2=y2;
	coordZ2=z2;
	coordX3=x3;
	coordY3=y3;
	coordZ3=z3;
	U.x=(x2-x1);
	U.y=(y2-y1);
	U.z=(z2-z1);
	V.x=(x3-x1);
	V.y=(y3-y1);
	V.z=(z3-z1);
	normal.x=((U.y*V.z)-(U.z*V.y));
	normal.y=((U.z*V.x)-(U.x*V.z));
	normal.z=((U.x*V.y)-(U.y*V.x));
	a=sqrt(pow((x1-x3),2)+pow((y1-y3),2)+pow((z1-z3),2));
	b=sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
	c=sqrt(pow((x3-x2),2)+pow((y3-y2),2)+pow((z3-z2),2));
	cosB=((a*a)-(b*b)+(c*c))/(2*a);
	sinB=sqrt(1-(cosB*cosB));
}

void Triangle::draw(void){
	glBegin(GL_TRIANGLES);
	glNormal3f(normal.x,normal.y,normal.z);glTexCoord2f(0,0);glVertex3f(coordX1,coordY1,coordZ1);
	glNormal3f(normal.x,normal.y,normal.z);glTexCoord2f(c,0);glVertex3f(coordX2,coordY2,coordZ2);
	glNormal3f(normal.x,normal.y,normal.z);glTexCoord2f(c-(a*cosB),a*sinB);glVertex3f(coordX3,coordY3,coordZ3);
	glEnd();
}