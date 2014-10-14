#include "Rectangle.h"


Rectangle::Rectangle(double x1, double y1, double x2, double y2){
	coordX1=x1;
	coordY1=y1;
	coordX2=x2;
	coordY2=y2;
}

void Rectangle::draw(){
	glMatrixMode(GL_TEXTURE);
		
		glLoadIdentity();
		glScalef(abs(coordX1-coordX2)/this->tex_s,abs(coordY1-coordY2)/this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_QUADS);
	
		glTexCoord2d(0,1);glNormal3f(0,1,0);glVertex3d(coordX2,coordY1,0);
		glTexCoord2d(1,1);glNormal3f(0,1,0);glVertex3d(coordX2,coordY2,0);
		glTexCoord2d(1,0);glNormal3f(0,1,0);glVertex3d(coordX1,coordY2,0);
		glTexCoord2d(0,0);glNormal3f(0,1,0);glVertex3d(coordX1,coordY1,0);
	glEnd();

	glMatrixMode(GL_TEXTURE);
		
		glScalef(1/(abs(coordX1-coordX2)/this->tex_s),1/(abs(coordY1-coordY2)/this->tex_t),1);
		
	glMatrixMode(GL_MODELVIEW);

}