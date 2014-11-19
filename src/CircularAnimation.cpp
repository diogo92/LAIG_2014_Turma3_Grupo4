#include "CircularAnimation.h"


CircularAnimation::CircularAnimation(void)
{
}


CircularAnimation::~CircularAnimation(void)
{
}

void CircularAnimation::reset()
{
	doReset=true;
}

void CircularAnimation::calcValues(){
	this->stepAngle = rotang / span;
}

void CircularAnimation::update(unsigned long t)
{
		if (doReset){
			init(t);
		}
		else
		{
			animT=t-startTime;
			if(animT < (unsigned long)this->span){
				dT.x = this->center.x + radius;
				dT.y = this->center.y;
				dT.z = this->center.z;
				angle = this->startang + this->stepAngle*(float)(animT);
			}
			else{
				this->ended = true;
			}
		}
}

void CircularAnimation::apply(){
	glTranslatef(this->center.x,this->center.y,this->center.z);
	glRotatef(this->angle,0,1,0);
	glTranslatef(this->radius,0,0);
	glRotatef(180,0,1,0);
}

void CircularAnimation::init(unsigned long t)
{
	this->startTime=t;
	this->doReset=false;
}