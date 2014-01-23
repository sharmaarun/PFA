#include "CMapBaseSceneNode.h"





void CMapBaseSceneNode::OnRegisterSceneNode()
{
	if(IsVisible)
		this->SceneManager->registerNodeForRendering(this);

	irr::scene::ISceneNode::OnRegisterSceneNode();
}


void CMapBaseSceneNode::render()
{
	irr::u16  indeces[] = {0,1,2, 0,2,3};

	

	this->setMaterialTexture(0,this->tex);
	
	SceneManager->getVideoDriver()->setMaterial(materialMain);
	SceneManager->getVideoDriver()->setTransform(irr::video::ETS_WORLD, this->AbsoluteTransformation);
	SceneManager->getVideoDriver()->drawIndexedTriangleList(&Vertices[0],4,&indeces[0],2);
}

const irr::core::aabbox3d<irr::f32>& CMapBaseSceneNode::getBoundingBox() const
{
	return this->boundingBox;
}

irr::u32 CMapBaseSceneNode::getMaterialCount() const
{
        return 1;
}

irr::video::SMaterial& CMapBaseSceneNode::getMaterial(irr::u32 i)
{
	return this->materialMain;
}    