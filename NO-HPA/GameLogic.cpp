#include "GameLogic.h"


GameLogic::GameLogic(irr::IrrlichtDevice* tp_Device)
{
	if(!tp_Device)
		exit(0);
	this->p_Device = tp_Device;							//make the pointer point to main device
	//init other pointers too
	this->p_VideoDriver = this->p_Device->getVideoDriver();
	this->p_SceneManager = this->p_Device->getSceneManager();

	oldFps=-1;


}


//return the video driver
irr::video::IVideoDriver* GameLogic::getVideoDriver()
{
	if(!this->p_VideoDriver)
		return NULL;
	
	return this->p_VideoDriver;
}

//return the scene manager
irr::scene::ISceneManager* GameLogic::getSceneManager()
{
	if(!this->p_SceneManager)
		return NULL;
	
	return this->p_SceneManager;
}



void GameLogic::initializeGame(GAME_STATES gs,MapSystem::HPAMap* tempMap,CSettings* tp_Settings)
{
	//init and set eventreceiver for the deive
	this->p_Settings = tp_Settings;
	this->mainEventReceiver = new CEventReceiver(this->p_Device,tp_Settings);
	this->p_Device->setEventReceiver(mainEventReceiver);

	this->currentGameState = gs;			//set startup game state to be editor mode

	if(gs==GS_EDITOR)
	{
		this->editorWorld = new CEditor(this->p_Device,tp_Settings);
		this->editorWorld->initEditorWorld(tempMap);					//set hpa map pointer for editor world
		this->editorWorld->setEventReceiver(this->mainEventReceiver);
	}

	if(gs==GS_PLAYMODE)
	{
		
		this->p_Device->getGUIEnvironment()->getSkin()->setFont(this->p_Device->getGUIEnvironment()->getFont("../data/fonts/editorFont.xml"));
		this->p_Device->getGUIEnvironment()->addFileOpenDialog(L"Open .map file");
		

		//add a camera to the 3d world 
		this->currentCamera=this->p_SceneManager->addCameraSceneNodeFPS(0,50.0f,0.1f);
		currentCamera->setTarget(irr::core::vector3df(5.0f,0.0f,0.0f));
		
		this->gameWorld = new Environment3D(this->p_Device,tp_Settings,this->mainEventReceiver,currentCamera);
		

		

	}

		//set event receiver for the editor world

}





void GameLogic::logicLoop()
{
	//main game logic goes here

	fps=p_Device->getVideoDriver()->getFPS();
	if(fps!=oldFps)
	{
		irr::core::stringw fpstr;
		fpstr+="FPS : ";
		fpstr+=fps;
		this->p_Device->setWindowCaption(fpstr.c_str());
		oldFps=fps;
	}

	this->p_SceneManager->drawAll();

	if(this->currentGameState==GS_EDITOR)
	{

		this->editorWorld->drawEditorWorld();
		
	}
	if(this->currentGameState==GS_PLAYMODE)
	{

		this->gameWorld->drawEnvironment3D();
		
	}

	this->p_Device->getGUIEnvironment()->drawAll();




	//custom logic code ends

	//draw all scn manager content
	
	
	
}

