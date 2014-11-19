#include "LinearAnimation.h"


LinearAnimation::LinearAnimation(void)
{
	this->segmento_atual = 0;
	this->ended = false;
	this->angle = 0;
	reset();
}


LinearAnimation::~LinearAnimation(void)
{
}

void LinearAnimation::init(unsigned long t)
{
	this->startTime=t;
	this->doReset=false;
}

void LinearAnimation::apply(){
	glTranslatef(this->dT.x,this->dT.y,this->dT.z);
}

void LinearAnimation::calcValues(){
	cor velocidade;

	this->sector = (this->span) / (this->control_points.size()-1);

	for(unsigned int i = 0; i < this->control_points.size() - 1; i++) {
		velocidade.x =  (float)(control_points[i+1].x-control_points[i].x)/(this->sector/1000);
		velocidade.y =  (control_points[i+1].y-control_points[i].y)/(this->sector/1000);
		velocidade.z =  (control_points[i+1].z-control_points[i].z)/(this->sector/1000);
		velocidades_segmentos.push_back(velocidade);
	}
}

void LinearAnimation::reset()
{
	doReset=true;
}

void LinearAnimation::update(unsigned long t)
{
		if (doReset){
			init(t);
		}
		else
		{
			animT=t-startTime;
			if(animT < (unsigned long)this->sector){
				dT.x = this->control_points.at(segmento_atual).x + velocidades_segmentos.at(segmento_atual).x * ((float)animT/1000);
				dT.y = this->control_points.at(segmento_atual).y + velocidades_segmentos.at(segmento_atual).y * ((float)animT/1000);
				dT.z = this->control_points.at(segmento_atual).z + velocidades_segmentos.at(segmento_atual).z * ((float)animT/1000);
			}
			else{
				init(t);
				segmento_atual++;
				if(segmento_atual >= this->velocidades_segmentos.size()){
					this->segmento_atual = 0;
					this->ended = true;
				}
			}
		}
}