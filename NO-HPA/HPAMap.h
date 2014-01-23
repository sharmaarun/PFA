#ifndef _HPAMap_
#define _HPAMap_

#include "Node.h"

namespace MapSystem
{
	
	class HPAMap
	{
	public:

		
		int nodesCount;
		int mapHeight  ;				// hieght of map
		int mapWidth ;					// width of map

		float nodeWidth;
		float nodeHeight;

		Node** mapArray;					//map array : contains nodes (either walkable or not walkable)

	public:

		HPAMap();
		HPAMap(int width, int height, float tnodeWidth, float tnodeHeight);

		

		bool InitMap();
		bool InitNodesData();

		MapSystem::Node* getNodeByNodeNumber(int num);
		void resetMap();
		void DrawNodes(irr::video::IVideoDriver* tempDriver);
	};

};

#endif