


#include "irrlicht.h"
#include "GlobalVars.h"
#include "MapManager.h"
#include "GameLogic.h"
#include <conio.h>
#include "CEventReceiver.h"
#include <iostream>


#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace std;

using namespace irr;
using namespace gui;
using namespace core;
using namespace io;
using namespace video;
using namespace scene;
using namespace MapSystem;

int main(char *argc,char **argv)
{

	CSettings settingsMain;

	HPAMap *mainMap;

	int choice;
	int tH , tW;

	cout<<"__________________NO-HPA*___________________\n\n";
	cout<<"Enter the choice :\n1)Map Creation Mode \n2)PlayMode\n\n";
	
	cin>>choice;

	switch(choice)
	{
	case 1:
		cout<<"\nEnter the width :\t";
		cin>>tW;
		cout<<"\nEnter the Height :\t";
		cin >>tH;

		if((tW<3 || tH<3) || (tW>42 ||tH>24)) 
		{
			cout<<"Invalid Height and Width (both should be in range (width : 3-42 , height : 3-24)) ";
			_getch();
			return 0;
		};
		
		 mainMap = new HPAMap(tW,tH,50,50);
		 break;
	case 2:

		//exit(0);
		break;
	default:
		exit(0);
		
	};

	if(choice==1)
	{
		if(!mainMap->InitMap())
		{
			cout<<"Error";
			_getch();
			return 0;
		}
	}
	else
	{
		mainMap = new HPAMap(1,1,1,1);
	}
	
	

	IrrlichtDevice* device;
	

	//initialize device
	if(choice==1)
	{
	 device = createDevice(EDT_OPENGL,dimension2d<u32>(1000,700),16U,false,false,false);
	}
	else
	{
		device = createDevice(EDT_OPENGL,dimension2d<u32>(1000,700),16U,false,true,false);
	}
	if(!device)
		return 0;
	
	device->setResizable(true);

	GameLogic* mainGameLogic = new GameLogic(device);

	device->setWindowCaption(L"NO-HPA");
	
	mainGameLogic->initializeGame((GAME_STATES)choice,mainMap,&settingsMain);


	while(device->run() && mainGameLogic->getVideoDriver())
	{
		if(device->isWindowActive())
		{
		mainGameLogic->getVideoDriver()->beginScene(true,true,SColor(255,100,100,100));
		mainGameLogic->logicLoop();
		
		mainGameLogic->getVideoDriver()->endScene();
		}
	}
	
	
	device->drop();
	return 0;
}