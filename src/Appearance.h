#ifndef _APPEARENCE_H_
#define _APPEARENCE_H_

#include <string>

using std::string;

class Appearance
{
public:
	Appearance(void);
	Appearance(string id,float shininess, float ambient[4], float diffuse[4], float specular[4]);
	~Appearance(void);
	string id;
	string textureref;
	float shininess;
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

#endif