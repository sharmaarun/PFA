#include <iostream>
#include <conio.h>

// parent header include
#include "Node.h"



// default constructor to initialize a node
MapSystem::Node::Node()
{
		g = 0;
		h = 0;
		f = g +h;

		parent = NULL;
		child = NULL;

		walkable = 0;
		nodeNumber = -1;
		this->currentAdjectNodesFillCount = 0;
		this->nodePosition= irr::core::position2df(0.0f,0.0f);
		
		this->nodeTexture_2D = NULL;
		this->textureType = 0;
};


// custom node constructor

MapSystem::Node::Node(int state)
{
	Node();
	this->walkable = state;
};




//set the parent of current node
void MapSystem::Node::setParent(MapSystem::Node* newParent)
{
	
		this->parent = newParent;
	
};


//set the child of current node
void MapSystem::Node::setChild(MapSystem::Node* newChild)
{
	
		this->child = newChild;
	
}


//return the parent of the current node
MapSystem::Node* MapSystem::Node::getParent()
{
	if(this->parent!=NULL)
	{
		return this->parent;
	}
	else return NULL;
};

//return the child of the current node
MapSystem::Node* MapSystem::Node::getChild()
{
	if(this->child!=NULL)
	{
		return this->child;
	}
	else return NULL;
};



//make node walkable or unwalkable
void MapSystem::Node::setWalkableState(int state)
{
	this->walkable = state;
};

//get the current satte of node
int MapSystem::Node::getWalkableState()
{
	return this->walkable;
};





//set various scores of this node
void MapSystem::Node::setGScore(float newG)
{
	this->g = newG;
	this->f = this->g + this->h;
};

void MapSystem::Node::setHScore(float newH)
{
	this->h = newH;
	this->f = this->g + this->h;
};


//get all scores
float MapSystem::Node::getGScore()
{
	return this->g;
}

float MapSystem::Node::getHScore()
{
	return this->h;
}

float MapSystem::Node::getFScore()
{
	return this->f;
}


//set nodeNumber
void MapSystem::Node::setNodeNumber(int newNum)
{
	this->nodeNumber = newNum;
}

//get node number
int MapSystem::Node::getNodeNumber()
{
	return this->nodeNumber;
}


//add new node to adjecent nodes list of the current node

void MapSystem::Node::addNodeToAdjecentNodesList(Node* newNode)
{
	if(newNode!=NULL)
	{
		this->adjecentNodes[this->currentAdjectNodesFillCount] = newNode;
		this->currentAdjectNodesFillCount+=1;
	}
}


void MapSystem::Node::showAdjecentNodes()
{
	std::cout<<"Node Number: "<<this->nodeNumber<<"Adjecent Nodes for this node are : \n";
			
		if(this->adjecentNodes!=NULL)
		{
			for(int i=0;i<this->getTotalAdjecentNodes();i++)
			std::cout<<this->adjecentNodes[i]->getNodeNumber()<<std::endl;
			
		}
	
	std::cout<<"\n";
}


//set and get total adjecent nodes
void MapSystem::Node::setTotalAdjecentNodes(int newTAN)
{
	this->totalAdjecentNodes = newTAN;
}

int MapSystem::Node::getTotalAdjecentNodes()
{
	return this->totalAdjecentNodes;
}



//return node position

irr::core::position2df* MapSystem::Node::getCurrentNodePosition()
{
	irr::core::position2df* tempNodePosition = &(this->nodePosition);

	return tempNodePosition;
}

//set node position

void MapSystem::Node::setNewNodePosition(irr::core::position2df newPos)
{
	this->nodePosition = newPos;
}


//return 2d position
irr::core::vector2d<irr::s32>* MapSystem::Node::getCurrentNodePosition_2D()
{
	irr::core::vector2d<irr::s32>* tempNodePosition = &(this->nodePosition_2D);

	return tempNodePosition;
}

//set node position

void MapSystem::Node::setNewNodePosition_2D(irr::core::vector2d<irr::s32> newPos)
{
	this->nodePosition_2D = newPos;
}

//set 2d texture for use in editor
void MapSystem::Node::setTexture_2D(irr::video::ITexture* t_texture2D)
{
	this->nodeTexture_2D = t_texture2D;
}

irr::video::ITexture* MapSystem::Node::returnTexture_2D()
{
	return this->nodeTexture_2D;
}

//set get texture 2d type
void MapSystem::Node::setTexture2DType(int type)
{
	this->textureType = type;
}

int MapSystem::Node::getTexture2DType()
{
	return this->textureType;
}