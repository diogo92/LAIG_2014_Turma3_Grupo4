#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "XMLScene.h"
#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFapplication.h"
#include "CGFaxis.h"
#include "Graph.h"
#include "GameSocket.h"
#include <map>
#include <string>
#include <typeinfo>
#include <time.h>


class DemoScene : public CGFscene
{
public:
	gameSocket m;
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
	void setGlobals(const GlobalData &globals);
	void setCamera();
	void initLights();
	void setLights();
	int drawMode;
	int activeCameraNumber;
	int wind;
	int updatePer;
	vector<CGFlight* > lights;
	vector<Light* > graphLights;
	map<string,Camera *> cameras;
	void setLightVector();
	void processCameras();
	void setAnfFileName(char *filename,unsigned int size);
	void changeTheme();
	int theme;
	int gameMode;
	Board * board;
	bool gameStarted;
	bool gameInit;
	int player;
	bool primeiraJogada;
	int linhaPrimeira;
	int colunaPrimeira;
	int gameTime;
private:
};

#endif