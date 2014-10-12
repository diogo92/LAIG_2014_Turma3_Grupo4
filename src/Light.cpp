#include "Light.h"

Light::Light(unsigned int number, string id,string type,bool enabled, bool marked,float pos[4],float amb[4],float dif[4], float spe[4]):CGFlight(number,pos,(0,0,0)){
	this->number=number;
	this->id=id;
	this->type=type;
	this->enabled=enabled;
	this->marked=marked;
	for(int i=0;i<4;i++){
		this->amb[i]=amb[i];
		this->dif[i]=dif[i];
		this->spe[i]=spe[i];
	}
	this->setAmbient(amb);
	this->setDiffuse(dif);
	this->setSpecular(spe);

};

Light::Light(unsigned int number, string id,string type,bool enabled, bool marked,float pos[4],float tar[3],float angle, float exponent, float amb[4],float dif[4], float spe[4]):CGFlight(number,pos,tar){
	this->number=number;
	this->id=id;
	this->type=type;
	this->enabled=enabled;
	this->marked=marked;
	this->angle=angle;
	this->exponent=exponent;
	for(int i=0;i<4;i++){
		this->amb[i]=amb[i];
		this->dif[i]=dif[i];
		this->spe[i]=spe[i];
		this->tar[i]=tar[i];
	}
}
