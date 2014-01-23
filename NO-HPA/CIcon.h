#ifndef _CIcon_
#define _CIcon_

#include "irrlicht.h"


class CIcon
{
private:
	irr::IrrlichtDevice* p_Device;
	irr::video::ITexture* iconTexture;
	irr::video::ITexture* textureFor2DMap;
	irr::core::vector2d<irr::s32> iconPos;
	irr::core::rect<irr::s32> iconRectangle;
	int iconNumber;
	irr::core::stringw iconName;

public:
	CIcon(irr::IrrlichtDevice* tp_Device);
	void setIconTexture(irr::io::path filePath);
	void setTextureFor2DMap(irr::io::path filePath);
	void setIconPosition(irr::core::vector2d<irr::s32> t_Position);
	irr::video::ITexture* returnIconTexture();
	irr::video::ITexture* returnTextureFor2DMap();
	irr::core::vector2d<irr::s32>* getIconPosition();
	void setIconRectangle(irr::core::rect<irr::s32> t_Rect);
	irr::core::rect<irr::s32>* getIconRectangle();

	void setIconNumber(int num);
	int getIconNumber();

	void setIconName(irr::core::stringw iconnm);
	irr::core::stringw* getIconName();

	
};


#endif
