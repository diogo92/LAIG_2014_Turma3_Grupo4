#include "Primitives.h"

GLfloat ctrlpoints[4][3]={
	{0.5,0.0,-0.5},
	{0.5,0.0,0.5},
	{-0.5,0.0,-0.5},
	{-0.5,0.0,0.5}
};
GLfloat nrmlcompon[4][3]={
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0}
};

GLfloat textpoints[4][2] = {
	{ 0.0, 0.0},
	{ 0.0, 1.0},
	{ 1.0, 0.0},
	{ 1.0, 1.0} 
};
GLfloat colorpoints[4][4] = {	{ 0.0, 0.7, 0.7, 0},
								{ 0.0, 0.0, 0.7, 0}, 
								{ 0.0, 0.7, 0.0, 0},
								{ 0.7, 0.0, 0.0, 0} };
Cylinder::Cylinder(double raioBase, double raioTopo, double altura, int slices, int stacks) {
	lados = slices;
	andares = stacks;
	this->raioTopo=raioTopo;
	this->raioBase=raioBase;
	this->altura=altura;
	this->obj = gluNewQuadric();
	this->diskTop = gluNewQuadric();
	this->diskBot = gluNewQuadric();

}

Cylinder::~Cylinder(){
	gluDeleteQuadric(this->obj);
	gluDeleteQuadric(this->diskTop);
	gluDeleteQuadric(this->diskBot);
}
void Cylinder::draw() 
{
	/*glMatrixMode(GL_TEXTURE);
		
		glLoadIdentity();
		glScalef(1/this->tex_s,1/this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);*/

	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
	gluQuadricNormals(obj, GLU_SMOOTH);
	gluCylinder(obj, raioBase, raioTopo, altura, lados, andares);
	if(raioTopo>0){
		glPushMatrix();
		drawTop();
		glPopMatrix();
	}
	if(raioBase>0){
		glPushMatrix();
		drawBase();
		glPopMatrix();
	
	}

	/*glMatrixMode(GL_TEXTURE);
		
		glScalef(this->tex_s,this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);*/
	
}

void Cylinder::drawTop(){
	glPushMatrix();
	glTranslated(0,0,altura);
	gluQuadricOrientation(diskTop,GLU_OUTSIDE);
	gluQuadricTexture(diskTop,GLU_TRUE);
	gluDisk(diskTop,0,raioTopo,lados,1);
	glPopMatrix();
}

void Cylinder::drawBase(){
	glPushMatrix();
	glRotated(180,1,0,0);
	gluQuadricOrientation(diskBot,GLU_OUTSIDE);
	gluQuadricTexture(diskBot,GLU_TRUE);
	gluDisk(diskBot,0,raioBase,lados,1);
	glPopMatrix();
}


Plane::Plane(int parts){
	this->parts=parts;
}

void Plane::draw(){
	
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(parts, 0.0, 1.0, parts, 0.0, 1.0); 

	glEvalMesh2(GL_FILL, 0, parts, 0, parts);

}
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
	
		glTexCoord2d(0,1);glNormal3f(0,0,1);glVertex3d(coordX2,coordY1,0);
		glTexCoord2d(1,1);glNormal3f(0,0,1);glVertex3d(coordX2,coordY2,0);
		glTexCoord2d(1,0);glNormal3f(0,0,1);glVertex3d(coordX1,coordY2,0);
		glTexCoord2d(0,0);glNormal3f(0,0,1);glVertex3d(coordX1,coordY1,0);
	glEnd();

	glMatrixMode(GL_TEXTURE);
		
		glScalef(1/(abs(coordX1-coordX2)/this->tex_s),1/(abs(coordY1-coordY2)/this->tex_t),1);
		
	glMatrixMode(GL_MODELVIEW);

}

Sphere::Sphere(float raio, int slices, int stacks) {
	this->lados = slices;
	this->raio=raio;
	this->andares = stacks;
	this->obj = gluNewQuadric();

	gluQuadricOrientation(obj,GLU_OUTSIDE);
	gluQuadricTexture(obj,GLU_TRUE);
	gluQuadricNormals(obj,GLU_SMOOTH);
}

Sphere::~Sphere(){
	gluDeleteQuadric(this->obj);
}

void Sphere::draw() {
/*		glMatrixMode(GL_TEXTURE);
		
		glLoadIdentity();
		glScalef(1/this->tex_s,1/this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);*/
	gluSphere(obj,raio,lados,andares);
	/*	glMatrixMode(GL_TEXTURE);
		
		glScalef(this->tex_s,this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);*/
}

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
	glRotatef(90,1,0,0);
	glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(1/this->tex_s,1/this->tex_t,1);
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLE_STRIP);
	for(unsigned int i=0;i<vertices.size();i++){
		
		glTexCoord2f(tex[i].x,tex[i].y);
		glNormal3f(normal[i].x,normal[i].y,normal[i].z);
		glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
	}
	glEnd();
	glMatrixMode(GL_TEXTURE);
		glScalef(this->tex_s,this->tex_t,1);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(-90,1,0,0);
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
	b=sqrt(pow((x3-x1),2)+pow((y3-y1),2)+pow((z3-z1),2));
	c=sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
	a=sqrt(pow((x3-x2),2)+pow((y3-y2),2)+pow((z3-z2),2));
	cosB=((a*a)-(b*b)+(c*c))/(2*a*c);
	sinB=sqrt(abs(1-(cosB*cosB)));
}

void Triangle::draw(void){
	glMatrixMode(GL_TEXTURE);
		
		glLoadIdentity();
		glScalef(1/this->tex_s,1/this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLES);
	glNormal3f(normal.x,normal.y,normal.z);glTexCoord2f(0,0);glVertex3f(coordX1,coordY1,coordZ1);
	glNormal3f(normal.x,normal.y,normal.z);glTexCoord2f(c,0);glVertex3f(coordX2,coordY2,coordZ2);
	glNormal3f(normal.x,normal.y,normal.z);glTexCoord2f(abs(c-(a*cosB)),abs(a*sinB));glVertex3f(coordX3,coordY3,coordZ3);
	glEnd();

	glMatrixMode(GL_TEXTURE);
		
		glScalef(this->tex_s,this->tex_t,1);
		
	glMatrixMode(GL_MODELVIEW);
	
}