#include"PathFinder.h"

MapSystem::CPathFinder::CPathFinder(MapSystem::HPAMap* tp_MainMap)
{
	this->p_MainMap = tp_MainMap;
	this->sourceNode = NULL;
	this->destinationNode = NULL;
	this->pathFound=false;
	
};


float MapSystem::CPathFinder::calcManhattan(MapSystem::Node* cNode, MapSystem::Node* dNode)
{
	float x1,x2,xSteps,y1,y2,ySteps;

	x1 = (float)( dNode->getNodeNumber()%this->p_MainMap->mapWidth);
	x2 = (float)( cNode->getNodeNumber()%this->p_MainMap->mapWidth);
	
	if(x1==0)
		x1=(float)this->p_MainMap->mapWidth;
	if(x2==0)
		x2=(float)this->p_MainMap->mapWidth;

	xSteps = x2-x1;
	if(xSteps<0)
		xSteps*=-1;
	
	
	int k=0,found=0;
	for(int i=0;i<this->p_MainMap->mapHeight;i++)
	{
		if(found>1)
			{
				break;
			}

		for(int j=0;j<this->p_MainMap->mapWidth;j++)
		{
			if(found>1)
			{
				break;
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==cNode->getNodeNumber())
			{
				y2= (float)(i+1);
				found+=1;
				
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==dNode->getNodeNumber())
			{
				y1= (float)(i+1);
				found+=1;
				
			}
			
			k++;
		}

	}
	ySteps = (y2-y1);
	

	if(ySteps<0)
		ySteps*=-1;
	
	
	

	
	return (xSteps+ySteps);


}



float MapSystem::CPathFinder::getGVariation(MapSystem::Node* cNode,MapSystem::Node* sNode,MapSystem::Node* pNode)
{
	//calc d1
	float x1,x2,y1,y2,d1xSteps,d1ySteps,d2xSteps,d2ySteps,d1,d2;

	x1 = (float)( pNode->getNodeNumber()%this->p_MainMap->mapWidth);
	x2 = (float)( sNode->getNodeNumber()%this->p_MainMap->mapWidth);
	

	if(x1==0)
		x1=(float)this->p_MainMap->mapWidth;
	if(x2==0)
		x2=(float)this->p_MainMap->mapWidth;

	d1xSteps = x2-x1;
	if(d1xSteps<0)
		d1xSteps*=-1;
	
	
	int k=0,found=0;
	for(int i=0;i<this->p_MainMap->mapHeight;i++)
	{
		if(found>1)
			{
				break;
			}

		for(int j=0;j<this->p_MainMap->mapWidth;j++)
		{
			if(found>1)
			{
				break;
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==sNode->getNodeNumber())
			{
				y2= (float)(i+1);
				found+=1;
				
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==pNode->getNodeNumber())
			{
				y1= (float)(i+1);
				found+=1;
				
			}
			
			k++;
		}

	}
	d1ySteps = (y2-y1);
	

	if(d1ySteps<0)
		d1ySteps*=-1;
	

	d1 = std::sqrtf(d1xSteps*d1xSteps+d1ySteps*d1ySteps);
	

	//calc d2

	x1=x2=y1=y2=0.0f;
	k=found=0;

	x1 = (float)( sNode->getNodeNumber()%this->p_MainMap->mapWidth);
	x2 = (float)( cNode->getNodeNumber()%this->p_MainMap->mapWidth);
	

	if(x1==0)
		x1=(float)this->p_MainMap->mapWidth;
	if(x2==0)
		x2=(float)this->p_MainMap->mapWidth;

	d2xSteps = x2-x1;
	if(d2xSteps<0)
		d2xSteps*=-1;
	

	
	for(int i=0;i<this->p_MainMap->mapHeight;i++)
	{
		if(found>1)
			{
				break;
			}

		for(int j=0;j<this->p_MainMap->mapWidth;j++)
		{
			if(found>1)
			{
				break;
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==cNode->getNodeNumber())
			{
				y2= (float)(i+1);
				found+=1;
				
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==sNode->getNodeNumber())
			{
				y1= (float)(i+1);
				found+=1;
				
			}
			
			k++;
		}

	}
	d2ySteps = (y2-y1);
	

	if(d2ySteps<0)
		d2ySteps*=-1;
	
	d2 = std::sqrtf(d2xSteps*d2xSteps+d2ySteps*d2ySteps);
	
	
	return d1+d2+pNode->getGScore();

}


void MapSystem::CPathFinder::setScores(MapSystem::Node* currentNode,MapSystem::Node* p_SourceNode)
{
	currentNode->setHScore(this->calcManhattan(currentNode,this->destinationNode));
	

	if(p_SourceNode!=NULL)
	{
	
	float x1,x2,xSteps,y1,y2,ySteps;

	x1 = (float)( p_SourceNode->getNodeNumber()%this->p_MainMap->mapWidth);
	x2 = (float)( currentNode->getNodeNumber()%this->p_MainMap->mapWidth);
	
	if(x1==0)
		x1=(float)this->p_MainMap->mapWidth;
	if(x2==0)
		x2=(float)this->p_MainMap->mapWidth;

	xSteps = x2-x1;
	if(xSteps<0)
		xSteps*=-1;

	
	int k=0,found=0;
	for(int i=0;i<this->p_MainMap->mapHeight;i++)
	{
		if(found>1)
			{
				break;
			}
		for(int j=0;j<this->p_MainMap->mapWidth;j++)
		{
			if(found>1)
			{
				break;
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==currentNode->getNodeNumber())
			{
				y2= (float)(i+1);
				found+=1;
			}
			if(this->p_MainMap->mapArray[k]->getNodeNumber()==p_SourceNode->getNodeNumber())
			{
				y1= (float)(i+1);
				found+=1;
			}
			
			k++;
		}
	}
	ySteps = (y2-y1);
	

	if(ySteps<0)
		ySteps*=-1;
	
	currentNode->setGScore(sqrt(ySteps*ySteps+xSteps*xSteps)+p_SourceNode->getGScore());

	}
	else
	{
		currentNode->setGScore(0.0f);
	}

	


}


bool MapSystem::CPathFinder::isNodeInOpenList(MapSystem::Node* tNode)
{
	for(unsigned int i=0;i<this->openList.size();i++)
	{
		if(tNode->getNodeNumber()==openList[i]->getNodeNumber())
		{
			return true;
		}
	}

	return false;
}

bool MapSystem::CPathFinder::isNodeInClosedList(MapSystem::Node* tNode)
{
for(unsigned int i=0;i<this->closedList.size();i++)
	{
		if(tNode->getNodeNumber()==closedList[i]->getNodeNumber())
		{
			return true;
		}
	}

	return false;
}




void MapSystem::CPathFinder::setDestination(MapSystem::Node* p_DestNode)
{
	this->destinationNode = p_DestNode;
}


MapSystem::Node* MapSystem::CPathFinder::getDestinationNode()
{
	return this->destinationNode;
}



std::vector<MapSystem::Node*> MapSystem::CPathFinder::CalculatePath(MapSystem::Node* p_SourceNode,MapSystem::Node* p_DestinationNode)
{

	//std::cout<<std::endl<<"SourceNode num : "<<p_SourceNode->getNodeNumber()<<" \t DestinationNode num : "<<p_DestinationNode->getNodeNumber()<<std::endl;
	if(p_SourceNode==p_DestinationNode)
		return this->foundPath;
	this->sourceNode = p_SourceNode;
	
	//main algorithm - pathfinding

	
	MapSystem::Node* selectedNode;
	
	selectedNode= NULL;
	
	//1 push sourcenode to close list
	closedList.push_back(p_SourceNode);
	//2 add sourcenode's adjecent nodes to the openlist
	for(int i=0;i<p_SourceNode->getTotalAdjecentNodes();i++)
	{
		//check if the adjecent node is the destination itself or not
		if(p_SourceNode->adjecentNodes[i]->getNodeNumber()==p_DestinationNode->getNodeNumber())
		{
			//std::cout<<"Destination Node Found!";
			this->pathFound=true;
			this->foundPath.push_back(p_DestinationNode);
			this->foundPath.push_back(p_SourceNode);
			p_DestinationNode->setParent(p_SourceNode);
			p_SourceNode->setParent(p_DestinationNode);
			break;
		}

		//check for walkable and those nodes that are not in closed list
		if(p_SourceNode->adjecentNodes[i]->getWalkableState()!=1 && !this->isNodeInClosedList(p_SourceNode->adjecentNodes[i]))
		{
			//add nodes to openlist
			p_SourceNode->adjecentNodes[i]->setParent(p_SourceNode);
			//std::cout<<"parent changed to "<<p_SourceNode->getNodeNumber()<<std::endl;
			this->setScores(p_SourceNode->adjecentNodes[i],p_SourceNode);
			this->openList.push_back(p_SourceNode->adjecentNodes[i]);
			//std::cout<<"node inserted in openlist  :"<<p_SourceNode->adjecentNodes[i]->getNodeNumber()<<std::endl;
			//std::cout<<"gScore of above node :"<<p_SourceNode->adjecentNodes[i]->getGScore()<<std::endl;
			//std::cout<<"fScore of above node :"<<p_SourceNode->adjecentNodes[i]->getFScore()<<std::endl;
			//std::cout<<"hScore of above node :"<<p_SourceNode->adjecentNodes[i]->getHScore()<<std::endl;
		}
	}

	
	//main loop starts : check all the adjecent nodes
	this->counter=0;
	//std::cout<<"Source selected :"<<p_SourceNode->getNodeNumber()<<std::endl;
	//std::cout<<"Destin selected :"<<p_DestinationNode->getNodeNumber()<<std::endl;
	while(pathFound!=true)
	{
		this->counter+=1;
		
		if(this->counter > this->p_MainMap->nodesCount)
		{			
			break;
		}

		

		
		//check for node with lowest f score in the openlist
		selectedNode= openList[0];
		int selectedNodeLocation = 0;
		for(unsigned int i=0;i<openList.size();i++)
		{
			if(openList[i]->getFScore()<selectedNode->getFScore())
				{
					selectedNode = openList[i];
					selectedNodeLocation = i;
				}
		}
		//std::cout<<"Node selected :"<<selectedNode->getNodeNumber()<<std::endl;
		//remove the node with lowest f score from the openlist and put it in closed list
		
		openList.erase(openList.begin()+selectedNodeLocation);	//remove from open list
		closedList.push_back(selectedNode);						//add to closed list

		

		if(selectedNode->getNodeNumber()==p_DestinationNode->getNodeNumber() )
		{
			this->pathFound=true;
			break;
		}
		



		/*std::cout<<std::endl<<"Contents in openlist :\n";
		for(int ti = 0;ti<openList.size();ti++)
		{
			std::cout<<openList.at(ti)->getNodeNumber()<<"\t";
		}
		std::cout<<std::endl<<"Contents in closedList :\n";
		for(int ti = 0;ti<closedList.size();ti++)
		{
			std::cout<<closedList.at(ti)->getNodeNumber()<<"\t";
		}
		*/




		//check all the adjecent nodes of selected node for variation in g
		for(int i=0;i<selectedNode->getTotalAdjecentNodes();i++)
		{
			//std::cout<<"adjecent Node subselected :"<<selectedNode->adjecentNodes[i]->getNodeNumber()<<std::endl;
			if(selectedNode->adjecentNodes[i]->getWalkableState()!=1 && !this->isNodeInClosedList(selectedNode->adjecentNodes[i]))
			{
				if(!this->isNodeInOpenList(selectedNode->adjecentNodes[i]))
				{
					openList.push_back(selectedNode->adjecentNodes[i]);	//push the adjecent node in the openlist
					//std::cout<<"this node is not in open list so we added it"<<std::endl;
					selectedNode->adjecentNodes[i]->setParent(selectedNode);	//make selected node the parent of its adjecent node
					//std::cout<<"parent of this node is now : "<<selectedNode->getNodeNumber()<<std::endl;
					this->setScores(selectedNode->adjecentNodes[i],selectedNode);
					//std::cout<<"gScore of above node :"<<selectedNode->adjecentNodes[i]->getGScore()<<std::endl;
					//std::cout<<"fScore of above node :"<<selectedNode->adjecentNodes[i]->getFScore()<<std::endl;
					//std::cout<<"hScore of above node :"<<selectedNode->adjecentNodes[i]->getHScore()<<std::endl;
					
					
				}
				else
				{
					//std::cout<<"this node is not in openlist and it's g-var score is "<<this->getGVariation(selectedNode->adjecentNodes[i],selectedNode,selectedNode->getParent())<<std::endl;
					if(selectedNode->adjecentNodes[i]->getGScore()>this->getGVariation(selectedNode->adjecentNodes[i],selectedNode,selectedNode->getParent()))
					{
						//std::cout<<"this node is already in the open list so we chenged parent to : ";
						selectedNode->adjecentNodes[i]->setParent(selectedNode);	//reset parent
						//std::cout<<"\t"<<selectedNode->getNodeNumber()<<std::endl;
						this->setScores(selectedNode->adjecentNodes[i],selectedNode);	//reset f,g scores
						//std::cout<<"gScore of above node :"<<selectedNode->adjecentNodes[i]->getGScore()<<std::endl;
						//std::cout<<"fScore of above node :"<<selectedNode->adjecentNodes[i]->getFScore()<<std::endl;
						//std::cout<<"hScore of above node :"<<selectedNode->adjecentNodes[i]->getHScore()<<std::endl;
					}
				}
			}
		}

	}

	
	
	if(this->pathFound)
	{
		this->pathFound=false;
		MapSystem::Node *parentNode,*nodeCurrent;
		nodeCurrent = this->destinationNode;
		while(true)
		{
			
			this->foundPath.push_back(nodeCurrent);
			parentNode = nodeCurrent->getParent();
			nodeCurrent = parentNode;
			if(nodeCurrent->getNodeNumber()==this->sourceNode->getNodeNumber())
				break;

		}

		foundPath.push_back(this->sourceNode);
	

	}

	this->outPutPathFound();

	closedList.clear();
	openList.clear();
	

	return this->foundPath;
	

}


void MapSystem::CPathFinder::outPutPathFound()
{
	if(this->foundPath.size()>0)
	{
		std::cout<<"The path from source to destination is:"<<std::endl;
		for(int i=0;i<(int)foundPath.size();i++)
		{
			std::cout<<foundPath.at(i)->getNodeNumber()<<"\t";
		}
	}
}


std::vector<MapSystem::Node*>* MapSystem::CPathFinder::getFoundPathList()
{
	return &this->foundPath;
}

void MapSystem::CPathFinder::emptyPathList()
{
	foundPath.clear();		

}