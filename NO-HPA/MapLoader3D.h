#ifndef _MapLoader3D_
#define _MapLoader3D_

#include "irrlicht.h"
#include "HPAMap.h"
#include "CMapBaseSceneNode.h"
#include <fstream>
#include <iostream>


class MapLoader3D
{

private:

	//create pointer to irrlicht device
	irr::IrrlichtDevice* p_Device;
	//create pointer to the loaded 2D map
	MapSystem::HPAMap* p_MainMap;

	//create array of pointers to obstacle and walkable scene meshes
	irr::scene::IAnimatedMesh** p_walkableMeshes;
	irr::scene::IMesh** p_obstacleMeshes;


	//scene nodes for obstacles
	irr::scene::IMeshSceneNode** p_arrayOfSceneNodesWAO;

	//grasss billboards
	irr::scene::IBillboardSceneNode** grassNode;

	//map base
	irr::scene::IAnimatedMesh* mapBase;
	irr::scene::IAnimatedMeshSceneNode* mapBaseNode;

public:

	MapLoader3D();
	MapLoader3D(irr::IrrlichtDevice* tp_Device);			//set device pointer through init
	void setMainDevice(irr::IrrlichtDevice* tp_Device);		//set device pointer through function

	void readMapFromFile(irr::core::stringw t_FilePath);	//map reader(2d)
	void initWAOSceneNodes();
	MapSystem::HPAMap* getMainMap();
	irr::scene::IAnimatedMesh** getWalkableMeshes();
	irr::scene::IMesh** getObstacleMeshes();
	irr::scene::IMeshSceneNode** getArrayOfSceneNodes();
	irr::scene::IAnimatedMeshSceneNode* getMapBaseNode();
};


#endif