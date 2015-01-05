#include "DemoScene.h"
#include "DemoInterface.h"
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

DemoInterface::DemoInterface()
{
}

void DemoInterface::initGUI()
{
	this->pieceSelected=false;
	scorep1=0;
	scorep2=0;
	glutReshapeWindow(680,550);
	GLUI_Panel *masterPanel=addPanel("Interface",GLUI_PANEL_RAISED);
	addStaticTextToPanel(masterPanel,"Interface");
	int atual=2;
	GLUI_Panel *globalPanel= addPanelToPanel(masterPanel,"Globals", 1);
	GLUI_RadioGroup * g1 = addRadioGroupToPanel(globalPanel,&(((DemoScene *) scene)->drawMode),1);
	addRadioButtonToGroup(g1,"Fill");
	addRadioButtonToGroup(g1,"Wireframe");
	addRadioButtonToGroup(g1,"Point");

	addColumnToPanel(masterPanel);
	addStaticTextToPanel(masterPanel,"");
	GLUI_Panel *cameraPanel= addPanelToPanel(masterPanel,"Cameras",1);
	GLUI_RadioGroup * g2 = addRadioGroupToPanel(cameraPanel,&(((DemoScene*) scene)->activeCameraNumber),atual);
	atual++;
	map<string,Camera *>::const_iterator it;

	for(it=((DemoScene*) scene)->cameras.begin();it!=((DemoScene*) scene)->cameras.end();it++){
		addRadioButtonToGroup(g2,(char*)it->second->id.c_str());
	}

	addColumnToPanel(masterPanel);
	addStaticTextToPanel(masterPanel,"");
	GLUI_Panel *lighPanel=addPanelToPanel(masterPanel,"Lights",1);
	for(unsigned int i=0;i<((DemoScene *) scene)->graphLights.size();i++){
		addCheckboxToPanel(lighPanel,(char*)((DemoScene *) scene)->graphLights.at(i)->id.c_str(),(int *)&((DemoScene *) scene)->graphLights.at(i)->state,atual);
	}
	atual++;

	atual++;
	addColumnToPanel(masterPanel);
	GLUI_Panel * ambientPanel=addPanelToPanel(masterPanel,"Game Ambient",1);
	GLUI_RadioGroup * amb=addRadioGroupToPanel(ambientPanel,&((DemoScene *) scene)->theme,atual);
	atual++;
	addRadioButtonToGroup(amb,"Wood");
	addRadioButtonToGroup(amb,"Mineral");
	addRadioButtonToGroup(amb,"Aquatic");




	GLUI_Panel * gameTimePanel = addPanel("Game Time",GLUI_PANEL_EMBOSSED);
	GLUI_Panel * timePanel = addPanelToPanel(gameTimePanel,"Game Time",1);
	GLUI_EditText * time = addEditTextToPanel(timePanel,"Current Game Time", &((DemoScene *) scene)->gameTime,1);

	GLUI_Panel * gamePanel = addPanel("Game Status",GLUI_PANEL_EMBOSSED);
	GLUI_Panel * statusPanel = addPanelToPanel(gamePanel,"Game Status",1);
	gameStatus = addStaticTextToPanel(statusPanel,"Game Status");
	char c[128];
	sprintf(c, "Current player: %d | Game score: %d - %d \n ", &((DemoScene *) scene)->player,scorep1,scorep2);
	gameStatus->set_text(c);
	addColumnToPanel(gamePanel);


	GLUI_Panel * difPanel = addPanelToPanel(gamePanel,"Game Difficulty",1);
	GLUI_RadioGroup * dif=addRadioGroupToPanel(difPanel,0,atual);
	atual++;
	addRadioButtonToGroup(dif,"Easy");
	addRadioButtonToGroup(dif,"Medium");
	addRadioButtonToGroup(dif,"Hard");	


	addColumnToPanel(gamePanel);
	GLUI_Panel * modePanel = addPanelToPanel(gamePanel,"Game Mode",1);
	GLUI_RadioGroup * mode=addRadioGroupToPanel(modePanel,&((DemoScene *) scene)->gameMode,atual);
	atual++,
	addRadioButtonToGroup(mode,"Hum vs. Hum");
	addRadioButtonToGroup(mode,"Hum vs. CPU");
	addRadioButtonToGroup(mode,"CPU vs. CPU");



	addColumnToPanel(gamePanel);
	GLUI_Panel * buttonPanel = addPanelToPanel(gamePanel,"");
	GLUI_Button * undoButton=addButtonToPanel(buttonPanel,"Undo Move",atual);
	atual++;
	GLUI_Button * replayButton=addButtonToPanel(buttonPanel,"Replay last game",atual);
	atual++;
	GLUI_Button * startButton=addButtonToPanel(buttonPanel,"Start Game",atual);
	atual++;

}
void DemoInterface::updateStatus()
{
	char c[128];
	sprintf(c, "Current player: %d | Game score: %d - %d \n ", ((DemoScene *) scene)->player,scorep1,scorep2);
	gameStatus->set_text(c);
}

void DemoInterface::processGUI(GLUI_Control *ctrl)
{
	printf("%d\n",ctrl->user_id);
	if(ctrl->user_id == 2)
		((DemoScene*) scene)->processCameras();
	if(ctrl->user_id == 3)
		((DemoScene*) scene)->setLights();
	if(ctrl->user_id == 5)
		((DemoScene*) scene)->changeTheme();
	if(ctrl->user_id == 6)
		printf("AI difficulty changed\n");
	if(ctrl->user_id == 7)
		printf("Game mode\n");
	if(ctrl->user_id == 8)
		printf("Undo\n");
	if(ctrl->user_id == 9)
		printf("Replay\n");
	if(ctrl->user_id == 10){
		printf("Starting Game\n");
		((DemoScene*) scene)->gameStarted=true;
		((DemoScene*) scene)->gameInit = true;
		((DemoScene*) scene)->m.envia("initialize.\n",strlen("initialize.\n"));
		char s[255];
		((DemoScene*) scene)->m.recebe(s);
		printf("%s\n",s);
	}
}

void DemoInterface::verificarTermino(int player){
	ostringstream converter2;
	converter2.str("");
	converter2 << "avalia(";
	if(player == 1){
		converter2 << player+1;
	}
	else {
		converter2 << player-1;	
	}
	converter2 << "," << ((DemoScene*) scene)->board->toString() << ").\n";
	string message2;
	message2 = converter2.str();
	((DemoScene*) scene)->m.envia((char*)message2.c_str(),strlen(message2.c_str()));
	char res2[255];
	((DemoScene*) scene)->m.recebe(res2);
	printf("%s\n",res2);
	if(strcmp(res2,"0\r") == 0){
		printf("jogador %d ganhou\n",player);
		if(player==1)
			scorep1++;
		else
			scorep2++;
		((DemoScene*) scene)->board=new Board();
	}
}

void DemoInterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}


void DemoInterface::performPicking(int x, int y)
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);
	// Initialize the picking name stack
	glInitNames();
	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);
	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();
	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);
	// reset projection matrix
	glLoadIdentity();
	// get current viewport and use it as reference for
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);
	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);
	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	((DemoScene*) scene)->display();
	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glFlush();
	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void DemoInterface::processHits (GLint hits, GLuint buffer[])
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
			printf("%d ",selected[i]);
		printf("\n");
		if(nselected==3){
			if(selected[2]>=100)
				selected[2]-=100;
			if(pieceSelected){
				if(((DemoScene*) scene)->board->selected(selected[1],selected[2])){
					((DemoScene*) scene)->board->selectedColumn=500;
					((DemoScene*) scene)->board->selectedRow=500;
					pieceSelected=false;
				}
				else{
						if(((DemoScene*) scene)->gameMode == 0 ||((DemoScene*) scene)->gameMode == 1 && ((DemoScene*) scene)->player == 1){
						((DemoScene*) scene)->board->targetColumn=selected[2];
						((DemoScene*) scene)->board->targetRow=selected[1];
						ostringstream converter;
						converter << "execute(jogada," << ((DemoScene*) scene)->player << "," << ((DemoScene*) scene)->board->selectedColumn+1 << "," << ((DemoScene*) scene)->board->selectedRow+1 << "," << selected[2]+1 << "," << selected[1]+1 << "," << ((DemoScene*) scene)->board->toString() << ").\n";
							string message;
							message = converter.str();
							((DemoScene*) scene)->m.envia((char*)message.c_str(),strlen(message.c_str()));
							char res[255];
							((DemoScene*) scene)->m.recebe(res);
							printf("%s\n",res);
							string inv = "invalid.\r";
							if(inv.compare(res)!=0){
								((DemoScene*) scene)->board->movePiece();

								// verificar quem ganhou e jogador seguinte

								if(((DemoScene*) scene)->player == 1){
									verificarTermino(((DemoScene*) scene)->player);
									((DemoScene*) scene)->player++;
								}
								else{					
									verificarTermino(((DemoScene*) scene)->player);
									((DemoScene*) scene)->player = 1;
								}
							}
						pieceSelected=false;
						
						}
				}
			}
			else{
				if(((DemoScene*) scene)->board->pieces[selected[1]][selected[2]]==1 && ((DemoScene*) scene)->player == 1 || ((DemoScene*) scene)->board->pieces[selected[1]][selected[2]]==2 && ((DemoScene*) scene)->player == 2){
					((DemoScene*) scene)->board->selectedColumn=selected[2];
					((DemoScene*) scene)->board->selectedRow=selected[1];
					pieceSelected=true;
					if(((DemoScene*) scene)->primeiraJogada){
						string status_board = ((DemoScene *) scene)->board->toString();
						ostringstream converter;
						if(((DemoScene*) scene)->player == 1){
							converter << "execute(primeiraJogada," << selected[2]+1 << "," << selected[1]+1 << "," << status_board << ").\n";
							string message;
							message = converter.str();
							((DemoScene*) scene)->m.envia((char*)message.c_str(),strlen(message.c_str()));
							char res[255];
							((DemoScene*) scene)->m.recebe(res);
							printf("%s\n",res);
							string inv = "invalid.\r";
							if(inv.compare(res)!=0){
								((DemoScene*) scene)->board->pieces[selected[1]][selected[2]] = 0;
								((DemoScene*) scene)->linhaPrimeira = selected[1];
								((DemoScene*) scene)->colunaPrimeira = selected[2];
								pieceSelected = false;
								((DemoScene*) scene)->player++;
							}
						}
						else{
							converter << "execute(primeiraJogada," << selected[2]+1 << "," << selected[1]+1 << "," << ((DemoScene*) scene)->colunaPrimeira+1 << "," << ((DemoScene*) scene)->linhaPrimeira+1 << "," << status_board << ").\n";
							string message;
							message = converter.str();
							((DemoScene*) scene)->m.envia((char*)message.c_str(),strlen(message.c_str()));
							char res[255];
							((DemoScene*) scene)->m.recebe(res);
							printf("%s\n",res);
							string inv = "invalid.\r";
							if(inv.compare(res)!=0){
								((DemoScene*) scene)->board->pieces[selected[1]][selected[2]] = 0;
								((DemoScene*) scene)->linhaPrimeira = selected[1];
								((DemoScene*) scene)->colunaPrimeira = selected[2];
								pieceSelected = false;
								((DemoScene*) scene)->player = 1;
								((DemoScene*) scene)->primeiraJogada = false;
							}
						}
					}
				}
			}
			
		updateStatus();
		}
	}
	else
		printf("Nothing selected while picking \n");	
}