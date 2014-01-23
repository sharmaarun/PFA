#ifndef _CEventReceiver_
#define _CEventReceiver_

#include "irrlicht.h"
#include <iostream>
#include "GlobalVars.h"



class CEventReceiver : public irr::IEventReceiver
{
private:

	
	irr::IrrlichtDevice*		p_Device;					//irrlicht device pointer
	//pointer to settings opbject
	CSettings* p_Settings;

	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];				//create array to check which keys are pressed at a time
	bool MouseIsDown[2];
	

public:

	CEventReceiver();		//default cunstru
	CEventReceiver(irr::IrrlichtDevice* tp_Device,CSettings* tp_Settings);

	//override the base class function to receive events
	virtual bool OnEvent(const irr::SEvent& events);

	bool isKeyDown(irr::EKEY_CODE keyCode);
	bool isMouseDown(int mouseButton);

};

#endif
