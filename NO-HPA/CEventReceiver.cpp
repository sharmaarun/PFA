#include "CEventReceiver.h"


//event receiver's default constructor
CEventReceiver::CEventReceiver()
{
	for(int i=0;i<255;i++)
	{
		this->KeyIsDown[i]=0;		//initialize all keys to 0 (0 means not pressed)
	}

	for(int i=0;i<2;i++)
		this->MouseIsDown[i]=0;		//init the mouse keys (0 means not pressed)
};

CEventReceiver::CEventReceiver(irr::IrrlichtDevice* tp_Device,CSettings* tp_Settings)
{


	for(int i=0;i<255;i++)
	{
		this->KeyIsDown[i]=0;		//initialize all keys to 0 (0 means not pressed)
	}

	for(int i=0;i<2;i++)
		this->MouseIsDown[i]=0;		//init the mouse keys (0 means not pressed)
	//initialize the device pointer
	this->p_Device = tp_Device;
	this->p_Settings = tp_Settings;

}



bool CEventReceiver::OnEvent(const irr::SEvent& events)
{
	
	
	//capture the key input events
	if(events.EventType==irr::EET_KEY_INPUT_EVENT)
	{

		this->KeyIsDown[events.KeyInput.Key] = events.KeyInput.PressedDown;
		
		//some functions to handle here based on gui events like file open etc

		if(events.KeyInput.Key==irr::KEY_KEY_S && events.KeyInput.PressedDown==false)
		{
			if(this->p_Settings->getSFlag())
			this->p_Settings->setDestSelFlag(true);
			

		}
		if(events.KeyInput.Key==irr::KEY_KEY_H && events.KeyInput.PressedDown==false)
		{
			
			if(this->p_Settings->getHelpFlag())
			{
				this->p_Settings->setHelpFlag(false);
			}
			else
			{
				this->p_Settings->setHelpFlag(true);
			}

		}
		if(events.KeyInput.Key==irr::KEY_ESCAPE && events.KeyInput.PressedDown==false)
		{
			exit(0);
		}


		//return true;

	}

	if(events.EventType==irr::EET_GUI_EVENT)
	{

		if(events.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
			if(events.GUIEvent.Caller->getID()==ID_FILE_OPEN_BUTTON)
			{
				
				this->p_Device->getGUIEnvironment()->addFileOpenDialog(L"Open Map File...");
				
			}
			if(events.GUIEvent.Caller->getID()==ID_FILE_SAVE_BUTTON)
			{
				char fname[40];
				std::cout<<"Enter file name\t:\t";
				std::cin>>fname;
				this->p_Settings->setFileToSave(fname);
				this->p_Settings->setFileSaveFlag(true);
				
			}

			

		}

		if(events.GUIEvent.EventType == irr::gui::EGET_FILE_SELECTED)
		{

			irr::gui::IGUIFileOpenDialog* t_Dialog = (irr::gui::IGUIFileOpenDialog*)events.GUIEvent.Caller;
			if(t_Dialog->getFileName()!=NULL)
			{
				this->p_Settings->setFileToOpen(t_Dialog->getFileName());
				this->p_Settings->setFileOpenFlag(true);
				this->p_Device->setWindowCaption(t_Dialog->getFileName());
			}

			
		}
		
	}

	



	//capture mouse input invents
	if(events.EventType==irr::EET_MOUSE_INPUT_EVENT)
	{
		if(events.MouseInput.isLeftPressed())
			this->MouseIsDown[0]=true;
		else
			this->MouseIsDown[0]=false;


		if(events.MouseInput.isRightPressed())
			this->MouseIsDown[1]=true;
		else
			this->MouseIsDown[1]=false;

		
	}

	return false;
}


//check which key is down
bool CEventReceiver::isKeyDown(irr::EKEY_CODE keyCode)			
{

	return this->KeyIsDown[keyCode];

}


//check is mouse is pressed
bool CEventReceiver::isMouseDown(int mouseButton)
{
	return this->MouseIsDown[mouseButton];
}