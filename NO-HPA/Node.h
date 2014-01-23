#ifndef _Node_
#define _Node_

#include "irrlicht.h"


namespace MapSystem
{

	class Node
	{
	private:
		
		float g,h,f;				//scores : G: distance from start node ,F: G+H , H: Heuristic score from start to end node
		
		Node* parent ;			// parent node of current node
		Node* child ;			// child node of current node

		int walkable ;			// tells if node is walkable or not
		int nodeNumber;
		int totalAdjecentNodes;
		irr::core::position2df nodePosition;
		
		int currentAdjectNodesFillCount ;
		

		//editor related variables
		irr::core::vector2d<irr::s32> nodePosition_2D;
		irr::video::ITexture* nodeTexture_2D;
		int textureType;
		//member functions

		

	public:
		Node** adjecentNodes;
		Node();						//constructor
		Node(int state);

		void setParent(Node* newParent);  //setparent of current node
		void setChild(Node* newChild);		//set child of current node

		Node* getParent();			// return parent of current node , if exists
		Node* getChild();			// return child of current node
		
		void setWalkableState(int state);	//set new state (walkable or unwalkable)
		int getWalkableState();			//return state

		void setGScore(float newG);			//set G score for current node
		void setHScore(float newG);			// set H score for current node
		//return all the scores

		float getGScore();
		float getHScore();
		float getFScore();

		//add/show neighbour nodes
		void addNodeToAdjecentNodesList(Node* newNode);
		void showAdjecentNodes();

		//set/get node number
		void setNodeNumber(int newNum);
		int getNodeNumber();

		//set get total adjecent nodes count
		void setTotalAdjecentNodes(int newTAN);
		int getTotalAdjecentNodes();

		//get-set node position
		irr::core::position2df* getCurrentNodePosition();
		void setNewNodePosition(irr::core::position2df newPos);

		irr::core::vector2d<irr::s32>* getCurrentNodePosition_2D();
		void setNewNodePosition_2D(irr::core::vector2d<irr::s32> newPos);
		
		irr::video::ITexture* returnTexture_2D();
		void setTexture_2D(irr::video::ITexture* t_texture2D);

		void setTexture2DType(int type);
		int getTexture2DType();

	};

};

#endif