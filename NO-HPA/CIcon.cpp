#include "CIcon.h"

CIcon::CIcon(irr::IrrlichtDevice* tp_Device)
{
	this->p_Device = tp_Device;
};


//set texture

void CIcon::setIconTexture(irr::io::path filePath)
{
	//load the texture for the icon
	this->iconTexture=this->p_Device->getVideoDriver()->getTexture(filePath.c_str());
}

void CIcon::setTextureFor2DMap(irr::io::path filePath)
{
	//load the texture for the icon
	this->textureFor2DMap=this->p_Device->getVideoDriver()->getTexture(filePath.c_str());
}

void CIcon::setIconPosition(irr::core::vector2d<irr::s32> t_Position)
{

	this->iconPos = t_Position;

}

//get texture and position

irr::core::vector2d<irr::s32>* CIcon::getIconPosition()
{
	return &(this->iconPos);
}

irr::video::ITexture* CIcon::returnIconTexture()
{
	return this->iconTexture;
}

irr::video::ITexture* CIcon::returnTextureFor2DMap()
{
	return this->textureFor2DMap;
}

//rectangle setting and retrival
void CIcon::setIconRectangle(irr::core::rect<irr::s32> t_Rect)
{
	this->iconRectangle = t_Rect;
}

irr::core::rect<irr::s32>* CIcon::getIconRectangle()
{
	return &(this->iconRectangle);
}



//get set icon numbers
void CIcon::setIconNumber(int num)
{
	this->iconNumber = num;
}

int CIcon::getIconNumber()
{
	return this->iconNumber;
}

//get set icon name
void CIcon::setIconName(irr::core::stringw iconnm)
{
	this->iconName = iconnm;
}

irr::core::stringw* CIcon::getIconName()
{

	return &this->iconName;
}

