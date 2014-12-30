#include "Primitives.h"

const GLfloat Plane::ctrlpoints[4][3]={
	{0.5,0.0,-0.5},
	{0.5,0.0,0.5},
	{-0.5,0.0,-0.5},
	{-0.5,0.0,0.5}
};
const GLfloat Plane::nrmlcompon[4][3]={
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0}
};

const GLfloat Plane::textpoints[4][2] = {
	{ 0.0, 0.0},
	{ 0.0, 1.0},
	{ 1.0, 0.0},
	{ 1.0, 1.0} 
};
const GLfloat Plane::colorpoints[4][4] = {	
	{ 0.0, 0.7, 0.7, 0},
	{ 0.0, 0.0, 0.7, 0}, 
	{ 0.0, 0.7, 0.0, 0},
	{ 0.7, 0.0, 0.0, 0} 
};

Piece::Piece(){
	this->tex=0;
	this->appearances1.push_back(new CGFappearance("woodtheme/p1.jpg",1,1));
	this->appearances1.push_back(new CGFappearance("mineraltheme/p1.png",1,1));
	this->appearances1.push_back(new CGFappearance("seatheme/p1.jpg",1,1));
	this->appearances2.push_back(new CGFappearance("woodtheme/p2.jpg",1,1));
	this->appearances2.push_back(new CGFappearance("mineraltheme/p2.jpg",1,1));
	this->appearances2.push_back(new CGFappearance("seatheme/p2.png",1,1));
	this->cyl=new Cylinder(0.5,0.5,0.1,16,16);
}

Piece::~Piece(){
	delete(this->cyl);
}


void Piece::draw(int player){
	if(player==1){
		this->appearances1.at(tex)->apply();
	}
	else
		this->appearances2.at(tex)->apply();

	cyl->draw();

}

Board::Board(){
	this->moving=false;
	this->moveX=0;
	this->moveZ=0;
	this->goingUp=true;
	this->tex=0;
	this->h=0;
	this->angRot=0;
	this->appearances1.push_back(new CGFappearance("woodtheme/boardp1.png",1,1));
	this->appearances1.push_back(new CGFappearance("mineraltheme/boardp1.jpg",1,1));
	this->appearances1.push_back(new CGFappearance("seatheme/boardp1.jpeg",1,1));
	this->appearances2.push_back(new CGFappearance("woodtheme/boardp2.jpg",1,1));
	this->appearances2.push_back(new CGFappearance("mineraltheme/boardp2.png",1,1));
	this->appearances2.push_back(new CGFappearance("seatheme/boardp2.png",1,1));
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			pieces[i][j]=0;
		}
	}
	this->init();
	square= new Rectangle(0,0,1,1);
	square->tex_s=1;
	square->tex_t=1;

}

bool Board::selected(int row, int col){
	bool res=false;
	if(selectedRow == row && selectedColumn==col)
		res=true;
	return res;
}
void Board::draw(){
	bool imp=false;
	glPushMatrix();
	glPushName(-1);
	glPopMatrix();
	for(int i = 0;i<8;i++){
		float col = (float)i/8.0;
		if(imp){
			appearances1.at(tex)->apply();
			imp=false;
		}
		else{
			appearances2.at(tex)->apply();
			imp=true;
		}
		glPushMatrix();
		glTranslated(0,0.001,0);
		glLoadName(i);
		for(int j=0;j<8;j++){
			float row = (float)j/8;

				glPushMatrix();
				glTranslated(col+(0.5/8.0), 0, row+(0.5/8.0));
				glRotated(-90,1,0,0);
				glScaled((0.5/8.0),(0.5/8.0),(0.5/8.0));

				glPushMatrix();
				glScaled(2,2,2);
				glTranslated(-0.5,-0.5,0);
				if(imp){
					appearances1.at(tex)->apply();
					imp=false;
				}
				else{
					appearances2.at(tex)->apply();
					imp=true;
				}
				glPushName(j+100);
				square->draw();
				glPopName();
				glPopMatrix();
				glPushName(j);
				glPushMatrix();
				if(selected(i,j)){
					glTranslated(moveX,moveZ,h);
					glRotated(angRot,0,1,0);
				}
				if(pieces[i][j]!=0)
					piece->draw(pieces[i][j]);
				glPopMatrix();
				glPopName();
				glPopMatrix();

		}
		glPopMatrix();
	}
}

void Board::movePiece(){
	printf("MOVING PIECE FROM %d %d TO %d %d\n",selectedRow,selectedColumn,targetRow,targetColumn);
	moving=true;
}
void Board::update(unsigned long t){
	if(moving){
		if(moveX<=-2.5 || moveX>=2.5 || moveZ>=2.5 || moveZ<=-2.5){
			pieces[targetRow][targetColumn]=pieces[selectedRow][selectedColumn];
			pieces[selectedRow][selectedColumn]=0;
			if(selectedRow==targetRow){
				if(selectedColumn>targetColumn){
					pieces[targetRow][targetColumn+1]=0;
				}
				else
					pieces[targetRow][targetColumn-1]=0;
			}
			else if(selectedColumn==targetColumn){
				if(selectedRow>targetRow){
					pieces[targetRow+1][targetColumn]=0;
				}
				else
					pieces[targetRow-1][targetColumn]=0;
			}
			
			selectedRow=-1;
			selectedColumn=-1;
			targetColumn=-1;
			targetRow=-1;
			moving=false;
			moveX=0;
			moveZ=0;
		}
		else if(selectedRow==targetRow){
			moveX=0;
			if(selectedColumn>targetColumn)
				moveZ+=0.5;
			else
				moveZ-=0.5;
		}
		else if(selectedColumn==targetColumn){
			moveZ=0;
			if(selectedRow>targetRow)
				moveX-=0.5;
			else
				moveX+=0.5;
		}
	}
	if(goingUp){
		if(h>3)
			goingUp=false;
		else
			h+=0.5;
	}
	if(!goingUp){
		if(h<=0)
			goingUp=true;
		else
			h-=0.5;
	}
	angRot+=15;
}

void Board::setTexture(int t){
	this->tex=t;
	this->piece->tex=t;
}

void Board::init(){
	this->piece=new Piece();
	int row=0;
	int peca1=1;
	int peca2=2;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(row%2==0){
				peca1=1;
				peca2=2;
			}
			else{
				peca2=1;
				peca1=2;
			}
			if(j%2==0){
				pieces[i][j]=peca1;
			}
			else{
				pieces[i][j]=peca2;
			}

		}
		row++;
	}
}

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

Patch::Patch(int order,int partsU,int partsV,string compute,GLfloat* ctrlpoints){
	this->order=order;
	this->partsU=partsU;
	this->partsV=partsV;
	this->compute=compute;
	const int numCP = (order+1)*(order+1);
	this->ctrlpoints=new GLfloat[numCP*3];
	for(int i = 0; i < numCP; i++) {
		this->ctrlpoints[i*3+0] = ctrlpoints[i*3+0];
		this->ctrlpoints[i*3+1] = ctrlpoints[i*3+1];
		this->ctrlpoints[i*3+2] = ctrlpoints[i*3+2];
	}
}

void Patch::draw(){
	int ff;
	glGetIntegerv(GL_FRONT_FACE, &ff);
	glEnable(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order+1, 0.0, 1.0, 3*(order+1), order+1, &this->ctrlpoints[0]);
	
	if(order==1){
		GLfloat textpoints[4][2] = {
			{1, 0.0}, {1,1},
			{0.0, 0.0},{0.0, 1} 
		};
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, (order+1), 0.0, 1.0, (order+1)*2, (order+1), &textpoints[0][0]);
	}else if(order==2){
		GLfloat textpoints[9][2] = {
			{0.0,1}, {1/2, 1}, {1,1},
			{0.0,1/2}, {1/2, 1/2}, {1, 1/2},
			{0.0,0.0}, {1/2,0.0}, {1,0.0}
		};
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, (order+1), 0.0, 1.0, (order+1)*2, (order+1), &textpoints[0][0]);
	}else if(order==3){
		GLfloat textpoints[16][2] = {
			{0.0,1}, {1/3, 1}, {2/3,1}, {1,1},
			{0.0,2/3},{1/3,2/3},{2/3,2*1/3}, {1,2/3},
			{0.0,1/3}, {1/3,1/3}, {2/3,1/3}, {1,1/3},
			{0.0,0.0}, {1/3,0.0}, {2/3,0.0}, {1,0.0}
		};
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, (order+1), 0.0, 1.0, (order+1)*2, (order+1), &textpoints[0][0]);
	}

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);

	glShadeModel(GL_SMOOTH);
	if(compute == "fill")
		glEvalMesh2(GL_FILL, 0, partsU, 0, partsV);
	else if(compute == "point")
		glEvalMesh2(GL_POINT, 0, partsU, 0, partsV);
	else if(compute == "line")
		glEvalMesh2(GL_LINE, 0, partsU, 0, partsV);
	
	glDisable(GL_AUTO_NORMAL);
	glFrontFace(ff);
}

Vehicle::Vehicle(){
	GLfloat vehicle1CtrlPoints[48]={
		2,-2,0,
		3,-1,0,
		3,1,0,
		2,2,0,
		1,-3,0,
		1,-1,5,
		1,1,5,
		1,3,0,
		-1,-3,0,
		-1,-1,5,
		-1,1,5,
		-1,3,0,
		-2,-2,0,
		-3,-1,0,
		-3,1,0,
		-2,2,0
	};

	GLfloat vehicle2CtrlPoints[48]={
		5,-5,0,
		6,-4,0,
		6,4,0,
		5,5,0,
		4,-6,0,
		4,-4,2,
		4,4,2,
		4,6,0,
		-4,-6,0,
		-4,-4,2,
		-4,4,2,
		-4,6,0,
		-5,-5,0,
		-6,-4,0,
		-6,4,0,
		-5,3,0
	};
	patch1=new Patch(3,100,100,"fill",vehicle1CtrlPoints);
	patch2=new Patch(3,100,100,"fill",vehicle2CtrlPoints);
}

void Vehicle::draw(){
	glPushMatrix();
	glRotatef(-90,1,0,0);
	glScalef(0.2,0.2,0.2);
	patch1->draw();
	patch2->draw();
	glPushMatrix();
	glRotated(180,0,1,0);
	patch2->draw();
	glPopMatrix();
	glPopMatrix();
}

Flag::Flag(string texture){
	this->p= new Plane(100);
	this->time2=0;
	this->wind2=0;
	char* vert="flag.vert";
	char* frag="flag.frag";
	this->shader.init(vert,frag);
	this->texture= new CGFtexture(texture);
}

void Flag::draw(){
	shader.bind();
	this->wind=glGetUniformLocation(shader.id(),"wind");
	glUniform1f(wind,wind2);
	this->time=glGetUniformLocation(shader.id(),"time");
	glUniform1f(time, time2);
	this->image=glGetUniformLocation(shader.id(),"hImage");
	glUniform1i(this->image,0);

	glActiveTexture(GL_TEXTURE0);

	this->texture->apply();

	p->draw();
	shader.unbind();
}

void Flag::update(unsigned long t){
	this->wind2=t;
	this->time2 += 0.3;
	if(this->time2 >=5){
		this->time2-=5;
	}
	
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