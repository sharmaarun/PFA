#ifndef _Environment3D_
#define _Environment3D_


#include "MapLoader3D.h"
#include "HPAMap.h"
#include "GlobalVars.h"
#include "CEventReceiver.h"
#include "CPlayer.h"
#include "PathFinder.h"

class Environment3D
{

private:

	//pointers to device , maploader , character etc
	irr::IrrlichtDevice* p_Device;
	MapLoader3D* p_Map3D;
	CSettings* p_Settings;
	CEventReceiver* p_EventReceiver;
	irr::scene::ICameraSceneNode* p_Cam;

	CPlayer* player;

	MapSystem::CPathFinder *pathFinderMain;
	std::vector<MapSystem::Node*> pathList;

public:

	Environment3D(irr::IrrlichtDevice* tp_Device,CSettings* tp_Settings,CEventReceiver* tp_EventReceiver,irr::scene::ICameraSceneNode* tp_Cam);

	void initEnvironment();
	void drawEnvironment3D();

};


#endif