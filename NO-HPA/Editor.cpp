#include "Editor.h"

CEditor::CEditor(irr::IrrlichtDevice* tp_Device,CSettings* tp_Settings)
{

	
	
	//set device
	this->p_Device = tp_Device;
	this->p_Settings= tp_Settings;

	
	
	

	//set the font
	this->editorFont = new irr::gui::IGUIFont*[2];
	this->editorFont[0] = this->p_Device->getGUIEnvironment()->getFont("../data/fonts/editorFont.xml");
	this->editorFont[1] = this->p_Device->getGUIEnvironment()->getFont("../data/fonts/headingFont.xml");

	//set gui buttons
	this->p_Device->getGUIEnvironment()->getSkin()->setFont(this->editorFont[0]);
	this->p_Device->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(500,30,580,60),0,ID_FILE_OPEN_BUTTON,L"OPEN MAP");
	this->p_Device->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(600,30,680,60),0,ID_FILE_SAVE_BUTTON,L"SAVE MAP");


	//map offsets
	this->mapOffset_X=70;
	this->mapOffset_Y=210;

	//initialize the icons arrays
	this->p_ObstacleIconsArray = new CIcon*[3];
	this->p_WalkableIconsArray = new CIcon*[2];

	//default icons row position
	this->distanceFromTop=50;
	this->walkableIconsRowPos=50;
	this->obstacleIconsRowPos=320;

	for(int i=0;i<3;i++)
	{

		//set icon numbers
		
		//initialize icons array
		if(i!=2)
		this->p_WalkableIconsArray[i] = new CIcon(tp_Device);
		this->p_ObstacleIconsArray[i] = new CIcon(tp_Device);

		//set rectangles for source texture
		if(i!=2)
		this->p_WalkableIconsArray[i]->setIconRectangle(irr::core::rect<irr::s32>(0,0,50,50));
		this->p_ObstacleIconsArray[i]->setIconRectangle(irr::core::rect<irr::s32>(0,0,50,50));

		//set positions
		if(i!=2)
		this->p_WalkableIconsArray[i]->setIconPosition(irr::core::vector2d<irr::s32>(this->walkableIconsRowPos+(i*60),this->distanceFromTop));
		this->p_ObstacleIconsArray[i]->setIconPosition(irr::core::vector2d<irr::s32>(this->obstacleIconsRowPos+(i*60),this->distanceFromTop));

		if(i!=2)
			this->p_WalkableIconsArray[i]->setIconNumber(i+1);
		this->p_ObstacleIconsArray[i]->setIconNumber(i+3);


	}

	//load icons 
	this->p_WalkableIconsArray[0]->setIconTexture("../data/textures/smgrass.png");			//set large grass icon
	this->p_WalkableIconsArray[1]->setIconTexture("../data/textures/road.png");				//set tree icon
	this->p_ObstacleIconsArray[0]->setIconTexture("../data/textures/lggrass.png");				//set stone icon
	this->p_ObstacleIconsArray[1]->setIconTexture("../data/textures/tree.png");
	this->p_ObstacleIconsArray[2]->setIconTexture("../data/textures/stone.png");
	
	//load textures to draw over the map
	this->p_WalkableIconsArray[0]->setTextureFor2DMap("../data/textures/smgrass_tex.jpg");
	this->p_WalkableIconsArray[1]->setTextureFor2DMap("../data/textures/road_tex.jpg");
	this->p_ObstacleIconsArray[0]->setTextureFor2DMap("../data/textures/lggrass_tex.jpg");
	this->p_ObstacleIconsArray[1]->setTextureFor2DMap("../data/textures/tree_tex.jpg");
	this->p_ObstacleIconsArray[2]->setTextureFor2DMap("../data/textures/stone_tex.jpg");
	//this->p_WalkableIconsArray[1]->setIconTexture("../data/textures/lg.png");

	//set icon names
	this->p_WalkableIconsArray[0]->setIconName(irr::core::stringw("Small Grass - Walkable"));
	this->p_WalkableIconsArray[1]->setIconName(irr::core::stringw("Road - Walkable"));
	this->p_ObstacleIconsArray[0]->setIconName(irr::core::stringw("Large Grass - Obstacle"));
	this->p_ObstacleIconsArray[1]->setIconName(irr::core::stringw("Tree - Obstacle"));
	this->p_ObstacleIconsArray[2]->setIconName(irr::core::stringw("Stone - Obstacle"));

	//set current icon to print on map nodes
	this->currentIconTextureToPlaceOnMap = NULL;
	this->currentSelectedIconNumber = 0;
	
};



void CEditor::setEventReceiver(CEventReceiver* t_EventReceiver)
{
	this->p_EventReceiver = t_EventReceiver;
}



//get icon by its number
CIcon* CEditor::getIconByNumber(int num)
{
	if(this->p_WalkableIconsArray!=NULL && this->p_ObstacleIconsArray!=NULL)
	{
		for(int i=0;i<3;i++)
		{
			if(i!=2)
				if(this->p_WalkableIconsArray[i]->getIconNumber()==num)
					return this->p_WalkableIconsArray[i];

			if(this->p_ObstacleIconsArray[i]->getIconNumber()==num)
				return this->p_ObstacleIconsArray[i];
	
		}
	}
	else
		return NULL;

	return NULL;
}


void CEditor::initEditorWorld(MapSystem::HPAMap* tp_MainMap)
{

	this->p_MainMap = tp_MainMap;		//init empty map pointer

	for(int i=0;i<3;i++)
	{
		if(i!=2)
		this->p_Device->getGUIEnvironment()->addImage(this->p_WalkableIconsArray[i]->returnIconTexture(),*this->p_WalkableIconsArray[i]->getIconPosition());
		
		this->p_Device->getGUIEnvironment()->addImage(this->p_ObstacleIconsArray[i]->returnIconTexture(),*this->p_ObstacleIconsArray[i]->getIconPosition());
	}

	for(int i=0;i<this->p_MainMap->nodesCount;i++)
	{
		//this->p_MainMap->mapArray[i]->showAdjecentNodes();
	}
}

//read map from file
MapSystem::HPAMap* CEditor::readMapFromFile(irr::core::stringw t_FilePath)
{

	std::ifstream read(t_FilePath.c_str());
	if(!read.good())
		return NULL;

	int width,height,nwidth,nheight,nodeCount,nodeNumber,pos2dX,pos2dY,state,textureType;
	float posX,posY;
	read>>width;
	read>>height;
	read>>nwidth;
	read>>nheight;
	read>>nodeCount;

	MapSystem::HPAMap* tempMap = new MapSystem::HPAMap(width,height,(float)nwidth,(float)nheight);

	

	if(!tempMap)
	return NULL;

	tempMap->InitMap();
	
	for(int i=0;i<nodeCount;i++)
	{
		read>>nodeNumber;
		read>>posX;
		read>>posY;
		read>>pos2dX;
		read>>pos2dY;
		read>>state;
		read>>textureType;

		tempMap->mapArray[i]->setWalkableState(state);
		
		

		tempMap->mapArray[i]->setNodeNumber(nodeNumber);
		tempMap->mapArray[i]->setNewNodePosition(irr::core::position2df((irr::f32)posX,(irr::f32)posY));
		tempMap->mapArray[i]->setNewNodePosition_2D(irr::core::vector2d<irr::s32>(pos2dX,pos2dY));
		for(int j=0;j<3;j++)
		{
			if(j!=2)
			{
				if(this->p_WalkableIconsArray[j]->getIconNumber()==textureType)
				{
					tempMap->mapArray[i]->setTexture_2D(this->p_WalkableIconsArray[j]->returnTextureFor2DMap());
					tempMap->mapArray[i]->setTexture2DType(textureType);
				}
			}
			if(this->p_ObstacleIconsArray[j]->getIconNumber()==textureType)
			{
				tempMap->mapArray[i]->setTexture_2D(this->p_ObstacleIconsArray[j]->returnTextureFor2DMap());
				tempMap->mapArray[i]->setTexture2DType(textureType);
			}

		}
		
	}

	return tempMap;

}

//save current map
bool CEditor::saveCurrentMapAsFile(irr::core::stringw fileName)
{
	if(this->p_MainMap!=NULL)
	{
	irr::core::stringw fileToWrite;
	fileToWrite+=L"../GeneratedMaps/";
	fileToWrite+=fileName;
	fileToWrite+=".map";
	
	std::ofstream write(fileToWrite.c_str());

	if(!write.good())
		{
			std::cout<<"Error saving to file";
			return false;
		}
	
	write<<this->p_MainMap->mapWidth<<std::endl;
	write<<this->p_MainMap->mapHeight<<std::endl;
	write<<this->p_MainMap->nodeWidth<<std::endl;
	write<<this->p_MainMap->nodeHeight<<std::endl;
	write<<this->p_MainMap->nodesCount<<std::endl;
	for(int i=0;i<this->p_MainMap->nodesCount;i++)
	{
		write<<this->p_MainMap->mapArray[i]->getNodeNumber()<<std::endl;
		write<<this->p_MainMap->mapArray[i]->getCurrentNodePosition()->X<<std::endl;
		write<<this->p_MainMap->mapArray[i]->getCurrentNodePosition()->Y<<std::endl;
		write<<this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->X<<std::endl;
		write<<this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->Y<<std::endl;
		write<<this->p_MainMap->mapArray[i]->getWalkableState()<<std::endl;

		write<<this->p_MainMap->mapArray[i]->getTexture2DType()<<std::endl;
	}
	}
	std::cout<<"File Saved Successfully!";	
	return true;
}


void CEditor::drawEditorWorld()
{
	
	if(this->p_Settings->getFileOpenFlag())
	{
		delete this->p_MainMap;
		this->p_MainMap = NULL;

		this->p_MainMap = this->readMapFromFile(*this->p_Settings->getFileToOpen());
		
		this->p_Settings->setFileOpenFlag(false);
	}

	if(this->p_Settings->getFileSaveFlag())
	{
		this->saveCurrentMapAsFile(this->p_Settings->getFileToSave()->c_str());
		this->p_Settings->setFileSaveFlag(false);
		
	}

	//get mouse positions x,y
	irr::s32 mousePosX = this->p_Device->getCursorControl()->getPosition().X;
	irr::s32 mousePosY = this->p_Device->getCursorControl()->getPosition().Y;


	//draw headings and subtitles
	this->editorFont[1]->draw(L"NO-HPA EDITOR",irr::core::rect<irr::s32>(100,0,300,50),irr::video::SColor(255,255,255,255),true);
	this->editorFont[0]->draw(L"Walkables",irr::core::rect<irr::s32>(this->walkableIconsRowPos+30,this->distanceFromTop+53,this->walkableIconsRowPos+80,this->distanceFromTop+53),irr::video::SColor(255,255,255,255));
	

	//draw main map(empty)
	
	if(this->p_MainMap!=NULL)
	{
	int tempNodeCounter=0;
	for(int j=0;j<this->p_MainMap->mapHeight;j++)
	{
		
		//draw the nodes
		for(int i=0;i<this->p_MainMap->mapWidth;i++)
		{
			irr::s32 currentNodePos_X = this->mapOffset_X+20*i;
			irr::s32 currentNodePos_Y = this->mapOffset_Y+20*j;
			int currentNodeWidth = 20;
			int currentNodeHeight = 20;

			//std::cout<<currentNodePos_X<<" - "<<currentNodePos_Y<<" - "<<currentNodeWidth<<" - "<<currentNodeHeight<<"\n";
			this->p_MainMap->mapArray[tempNodeCounter]->setNewNodePosition_2D(irr::core::vector2d<irr::s32>(currentNodePos_X,currentNodePos_Y));
			irr::core::rect<irr::s32> *tempRect = new irr::core::rect<irr::s32>((currentNodePos_X-currentNodeWidth/2),currentNodePos_Y-currentNodeHeight/2,currentNodePos_X+currentNodeWidth/2,currentNodePos_Y+currentNodeHeight/2);
			
			
			if(this->p_MainMap->mapArray[tempNodeCounter]->returnTexture_2D()!=NULL)
				{
					this->p_Device->getVideoDriver()->draw2DImage(this->p_MainMap->mapArray[tempNodeCounter]->returnTexture_2D(),irr::core::vector2d<irr::s32>(this->p_MainMap->mapArray[tempNodeCounter]->getCurrentNodePosition_2D()->X-10,this->p_MainMap->mapArray[tempNodeCounter]->getCurrentNodePosition_2D()->Y-10));

				}
			else
				this->p_Device->getVideoDriver()->draw2DRectangle(irr::video::SColor(255,203,203,152),*tempRect);
			
			tempNodeCounter++;
			delete tempRect;

		}
	}
	}


	//hover over any block and it will be highlighted

	if(this->p_MainMap!=NULL && mousePosX>(this->mapOffset_X-10) && mousePosX < ((this->p_MainMap->mapWidth*20+this->mapOffset_X)-10) && mousePosY > this->mapOffset_Y-10 && mousePosY < (this->p_MainMap->mapHeight*20+this->mapOffset_Y)-10)
	{
		//update status
		irr::core::stringw str;
		str=L"mouse over the map : ";
		str+=mousePosX;
		str+=L"/";
		str+=mousePosY;
		if(!this->p_EventReceiver->isMouseDown(0))
		{
			str+="Currently selected Tool : ";
			str+=this->currentSelectedIconNumber;
		}
		
		this->editorFont[0]->draw(str.c_str(),irr::core::rect<irr::s32>(0,680,300,700),irr::video::SColor(255,255,255,255));
		//highlight depending on the node under the mouse

		for(int i = 0;i<this->p_MainMap->mapWidth*this->p_MainMap->mapHeight;i++)
		{
			int minCurrentNodeX = this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->X-10;
			int minCurrentNodeY = this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->Y-10;
			int maxCurrentNodeX = this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->X+10;
			int maxCurrentNodeY = this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->Y+10;


			if(mousePosX > minCurrentNodeX  &&  mousePosX <maxCurrentNodeX && mousePosY >minCurrentNodeY && mousePosY <maxCurrentNodeY)
			{
				
				if(this->p_EventReceiver->isKeyDown(irr::KEY_KEY_A))
				{
					for(int m=0;m<this->p_MainMap->mapArray[i]->getTotalAdjecentNodes();m++)
					{
						this->p_Device->getVideoDriver()->draw2DRectangle(irr::video::SColor(255,200,200,64),irr::core::rect<irr::s32>(this->p_MainMap->mapArray[i]->adjecentNodes[m]->getCurrentNodePosition_2D()->X-10,this->p_MainMap->mapArray[i]->adjecentNodes[m]->getCurrentNodePosition_2D()->Y-10,this->p_MainMap->mapArray[i]->adjecentNodes[m]->getCurrentNodePosition_2D()->X+10,this->p_MainMap->mapArray[i]->adjecentNodes[m]->getCurrentNodePosition_2D()->Y+10));
						this->p_Device->getVideoDriver()->draw2DLine(*this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D(),*this->p_MainMap->mapArray[i]->adjecentNodes[m]->getCurrentNodePosition_2D());
						this->p_Device->getVideoDriver()->draw2DPolygon(*this->p_MainMap->mapArray[i]->adjecentNodes[m]->getCurrentNodePosition_2D(),4);
					}
				}

				irr::core::rect<irr::s32> *tempRect = new irr::core::rect<irr::s32>(minCurrentNodeX,minCurrentNodeY,maxCurrentNodeX,maxCurrentNodeY);
				//check if the current node is already occupied by any of the obstacles or walkables
				if(this->p_MainMap->mapArray[i]->returnTexture_2D()!=NULL)
				{
					this->p_Device->getVideoDriver()->draw2DImage(this->p_MainMap->mapArray[i]->returnTexture_2D(),irr::core::vector2d<irr::s32>(this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->X-10,this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->Y-10));

				}
				else
				{
					this->p_Device->getVideoDriver()->draw2DRectangle(irr::video::SColor(255,128,128,64),*tempRect);
				}


				//draw the currently selected tool (only if one is selected)

				if(this->currentIconTextureToPlaceOnMap!=NULL)
				{
					this->p_Device->getVideoDriver()->draw2DImage(this->currentIconTextureToPlaceOnMap,irr::core::vector2d<irr::s32>(this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->X-10,this->p_MainMap->mapArray[i]->getCurrentNodePosition_2D()->Y-10));
						
				}

				//check which node is selected
				if(this->p_EventReceiver->isMouseDown(0))
				{
					if(this->p_MainMap->mapArray[i]->getTexture2DType()==0 || this->p_MainMap->mapArray[i]->getTexture2DType()==1 || this->p_MainMap->mapArray[i]->getTexture2DType()==2)
					{
						this->p_MainMap->mapArray[i]->setWalkableState(0);
					}
					else
					{
						this->p_MainMap->mapArray[i]->setWalkableState(1);
					}

					if(this->p_MainMap->mapArray[i]->returnTexture_2D()==NULL)
					{
						this->p_MainMap->mapArray[i]->setTexture_2D(this->currentIconTextureToPlaceOnMap);
						
						this->p_MainMap->mapArray[i]->setTexture2DType(this->currentSelectedIconNumber);
					}	
					irr::core::stringw nodeIndicator;
					nodeIndicator+="Node Selected is ";
					nodeIndicator+=this->p_MainMap->mapArray[i]->getNodeNumber();
					nodeIndicator+=" State : ";
					nodeIndicator+=this->p_MainMap->mapArray[i]->getWalkableState();

					this->editorFont[0]->draw(nodeIndicator.c_str(),irr::core::rect<irr::s32>(220,680,300,700),irr::video::SColor(255,255,255,255));

				}

				if(this->p_EventReceiver->isMouseDown(1))
				{
					if(this->p_MainMap->mapArray[i]->returnTexture_2D()!=NULL)
					{
						this->p_MainMap->mapArray[i]->setTexture_2D(NULL);
						this->p_MainMap->mapArray[i]->setTexture2DType(0);

					}
					this->p_MainMap->mapArray[i]->setWalkableState(0);
				}
			}
			
		}

			




	}


	//display the currently selected tool
	if(this->currentIconTextureToPlaceOnMap!=NULL )
	{
		this->editorFont[0]->draw(L"Currently Selected Tool : ",irr::core::rect<irr::s32>(600,130,680,150),irr::video::SColor(255,255,255,255));
		this->p_Device->getVideoDriver()->draw2DImage(this->currentIconTextureToPlaceOnMap,irr::core::vector2d<irr::s32>(800,130));
		this->editorFont[0]->draw(this->getIconByNumber(this->currentSelectedIconNumber)->getIconName()->c_str(),irr::core::rect<irr::s32>(840,130,880,150),irr::video::SColor(255,255,255,255));

	}


	//updates current state settings according to the mouse button pressed and pisition of the mouse
	if(this->p_EventReceiver->isMouseDown(0) && this->p_MainMap!=NULL)
	{

		//check for walkable/nonwalkable icons
		for(int i=0;i<3;i++)
		{
			//check for walkable icons
			if(i!=2)
			{

				if(mousePosX > this->p_WalkableIconsArray[i]->getIconPosition()->X && mousePosX < this->p_WalkableIconsArray[i]->getIconPosition()->X+50 &&
					mousePosY > this->p_WalkableIconsArray[i]->getIconPosition()->Y && mousePosY <this->p_WalkableIconsArray[i]->getIconPosition()->Y+50)
				{

					if(this->currentSelectedIconNumber!=this->p_WalkableIconsArray[i]->getIconNumber())
					{
						this->currentIconTextureToPlaceOnMap=NULL;
					}

					if(this->currentIconTextureToPlaceOnMap==NULL)
					{
						this->currentSelectedIconNumber = this->p_WalkableIconsArray[i]->getIconNumber();
						this->currentIconTextureToPlaceOnMap = this->p_WalkableIconsArray[i]->returnTextureFor2DMap();
							
					}



				}
			}

				if(mousePosX > this->p_ObstacleIconsArray[i]->getIconPosition()->X && mousePosX < this->p_ObstacleIconsArray[i]->getIconPosition()->X+50 &&
						mousePosY > this->p_ObstacleIconsArray[i]->getIconPosition()->Y && mousePosY <this->p_ObstacleIconsArray[i]->getIconPosition()->Y+50)
					{

						if(this->currentSelectedIconNumber!=this->p_ObstacleIconsArray[i]->getIconNumber())
							{
								this->currentIconTextureToPlaceOnMap=NULL;
							}

						if(this->currentIconTextureToPlaceOnMap==NULL)
						{
							this->currentSelectedIconNumber = this->p_ObstacleIconsArray[i]->getIconNumber();
							this->currentIconTextureToPlaceOnMap = this->p_ObstacleIconsArray[i]->returnTextureFor2DMap();
							
						}

							
					}
				
				




		}

	}


	


	



}


