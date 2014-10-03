#ifndef _APPEARENCE_H_
#define _APPEARENCE_H_

#include <CGFappearance.h>
#include <string>

using std::string;

class Appearance: public CGFappearance
{
public:
	Appearance();
	~Appearance();
	Appearance(string appid,float shininess,float * amb,float * dif, float * spe);
	string id;
};

#endif