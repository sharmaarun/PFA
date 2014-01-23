#ifndef _PathFinder_
#define _PathFinder_

#include "HPAMap.h"
#include <iostream>
#include <vector>
#include <math.h>


namespace MapSystem
{
class CPathFinder
{

private:
	
	//source and destination nodes
	MapSystem::Node* sourceNode;
	MapSystem::Node* destinationNode;
	MapSystem::HPAMap* p_MainMap;

	bool pathFound;
	int counter;

	std::vector<MapSystem::Node*> openList;
	std::vector<MapSystem::Node*> closedList;
	std::vector<MapSystem::Node*> foundPath;

	void setScores(MapSystem::Node* currentNode,MapSystem::Node* p_SourceNode);
	float calcManhattan(MapSystem::Node* cNode, MapSystem::Node* dNode);
	float getGVariation(MapSystem::Node* cNode,MapSystem::Node* sNode,MapSystem::Node* pNode);

public:

	CPathFinder(MapSystem::HPAMap* tp_MainMain);
	std::vector<MapSystem::Node*> CalculatePath(MapSystem::Node* p_SourceNode, MapSystem::Node* p_DestinationNode);
	bool isNodeInOpenList(MapSystem::Node* tNode);
	bool isNodeInClosedList(MapSystem::Node* tNode);
	void setDestination(MapSystem::Node* p_DestNode);
	MapSystem::Node* getDestinationNode();
	std::vector<MapSystem::Node*>* getFoundPathList();
	void emptyPathList();
	void outPutPathFound();
};
};
#endif