#include "Environment3D.h"

Environment3D::Environment3D(irr::IrrlichtDevice* tp_Device,CSettings* tp_Settings,CEventReceiver* tp_EventReceiver,irr::scene::ICameraSceneNode* tp_Cam)
{
	this->p_Device = tp_Device;
	this->p_Settings = tp_Settings;
	this->p_EventReceiver = tp_EventReceiver;
	this->p_Map3D = NULL;
	this->p_Cam=tp_Cam;
}


void Environment3D::initEnvironment()
{
	
	//read map file
	if(this->p_Map3D!=NULL)
	{
		for(int i=0;i<this->p_Map3D->getMainMap()->nodesCount;i++)
		{
			this->p_Map3D->getArrayOfSceneNodes()[i]->remove();
			delete this->p_Map3D->getArrayOfSceneNodes()[i];
		}
		delete this->p_Map3D;
	}
		

	this->p_Map3D = new MapLoader3D(this->p_Device);
	this->p_Map3D->readMapFromFile(this->p_Settings->getFileToOpen()->c_str());
	this->p_Map3D->initWAOSceneNodes();


	while(true)
		{
			int randPos = std::rand()%(this->p_Map3D->getMainMap()->mapWidth*this->p_Map3D->getMainMap()->mapHeight);
			if(this->p_Map3D->getMainMap()->mapArray[randPos]->getWalkableState()==0)
			{
				p_Cam->setPosition(irr::core::vector3df(this->p_Map3D->getMainMap()->mapArray[randPos]->getCurrentNodePosition()->X,10.0f,this->p_Map3D->getMainMap()->mapArray[randPos]->getCurrentNodePosition()->Y));
				this->player = new CPlayer(this->p_Device,irr::core::vector3df(this->p_Map3D->getMainMap()->mapArray[randPos]->getCurrentNodePosition()->X,20.0f,this->p_Map3D->getMainMap()->mapArray[randPos]->getCurrentNodePosition()->Y));
				this->player->getPlayerSceneNode()->setRotation(irr::core::vector3df(0.0f,0.0f,0.0f));
				this->player->setNodeUnderPlayer(this->p_Map3D->getMainMap()->mapArray[randPos]);
				break;
			}
		}


	irr::scene::ITriangleSelector* selector = 0;
	irr::scene::IMetaTriangleSelector* metaSelector = this->p_Device->getSceneManager()->createMetaTriangleSelector();
	irr::scene::ISceneNodeAnimator* collisionAnim=0;
	
	selector = this->p_Device->getSceneManager()->createTriangleSelector(this->p_Map3D->getMapBaseNode());
	this->p_Map3D->getMapBaseNode()->setTriangleSelector(selector);

	selector->drop();
	metaSelector->addTriangleSelector(selector);
	selector->drop();
	selector=0;
	collisionAnim = this->p_Device->getSceneManager()->createCollisionResponseAnimator(metaSelector,this->p_Cam,irr::core::vector3df(10.0f,12.0f,10.0f),irr::core::vector3df(0.0f,-3.0f,0.0f));
	metaSelector->drop();
	metaSelector=0;
	//this->p_Cam->addAnimator(collisionAnim);
	this->player->getPlayerSceneNode()->addAnimator(collisionAnim);
	//collisionAnim->drop();
	//collisionAnim=0;
	
	this->pathFinderMain = new MapSystem::CPathFinder(this->p_Map3D->getMainMap());
	
	
}


void Environment3D::drawEnvironment3D()
{
	if(this->p_Settings->getFileOpenFlag())
	{
		this->initEnvironment();
		

		this->p_Settings->setFileOpenFlag(false);
		
	}

	if(this->p_Map3D!=NULL)
	{

		irr::core::array<irr::scene::ISceneNode*,irr::core::irrAllocator<irr::scene::ISceneNode*>> tempNodesList;
		this->p_Device->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_BILLBOARD,tempNodesList);

		for(irr::u32 i=0;i<tempNodesList.size();i++)
		{
			if(tempNodesList[i]->getPosition().getDistanceFrom(this->p_Cam->getPosition()) >200.0f)
			{
				tempNodesList[i]->setVisible(false);
			}
			else
			{
				tempNodesList[i]->setVisible(true);
			}

			
		}

	//bottom bar
	irr::u32 screenWidth = this->p_Device->getVideoDriver()->getScreenSize().Width;
	irr::u32 screenHeight=this->p_Device->getVideoDriver()->getScreenSize().Height;

	this->p_Device->getVideoDriver()->draw2DRectangle(irr::video::SColor(100,0,0,0),irr::core::rect<irr::s32>(0,screenHeight-25,screenWidth,screenHeight));
	this->p_Device->getGUIEnvironment()->getSkin()->getFont()->draw(L"H - Help Window",irr::core::rect<irr::s32>(150,screenHeight-25,250,screenHeight),irr::video::SColor(255,255,255,255));
	
	if(this->p_Settings->getHelpFlag())
	{
		this->p_Device->getVideoDriver()->draw2DRectangle(irr::video::SColor(100,0,0,0),irr::core::rect<irr::s32>((screenWidth/2)-100,(screenHeight/2)-100,(screenWidth/2)+100,(screenHeight/2)+100));
		this->p_Device->getGUIEnvironment()->getSkin()->getFont()->draw(L"S- select node",irr::core::rect<irr::s32>((screenWidth/2)-80,(screenHeight/2)-80,(screenWidth/2)+30,(screenHeight/2)-60),irr::video::SColor(255,255,255,255));
		this->p_Device->getGUIEnvironment()->getSkin()->getFont()->draw(L"ESC- Exit",irr::core::rect<irr::s32>((screenWidth/2)-80,(screenHeight/2)-60,(screenWidth/2)+30,(screenHeight/2)-40),irr::video::SColor(255,255,255,255));
	}
	
		
	



	//highlight the selected node on the 3d map
		//case a ray
		
			

		irr::core::line3df collisionRay;
		collisionRay.start = this->p_Cam->getPosition();
		collisionRay.end = collisionRay.start + (this->p_Cam->getTarget()-collisionRay.start).normalize()* 2000.0f;

		//get the point of intersection
		irr::core::vector3df intersectionPoint;
		//irr::scene::ITriangleSelector* selector;
		irr::core::triangle3df triNode;
	


		irr::scene::ISceneNode* selNode;
		selNode =   this->p_Device->getSceneManager()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(collisionRay,intersectionPoint,triNode);
		
		


		if(selNode)
		{
			this->p_Settings->setSFlag(true);


			irr::f32 posX,posY;
			
			posX = intersectionPoint.X;
			posY = intersectionPoint.Z;
			/*irr::core::stringw strDet;
			strDet = "posx : ";
			strDet+=posX;
			strDet+=" posy : ";
			strDet+=posY;
			//this->p_Device->getGUIEnvironment()->getSkin()->getFont()->draw(strDet.c_str(),irr::core::rect<irr::s32>(0,0,100,25),irr::video::SColor(255,255,255,255));
			*/
			
			for(int ni = 0;ni<this->p_Map3D->getMainMap()->nodesCount;ni++)
			{
				if(posX > this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->X-(this->p_Map3D->getMainMap()->nodeWidth/2)
					&& posX < this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->X+(this->p_Map3D->getMainMap()->nodeWidth/2)
					&& posY >this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->Y-(this->p_Map3D->getMainMap()->nodeHeight/2)
					&& posY < this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->Y+(this->p_Map3D->getMainMap()->nodeHeight/2))
				{
					irr::core::stringw str;
					str+="Node Selected : ";
					str+=this->p_Map3D->getMainMap()->mapArray[ni]->getNodeNumber();
					
					this->p_Device->getGUIEnvironment()->getSkin()->getFont()->draw(str.c_str(),irr::core::rect<irr::s32>(0,screenHeight-25,100,screenHeight),irr::video::SColor(255,255,255,255));
					irr::video::SMaterial mat;
					mat.setTexture(0,this->p_Device->getVideoDriver()->getTexture("../data/textures/white.jpg"));
					this->p_Device->getVideoDriver()->setMaterial(mat);
					this->p_Device->getVideoDriver()->setTransform(irr::video::ETS_WORLD,irr::core::matrix4());
					
					
					this->p_Device->getVideoDriver()->draw3DLine(irr::core::vector3df(this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->X-(this->p_Map3D->getMainMap()->nodeWidth/2),1.5f,this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->Y-(this->p_Map3D->getMainMap()->nodeHeight/2)),
						irr::core::vector3df(this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->X+(this->p_Map3D->getMainMap()->nodeWidth/2),1.5f,this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->Y+(this->p_Map3D->getMainMap()->nodeHeight/2)),irr::video::SColor(255,255,255,255));

					this->p_Device->getVideoDriver()->draw3DLine(irr::core::vector3df(this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->X+(this->p_Map3D->getMainMap()->nodeWidth/2),1.5f,this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->Y-(this->p_Map3D->getMainMap()->nodeHeight/2)),
						irr::core::vector3df(this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->X-(this->p_Map3D->getMainMap()->nodeWidth/2),1.5f,this->p_Map3D->getMainMap()->mapArray[ni]->getCurrentNodePosition()->Y+(this->p_Map3D->getMainMap()->nodeHeight/2)),irr::video::SColor(255,255,255,255));
					
					if( this->p_Settings->getDestSelFlag()==true)
					{
						for(int pi=0;pi<this->p_Map3D->getMainMap()->nodesCount;pi++)
						{
							float pposX = this->player->getPlayerSceneNode()->getPosition().X;
							float pposY = this->player->getPlayerSceneNode()->getPosition().Z;

							if(pposX > this->p_Map3D->getMainMap()->mapArray[pi]->getCurrentNodePosition()->X-(this->p_Map3D->getMainMap()->nodeWidth/2)
								&& pposX < this->p_Map3D->getMainMap()->mapArray[pi]->getCurrentNodePosition()->X+(this->p_Map3D->getMainMap()->nodeWidth/2)
								&& pposY >this->p_Map3D->getMainMap()->mapArray[pi]->getCurrentNodePosition()->Y-(this->p_Map3D->getMainMap()->nodeHeight/2)
								&& pposY < this->p_Map3D->getMainMap()->mapArray[pi]->getCurrentNodePosition()->Y+(this->p_Map3D->getMainMap()->nodeHeight/2))
							{
								this->player->setNodeUnderPlayer(this->p_Map3D->getMainMap()->mapArray[pi]);
							}
						}

						if(this->p_Map3D->getMainMap()->mapArray[ni]->getWalkableState()!=0)
						{
							this->p_Settings->setDestSelFlag(false);
						}
						else
						{
						this->pathFinderMain->emptyPathList();
						this->p_Map3D->getMainMap()->resetMap();
						this->pathFinderMain->setDestination(NULL);
						this->player->nodeToReach=1;
						this->pathFinderMain->setDestination(this->p_Map3D->getMainMap()->mapArray[ni]);
						this->player->getPlayerSceneNode()->setPosition(irr::core::vector3df(this->player->getNodeUnderPlayer()->getCurrentNodePosition()->X,0.0f,this->player->getNodeUnderPlayer()->getCurrentNodePosition()->Y));
						}
					}

				}
			}
		
		}
		else
		{
			this->p_Settings->setSFlag(false);
		}

		//}





		//chk if pathfinding flag is true
		if(this->p_Settings->getDestSelFlag() && selNode!=NULL && this->p_Settings->getFindingPathFlag()==false)
		{
			this->p_Settings->setFindingPathFlag(true);
			this->pathFinderMain->CalculatePath(this->player->getNodeUnderPlayer(),this->pathFinderMain->getDestinationNode());
			if(this->pathFinderMain->getFoundPathList()->size()>0)
			{
			int tsize = this->pathFinderMain->getFoundPathList()->size();
			this->player->getPlayerSceneNode()->setPosition(irr::core::vector3df(this->pathFinderMain->getFoundPathList()->at(tsize-1)->getCurrentNodePosition()->X,0.0f,this->pathFinderMain->getFoundPathList()->at(tsize-1)->getCurrentNodePosition()->Y));
			}
			this->p_Settings->setDestSelFlag(false);
			this->p_Settings->setFindingPathFlag(false);
		}
		


		//draw the path representation

		if((int)this->pathFinderMain->getFoundPathList()->size()>0 && this->player->stopFlag==false)
		{




			MapSystem::Node* prevNode,*nextNode;
			int listSize = this->pathFinderMain->getFoundPathList()->size();
			prevNode = this->pathFinderMain->getFoundPathList()->at(listSize-1);
			for(int i=(int)pathFinderMain->getFoundPathList()->size()-2;i>=0;i--)
			{
				
				nextNode = this->pathFinderMain->getFoundPathList()->at(i);
				this->p_Device->getVideoDriver()->draw3DLine(irr::core::vector3df(prevNode->getCurrentNodePosition()->X,2.0f,prevNode->getCurrentNodePosition()->Y),irr::core::vector3df(nextNode->getCurrentNodePosition()->X,2.0f,nextNode->getCurrentNodePosition()->Y),irr::video::SColor(255,255,255,255));
				
				

				prevNode = nextNode;
			}

			
		

			if(this->player->animType!=irr::scene::EMAT_RUN)
			{
				this->player->animType=irr::scene::EMAT_RUN;
				this->player->getPlayerSceneNode()->setMD2Animation(this->player->animType);
			}
			
			//let the character follow the path
			
			prevNode = this->pathFinderMain->getFoundPathList()->at(listSize-this->player->nodeToReach);
			nextNode = this->pathFinderMain->getFoundPathList()->at(listSize-(this->player->nodeToReach+1));

			this->p_Device->getVideoDriver()->draw3DLine(this->player->getPlayerSceneNode()->getPosition(),irr::core::vector3df(nextNode->getCurrentNodePosition()->X,2.0f,nextNode->getCurrentNodePosition()->Y));
			
			//std::cout<<this->player->getPlayerSceneNode()->getPosition().getDistanceFrom(irr::core::vector3df(nextNode->getCurrentNodePosition()->X,0.0f,nextNode->getCurrentNodePosition()->Y))<<std::endl;
			//std::cout<<"prevNode :"<<prevNode->getNodeNumber()<<std::endl;
			//std::cout<<"nextNode :"<<nextNode->getNodeNumber()<<std::endl;
			

			if(this->player->getPlayerSceneNode()->getPosition().getDistanceFrom(irr::core::vector3df(nextNode->getCurrentNodePosition()->X,0.0f,nextNode->getCurrentNodePosition()->Y)) < 13.5f)
			{
				
				this->player->getPlayerSceneNode()->setPosition(irr::core::vector3df(nextNode->getCurrentNodePosition()->X,0.0f,nextNode->getCurrentNodePosition()->Y));
				if(this->pathFinderMain->getFoundPathList()->at(0)->getNodeNumber()==nextNode->getNodeNumber())
				{
					//this->pathFinderMain->getFoundPathList()->clear();
					this->player->stopFlag=true;
					this->player->nodeToReach=1;
				}
				//this->pathFinderMain->getFoundPathList()->erase(this->pathFinderMain->getFoundPathList()->begin()+(listSize-this->player->nodeToReach));
				this->player->nodeToReach+=1;
			}
			if(this->player->stopFlag!=true)
			{
			irr::core::vector3df moveUnit = (irr::core::vector3df(nextNode->getCurrentNodePosition()->X,0.0f,nextNode->getCurrentNodePosition()->Y)-irr::core::vector3df(prevNode->getCurrentNodePosition()->X,0.0f,prevNode->getCurrentNodePosition()->Y)).normalize();
			this->player->positionMain=this->player->getPlayerSceneNode()->getPosition();
			this->player->positionMain+=moveUnit*1.1f;
			float yRot=0.0f,x_x,y_y;
			y_y = prevNode->getCurrentNodePosition()->Y-nextNode->getCurrentNodePosition()->Y;
			x_x = prevNode->getCurrentNodePosition()->X-nextNode->getCurrentNodePosition()->X;
		
			yRot = std::atan2(y_y,x_x);
			yRot = (180*yRot)/(22/7);
			this->player->getPlayerSceneNode()->setRotation(irr::core::vector3df(0.0f,-yRot+180,0.0f));
			this->player->getPlayerSceneNode()->setPosition(this->player->positionMain);
			
			}
		}
		else
		{
			this->pathFinderMain->getFoundPathList()->clear();
			if(this->player->animType!=irr::scene::EMAT_STAND)
			{
				this->player->animType=irr::scene::EMAT_STAND;
				this->player->getPlayerSceneNode()->setMD2Animation(this->player->animType);
				this->player->stopFlag=false;
			}
		}






	}


}