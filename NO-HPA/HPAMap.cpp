#include "HPAMap.h"

#include <iostream>
#include <conio.h>


using namespace MapSystem;


// construct the map

HPAMap::HPAMap()
{
	this->mapWidth = 0;
	this->mapHeight = 0;
	this->nodeWidth = 0;
	this->nodeHeight = 0;
	this->nodesCount = 0;
	this->mapArray = NULL;
}

HPAMap::HPAMap(int width, int height, float tnodeWidth, float tnodeHeight)
{
	this->mapWidth = width;
	this->mapHeight = height;
	this->nodeWidth = tnodeWidth;
	this->nodeHeight = tnodeHeight;
	this->nodesCount = 0;
	this->mapArray = new Node*[width*height];
}




//initialize the map and set the nodes
bool HPAMap::InitMap()
{
	if(mapArray==NULL)
		return false;


	//init the map
	std::cout<<"Initializing Map  . . .\n";
	for(int i=0; i<(mapWidth*mapHeight);i++)
	{
		mapArray[i] = new Node();
		nodesCount=i+1;
		mapArray[i]->setNodeNumber(nodesCount);
			
		
	}
	std::cout<<"Done!\n";

	//initialize node positions
	int arrayCounter=0;
	for(int j=0;j<this->mapHeight;j++)
	{
		for(int i=0;i<this->mapWidth;i++)
		{
			this->mapArray[arrayCounter]->setNewNodePosition(irr::core::position2df( ((float)i*this->nodeWidth)+this->nodeWidth/2.0f, ((float)j*this->nodeHeight)+this->nodeHeight/2.0f )) ;
			arrayCounter+=1;
		}
	}

	//init the nodes
	std::cout<<"Initializing Nodes . . .\n";
	if(!this->InitNodesData())
	{
		return false;
	}
	std::cout<<"Done!\n";





	return true;
	
}


//Initialize All the nodes and set their neighbours

bool HPAMap::InitNodesData()
{
	if(!this->mapArray)
		return false;

	for(int i=0;i<mapWidth*mapHeight;i++)
	{
		if(!this->mapArray[i])
			return false;

		
		
		//std::cout<<"nodenum : "<<mapArray[i]->getNodeNumber()<<"\n";
		
		int tempNodeNumber = this->mapArray[i]->getNodeNumber();
		
		//check for non-boundary nodes
		if(tempNodeNumber > this->mapWidth
			&& tempNodeNumber%this->mapWidth != 1
			&& tempNodeNumber%this->mapWidth !=0
			&& tempNodeNumber < this->mapWidth*(this->mapHeight-1))
		{
			//set adjecent nodes number
			this->mapArray[i]->adjecentNodes = new Node*[8];
			this->mapArray[i]->setTotalAdjecentNodes(8);

			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-(mapWidth+1)]);
			//std::cout<<"\tadded "<<mapArray[i-(mapWidth+1)]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-(mapWidth)]);
			//std::cout<<"\tadded "<<mapArray[i-(mapWidth)]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-(mapWidth-1)]);
			//std::cout<<"\tadded "<<mapArray[i-(mapWidth-1)]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-1]);
			//std::cout<<"\tadded "<<mapArray[i-1]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+1]);
			//std::cout<<"\tadded "<<mapArray[i+1]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(mapWidth-1)]);
			//std::cout<<"\tadded "<<mapArray[i+(mapWidth-1)]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(mapWidth)]);
			//std::cout<<"\tadded "<<mapArray[i+(mapWidth)]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(mapWidth+1)]);
			//std::cout<<"\tadded "<<mapArray[i+(mapWidth+1)]->getNodeNumber()<<" to the node"<<this->mapArray[i]->getNodeNumber()<<"\n";
		}


		// check for corner nodes
		if(tempNodeNumber == 1)
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[3];
			this->mapArray[i]->setTotalAdjecentNodes(3);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+this->mapWidth]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+this->mapWidth+1]);

		}


		if(tempNodeNumber == this->mapWidth)
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[3];
			this->mapArray[i]->setTotalAdjecentNodes(3);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+this->mapWidth-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+this->mapWidth]);

		}


		if(tempNodeNumber == (this->mapWidth*(this->mapHeight-1))+1)
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[3];
			this->mapArray[i]->setTotalAdjecentNodes(3);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-this->mapWidth]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)+1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+1]);

		}

		if(tempNodeNumber == this->mapWidth*this->mapHeight)
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[3];
			this->mapArray[i]->setTotalAdjecentNodes(3);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-this->mapWidth]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-1]);

		}



		//check for other boundary nodes

		if(tempNodeNumber < this->mapWidth && tempNodeNumber > 1)
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[5];
			this->mapArray[i]->setTotalAdjecentNodes(5);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(this->mapWidth-1)]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(this->mapWidth)]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(this->mapWidth+1)]);

		}

		if(tempNodeNumber%this->mapWidth==1 && tempNodeNumber!=1 && tempNodeNumber!=((this->mapWidth*(this->mapHeight-1))+1))
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[5];
			this->mapArray[i]->setTotalAdjecentNodes(5);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-this->mapWidth]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)+1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(this->mapWidth)]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(this->mapWidth+1)]);

		}

		if(tempNodeNumber%this->mapWidth==0 && tempNodeNumber!=this->mapWidth && tempNodeNumber!=(this->mapWidth*this->mapHeight))
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[5];
			this->mapArray[i]->setTotalAdjecentNodes(5);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i+this->mapWidth)-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+(this->mapWidth)]);
			
		}

		if(tempNodeNumber>((this->mapWidth*(this->mapHeight-1))+1)  &&  tempNodeNumber < this->mapWidth*this->mapHeight  )
			
		{
			
			this->mapArray[i]->adjecentNodes = new Node*[5];
			this->mapArray[i]->setTotalAdjecentNodes(5);


			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[(i-this->mapWidth)+1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i-1]);
			this->mapArray[i]->addNodeToAdjecentNodesList(this->mapArray[i+1]);

		}


	}

	return true;

}


//draw nodes in form of lines
void HPAMap::DrawNodes(irr::video::IVideoDriver* tempDriver)
{



	irr::core::position2df *oldPos = this->mapArray[0]->getCurrentNodePosition();

	irr::core::position2df *newPos;

	for(int i=1;i<this->mapWidth*mapHeight;i++)
	{
		newPos= this->mapArray[i]->getCurrentNodePosition();

		tempDriver->draw3DLine(irr::core::vector3df(oldPos->X,0,oldPos->Y),irr::core::vector3df(newPos->X,0,newPos->Y),irr::video::SColor(255,255,255,255));

		oldPos = newPos;
	}
}



//get node by node number
MapSystem::Node* MapSystem::HPAMap::getNodeByNodeNumber(int num)
{
	if(num>0 && num<=this->nodesCount)
		return this->mapArray[num-1];
	else
		return NULL;
}

//reset the map

void MapSystem::HPAMap::resetMap()
{
	if(this->mapArray!=NULL)
	{
		for(int i=0;i<this->nodesCount;i++)
		{
			this->mapArray[i]->setParent(NULL);
			this->mapArray[i]->setChild(NULL);
			this->mapArray[i]->setGScore(0.0f);
			this->mapArray[i]->setHScore(0.0f);
		}
	}
}