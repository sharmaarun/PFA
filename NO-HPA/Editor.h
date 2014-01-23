#ifndef _Editor_
#define _Editor_

#include "irrlicht.h"
#include "HPAMap.h"
#include "CEventReceiver.h"
#include "CIcon.h"
#include <iostream>
#include <fstream>



class CEditor
{

private:

		irr::IrrlichtDevice* p_Device;
		CIcon** p_WalkableIconsArray; 	//array of icons used in editor mode
		CIcon** p_ObstacleIconsArray;

		MapSystem::HPAMap* p_MainMap;			//pointer to the main empty map (HPA map)
		CEventReceiver* p_EventReceiver;
		irr::gui::IGUIFont** editorFont;
		CSettings* p_Settings;
		//normal icons and map settings

		irr::video::ITexture* currentIconTextureToPlaceOnMap;		//icon texture that will be printed over the currently selected node in 2d map
		int currentSelectedIconNumber;
		int distanceFromTop;
		int walkableIconsRowPos;
		int obstacleIconsRowPos;

		int mapOffset_X,mapOffset_Y;

		//gui buttons
		
		//irr::gui::IGUIButton* buttonOpenMap;



public:
		
	//construct the editor world
	CEditor(irr::IrrlichtDevice* tp_Device,CSettings* tp_Settings);
	void setEventReceiver(CEventReceiver* t_EventReceiver);
	//member functions 
	void initEditorWorld( MapSystem::HPAMap* tp_MainMap);		//initialize the editor world based on the empty map
	void drawEditorWorld();


	//other functions
	MapSystem::HPAMap* readMapFromFile(irr::core::stringw t_FilePath);
	bool saveCurrentMapAsFile(irr::core::stringw fileName);
	CIcon* getIconByNumber(int num);

};



#endif