#ifndef _GameLogic_
#define _GameLogic_

#include "irrlicht.h"
#include "Editor.h"
#include "Environment3D.h"
#include "HPAMap.h"
#include "CEventReceiver.h"



//game states
enum GAME_STATES
	{
		GS_EDITOR = 1,
		GS_PLAYMODE
	};

class GameLogic
{

private :
	
	irr::IrrlichtDevice* p_Device;	//pointer to the game device (irrlicht's device)
	//other temporary pointers to video driver , scene manager etc
	irr::video::IVideoDriver* p_VideoDriver;
	irr::scene::ISceneManager* p_SceneManager;

	CEditor* editorWorld;
	Environment3D* gameWorld;
	CSettings* p_Settings;
	CEventReceiver* mainEventReceiver;
	GAME_STATES currentGameState;

	//for playmode
	irr::scene::ICameraSceneNode* currentCamera;

	//fps
	int fps;
	int oldFps;

public :

	//create enumrator type for various game states
	

	GameLogic(irr::IrrlichtDevice* tp_Device);
	void initializeGame(GAME_STATES gs,MapSystem::HPAMap* tempMap,CSettings* tp_Settings);			//initialize the game components
	void logicLoop();				//main game logic loop (must be put under the irrlicht's while loop

	irr::video::IVideoDriver* getVideoDriver();
	irr::scene::ISceneManager* getSceneManager();
	
	
};

#endif