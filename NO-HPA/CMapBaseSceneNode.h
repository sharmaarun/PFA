#ifndef _MapBaseSceneNode_
#define _MapBaseSceneNode_

#include "irrlicht.h"
#include "HPAMap.h"


class CMapBaseSceneNode : public irr::scene::IMeshSceneNode
{
private:

	irr::core::aabbox3d<irr::f32>	boundingBox;
	irr::video::S3DVertex			Vertices[4];
	irr::video::SMaterial			materialMain;
	irr::video::ITexture*			tex;

public:

	CMapBaseSceneNode(irr::scene::ISceneNode* parentNode,irr::scene::ISceneManager* smgr, irr::s32 id, MapSystem::HPAMap* tp_Map) : irr::scene::IMeshSceneNode(parentNode,smgr,id)
	{

		

		this->materialMain.Wireframe = false;
	this->materialMain.Lighting = false;
	this->materialMain.BackfaceCulling=false;

	irr::f32 x1,x2,x3,x4;
	irr::f32 y1,y2,y3,y4;

	x1 = 0.0f;
	y1 = 0.0f;

	x2 = tp_Map->mapWidth*tp_Map->nodeWidth;
	y2 = 0.0f;

	x3 = tp_Map->mapWidth*tp_Map->nodeWidth;
	y3 = tp_Map->mapHeight*tp_Map->nodeHeight;

	x4 = 0.0f;
	y4 = tp_Map->mapHeight*tp_Map->nodeHeight;

	this->Vertices[0] = irr::video::S3DVertex(x1,0,y1,0,-1,0,irr::video::SColor(255,255,255,255),0,0);
	this->Vertices[1] = irr::video::S3DVertex(x2,0,y2,0,-1,0,irr::video::SColor(255,255,255,255),1,0);
	this->Vertices[2] = irr::video::S3DVertex(x3,0,y3,0,-1,0,irr::video::SColor(255,255,255,255),1,1);
	this->Vertices[3] = irr::video::S3DVertex(x4,0,y4,0,-1,0,irr::video::SColor(255,255,255,255),0,1);

	boundingBox.reset(Vertices[0].Pos);
	for(int i=0;i<4;i++)
		boundingBox.addInternalPoint(Vertices[i].Pos);

	tex = SceneManager->getVideoDriver()->getTexture("../data/textures/basegrass.jpg");
	};

	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);

};



#endif
