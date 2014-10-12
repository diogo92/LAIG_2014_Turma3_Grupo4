#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.h"
#include "GraphNode.h"
#include "Appearance.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

#include <map>

using std::map;
using std::string;
using std::vector;

class Graph
{
	struct Texture{
		string id;
		string file;
		float texlength_s;
		float texlength_t;
	};
public:
	Graph(void);
	~Graph(void);
	map<string ,Node> nodes;
	string rootNodeID;
	map<string,GraphNode> graphNodes;
	map<string,Appearance> appearances;
	map<string,Texture> textures;
	map<string,Camera>  cameras;
	vector<Light*> lights;
	void draw();
};

#endif