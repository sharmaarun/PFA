#include "CPlayer.h"

CPlayer::CPlayer(irr::IrrlichtDevice* t_Device,irr::core::vector3df tPos)
{
	
	this->playerSceneNode = t_Device->getSceneManager()->addAnimatedMeshSceneNode(t_Device->getSceneManager()->getMesh("../data/models/sydney.md2"),t_Device->getSceneManager()->getRootSceneNode(),this->playerID,tPos);
	this->playerSceneNode->setMaterialTexture(0,t_Device->getVideoDriver()->getTexture("../data/models/sydney.bmp"));
	this->playerSceneNode->setScale(irr::core::vector3df(0.5f,0.5f,0.5f));
	this->playerSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING,false);
	this->playerSceneNode->setMD2Animation(irr::scene::EMAT_STAND);
	//cast shadows
	this->playerSceneNode->addShadowVolumeSceneNode();
	//tMesh->drop();
	this->animType = irr::scene::EMAT_STAND;
	this->animationFlag=false;
		nodeToReach=1;
		stopFlag  = false;
}

irr::scene::IAnimatedMeshSceneNode* CPlayer::getPlayerSceneNode()
{
	return this->playerSceneNode;
}

void CPlayer::setNodeUnderPlayer(MapSystem::Node* tnodeUnderPlayer)
{
	this->nodeUnderPlyaer= tnodeUnderPlayer;
}

MapSystem::Node* CPlayer::getNodeUnderPlayer()
{
	return this->nodeUnderPlyaer;
}