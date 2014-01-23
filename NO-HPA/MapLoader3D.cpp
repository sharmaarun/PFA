#include "MapLoader3D.h"


MapLoader3D::MapLoader3D()				//default constructor
{
	this->p_Device = NULL;
	this->p_walkableMeshes = new irr::scene::IAnimatedMesh*[2];
	this->p_obstacleMeshes = new irr::scene::IMesh*[3];
	
}


MapLoader3D::MapLoader3D(irr::IrrlichtDevice* tp_Device)			//overloaded constructor
{
	this->p_Device = tp_Device;
	this->p_walkableMeshes = new irr::scene::IAnimatedMesh*[2];
	this->p_obstacleMeshes = new irr::scene::IMesh*[3];
	
	this->p_walkableMeshes[0] = this->p_Device->getSceneManager()->getMesh("../data/models/stone.obj");
	this->p_walkableMeshes[1] = this->p_Device->getSceneManager()->getMesh("../data/models/stone.obj");
	this->p_obstacleMeshes[0] = this->p_Device->getSceneManager()->getMesh("../data/models/stone.obj");
	this->p_obstacleMeshes[1] = this->p_Device->getSceneManager()->getMesh("../data/models/tree.obj");
	this->p_obstacleMeshes[2] = this->p_Device->getSceneManager()->getMesh("../data/models/stone.obj");

	this->mapBase = NULL;
	

}



void MapLoader3D::setMainDevice(irr::IrrlichtDevice* tp_Device)
{
	this->p_Device = tp_Device;
}



void MapLoader3D::readMapFromFile(irr::core::stringw t_FilePath)
{

	std::ifstream read(t_FilePath.c_str());
	if(!read.good())
		std::cout<<"Error reading file!";	

	int width,height,nwidth,nheight,nodeCount,nodeNumber,pos2dX,pos2dY,state,textureType;
	float posX,posY;
	read>>width;
	read>>height;
	read>>nwidth;
	read>>nheight;
	read>>nodeCount;

	this->p_MainMap = new MapSystem::HPAMap(width,height,(float)nwidth,(float)nheight);

	if(!this->p_MainMap)
		std::cout<<"Could not read map correctly!";

	this->p_MainMap->InitMap();
	
	for(int i=0;i<nodeCount;i++)
	{
		read>>nodeNumber;
		read>>posX;
		read>>posY;
		read>>pos2dX;
		read>>pos2dY;
		read>>state;
		read>>textureType;

		if(state==0)
		this->p_MainMap->mapArray[i]->setWalkableState(false);
		if(state==1)
		this->p_MainMap->mapArray[i]->setWalkableState(true);
		this->p_MainMap->mapArray[i]->setNodeNumber(nodeNumber);
		this->p_MainMap->mapArray[i]->setNewNodePosition(irr::core::position2df((irr::f32)posX,(irr::f32)posY));
		this->p_MainMap->mapArray[i]->setTexture2DType(textureType);
			
	}

	read.close();



}


void MapLoader3D::initWAOSceneNodes()
{
	if(this->p_MainMap!=NULL)
	{

		//add map base to the scene
		//this->mapBase = new CMapBaseSceneNode(this->p_Device->getSceneManager()->getRootSceneNode(),this->p_Device->getSceneManager(),1001,this->p_MainMap);
		//this->mapBase->drop();
		//this->mapBase=0;
		
		this->mapBase = this->p_Device->getSceneManager()->addHillPlaneMesh(L"hill",
			irr::core::dimension2d<irr::f32>(this->p_MainMap->nodeWidth,this->p_MainMap->nodeHeight),
			irr::core::dimension2d<irr::u32>(this->p_MainMap->mapWidth,this->p_MainMap->mapHeight),0,2.0f,irr::core::dimension2df(5.0f,5.0f),irr::core::dimension2df((irr::f32)this->p_MainMap->mapWidth,(irr::f32)this->p_MainMap->mapHeight));
		
		this->mapBaseNode = this->p_Device->getSceneManager()->addAnimatedMeshSceneNode(mapBase);
		this->mapBaseNode->setMaterialTexture(0,this->p_Device->getVideoDriver()->getTexture("../data/textures/basegrass.jpg"));

		this->mapBaseNode->setPosition(irr::core::vector3df((this->p_MainMap->mapWidth*(this->p_MainMap->nodeWidth))/2,0.0f,(this->p_MainMap->mapHeight*this->p_MainMap->nodeHeight)/2));
		//add skybox
		this->p_Device->getSceneManager()->addSkyBoxSceneNode(this->p_Device->getVideoDriver()->getTexture("../data/textures/irrlicht2_up.jpg"),
			this->p_Device->getVideoDriver()->getTexture("../data/textures/irrlicht2_dn.jpg"),
			this->p_Device->getVideoDriver()->getTexture("../data/textures/irrlicht2_lf.jpg"),
			this->p_Device->getVideoDriver()->getTexture("../data/textures/irrlicht2_rt.jpg"),
			this->p_Device->getVideoDriver()->getTexture("../data/textures/irrlicht2_ft.jpg"),
			this->p_Device->getVideoDriver()->getTexture("../data/textures/irrlicht2_bk.jpg"));

		this->p_Device->getSceneManager()->addLightSceneNode(0,irr::core::vector3df(0.0f,1000.0f,0.0f),irr::video::SColorf(1.0f,1.0f,1.0f),10000.0f);
		this->p_arrayOfSceneNodesWAO = new irr::scene::IMeshSceneNode*[this->p_MainMap->nodesCount];
		for(int i=0;i<this->p_MainMap->nodesCount;i++)
		{
			
			
			if(this->p_MainMap->mapArray[i]->getWalkableState()==0)
			{
				

			if(this->p_MainMap->mapArray[i]->getTexture2DType()==1)
				{
					this->grassNode = new irr::scene::IBillboardSceneNode*[25];
					int nodeCounter=0;
					
					for(int gsni=0;gsni<5;gsni++)
					{
						for(int gsnj=0;gsnj<5;gsnj++)
						{
							
						grassNode[nodeCounter] = this->p_Device->getSceneManager()->addBillboardSceneNode(this->p_Device->getSceneManager()->getRootSceneNode());
						//setup material characterstics
						grassNode[nodeCounter]->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
						grassNode[nodeCounter]->setMaterialTexture(0,this->p_Device->getVideoDriver()->getTexture("../data/models/smallgrass.jpg"));
						grassNode[nodeCounter]->setMaterialFlag(irr::video::EMF_LIGHTING,false);
						grassNode[nodeCounter]->setMaterialFlag(irr::video::EMF_ZBUFFER,true);
						
						//set position
						irr::f32 nodePosX = this->p_MainMap->mapArray[i]->getCurrentNodePosition()->X-(this->p_MainMap->nodeWidth/2);
						irr::f32 nodePosZ = this->p_MainMap->mapArray[i]->getCurrentNodePosition()->Y-(this->p_MainMap->nodeHeight/2);

						irr::f32 gsnPosZ = nodePosZ+(gsni)*this->p_MainMap->nodeHeight/5;
						irr::f32 gsnPosX = nodePosX+(gsnj)*this->p_MainMap->nodeWidth/5;

						grassNode[nodeCounter]->setPosition(irr::core::vector3df(gsnPosX,2.0f,gsnPosZ));

						nodeCounter++;

						}
					}
				}

			}
			
			if(this->p_MainMap->mapArray[i]->getWalkableState()==1)
			{
				
				//draw small and large grass billboards
				// 1- smgrass , 2-road , 3-lggrass, 4-tree, 5-stone
				
				

				//draw  stones , tress , roads
				if(this->p_MainMap->mapArray[i]->getTexture2DType()==4)
					this->p_arrayOfSceneNodesWAO[i] = this->p_Device->getSceneManager()->addOctTreeSceneNode(this->getObstacleMeshes()[1]);
				if(this->p_MainMap->mapArray[i]->getTexture2DType()==5)
				this->p_arrayOfSceneNodesWAO[i] = this->p_Device->getSceneManager()->addOctTreeSceneNode(this->getObstacleMeshes()[2]);
				if(this->p_MainMap->mapArray[i]->getTexture2DType()==3)
				this->p_arrayOfSceneNodesWAO[i] = this->p_Device->getSceneManager()->addOctTreeSceneNode(this->getObstacleMeshes()[0]);

				
				float x_x = this->p_MainMap->mapArray[i]->getCurrentNodePosition()->X;
				float z_z = this->p_MainMap->mapArray[i]->getCurrentNodePosition()->Y;
				this->p_arrayOfSceneNodesWAO[i]->setPosition(irr::core::vector3df(x_x,0.0f,z_z));
				this->p_arrayOfSceneNodesWAO[i]->setScale(irr::core::vector3df(5.0f,5.0f,5.0f));


				this->p_arrayOfSceneNodesWAO[i]->setMaterialFlag(irr::video::EMF_LIGHTING,true);
				//this->p_arrayOfSceneNodesWAO[i]->setMaterialTexture(0,this->p_Device->getVideoDriver()->getTexture("../data/models/stone.jpg"));
				
				
			}
		}
	}
}


MapSystem::HPAMap* MapLoader3D::getMainMap()
{
	return this->p_MainMap;
}


irr::scene::IAnimatedMesh** MapLoader3D::getWalkableMeshes()
{
	return this->p_walkableMeshes;
}

irr::scene::IMesh** MapLoader3D::getObstacleMeshes()
{
	return this->p_obstacleMeshes;
}

irr::scene::IMeshSceneNode** MapLoader3D::getArrayOfSceneNodes()
{
	return this->p_arrayOfSceneNodesWAO;
}

irr::scene::IAnimatedMeshSceneNode* MapLoader3D::getMapBaseNode()
{
	return this->mapBaseNode;
}