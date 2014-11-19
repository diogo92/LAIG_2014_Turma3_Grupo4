#ifndef _GRAPH_H
#define _GRAPH_H

#include <map>
#include <string>
#include <vector>
#include "VisualObject.h"
#include "Camera.h"
#include "Light.h"
#include "Appearance.h"
#include "Animation.h"

using std::map;
using std::string;
using std::vector;


class Node;

struct Texture{
	string id;
	string file;
	float texlength_s;
	float texlength_t;
};

class Graph
{
public:
	Graph(void);
	~Graph(void);
	void draw();
	map<string,Node> nodes;
	map<string,Camera> cameras;
	map<string,Texture> textures;
	map<string,Appearance> appearances;
	vector<Light*> lights;
	string rootNode;
	vector<Animation * > anims;
};

class Node
{
public:
	Node(void);
	~Node(void);
	Node(string id);
	void draw(Graph * graph);
	void updateAnim(unsigned long t);
	void update(unsigned long t);
	string id;
	bool inherited;
	Appearance * appear;
	GLfloat matrix[16];
	vector<string> childs;
	vector<VisualObject*> primitives;
	GLuint dispList;
	bool displayList;
	void checkList(Graph * graph);
	void animsTransforms();
	unsigned int atualAnim;
	vector<Animation * > anims;
};
#endif
