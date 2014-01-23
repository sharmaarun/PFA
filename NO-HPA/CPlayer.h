#ifndef _CPlayer_
#define _CPlayer_

#include "irrlicht.h"
#include "Node.h"

class CPlayer
{
	irr::scene::IAnimatedMeshSceneNode*		playerSceneNode;//character scenenode
	irr::s32 playerID;
	MapSystem::Node* nodeUnderPlyaer;

public:
	irr::core::vector3df positionMain;
	irr::scene::EMD2_ANIMATION_TYPE animType;
	bool animationFlag;
	int nodeToReach;
	bool stopFlag;
	CPlayer(irr::IrrlichtDevice* t_Device,irr::core::vector3df tPos);
	irr::scene::IAnimatedMeshSceneNode* getPlayerSceneNode();
	void setNodeUnderPlayer(MapSystem::Node* tnodeUnderPlayer);
	MapSystem::Node* getNodeUnderPlayer();
};

#endif