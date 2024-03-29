#include "Light.h"

Light::Light(unsigned int number, string id,string type,bool enabled, bool marked,float pos[4],float amb[4],float dif[4], float spe[4]){
	this->number=number;
	this->id=id;
	this->type=type;
	this->enabled=enabled;
	this->marked=marked;
	for(int i=0;i<4;i++){
		this->amb[i]=amb[i];
		this->dif[i]=dif[i];
		this->spe[i]=spe[i];
		this->pos[i]=pos[i];
	}
	if(enabled)
		state=1;
	else state=0;
};

Light::Light(unsigned int number, string id,string type,bool enabled, bool marked,float pos[4],float tar[3],float angulo, float exponente, float amb[4],float dif[4], float spe[4]){
	this->number=number;
	this->id=id;
	this->type=type;
	this->enabled=enabled;
	this->marked=marked;
	this->angulo=angulo;
	this->expoente=exponente;
	for(int i=0;i<4;i++){
		this->amb[i]=amb[i];
		this->dif[i]=dif[i];
		this->spe[i]=spe[i];
		this->tar[i]=tar[i];
		this->pos[i]=pos[i];
	}
	if(enabled)
		state=1;
	else state=0;
}
