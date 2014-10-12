#ifndef LIGHT_H
#define LIGHT_H

#include <CGFlight.h>
#include <string>

using namespace std;

class Light:public CGFlight{

public:
	Light(unsigned int number, string id,string type,bool enabled, bool marked, float pos[4],float amb[4],float dif[4], float spe[4]); // for omni
	Light(unsigned int number, string id,string type,bool enabled, bool marked, float pos[4],float tar[3],float angle, float exponent, float amb[4],float dif[4], float spe[4]); // for spot
	string id,type;
	unsigned int number;
	bool enabled,marked;
	float /*pos[4],*/tar[3],angle,exponent,amb[4],dif[4],spe[4];
};

#endif
