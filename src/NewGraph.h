#ifndef _NEW_GRAPH_H
#define _NEW_GRAPH_H

#include <map>
#include <string>
#include <vector>
#include "VisualObject.h"
#include "Camera.h"
#include "Light.h"
#include "Appearance.h"

using std::map;
using std::string;
using std::vector;

class NewNode;

struct Texture{
	string id;
	string file;
	float texlength_s;
	float texlength_t;
};

class NewGraph
{
public:
	NewGraph(void);
	~NewGraph(void);
	void draw();
	map<string,NewNode> nodes;
	map<string,Camera> cameras;
	map<string,Texture> textures;
	map<string,Appearance> appearances;
	vector<Light*> lights;
	string rootNode;
};

class NewNode
{
public:
	NewNode(void);
	~NewNode(void);
	NewNode(string id);
	void draw(NewGraph * graph);
	string id;
	bool inherited;
	Appearance * appear;
	GLfloat matrix[16];
	vector<string> childs;
	vector<VisualObject*> primitives;
};
#endif
