#include "StdAfx.h"
#include "SpriteList.h"

SpriteList::SpriteList(Graphics^ stCanvas, Random^ stGen, TTileMap^ stMap, PlayerSprite^ stPlayer, TViewport^ stViewPort)
{
	canvas = stCanvas;
	rGen = stGen;
	worldMap = stMap;
	player = stPlayer;
	head = nullptr;
	tail = nullptr;
	viewPort = stViewPort;
}

//================================================================================================================================
//adds a new sprite into the linked list. if it is the first one in the list it is set to head an tail and any sprites after this
//are pointed to by the current tail and then are made the tail.
//================================================================================================================================
void SpriteList::addSprite(int newXPos, int newYPos,int boundsLeft, int boundsRight,int stSpeed,
						   array<String^,2>^ spriteSheets, array<int>^ spriteCount,int health,
						   int baseAttack, int damageModifyer, double defence)
{
	//if there is nothing in the list already add the new sprite to the head and tail pointers 
	if (head == nullptr){
		head = gcnew EnemySprite(canvas,rGen,newXPos, newYPos, boundsLeft, boundsRight,stSpeed,spriteSheets,
			spriteCount,worldMap,player,health,baseAttack,damageModifyer,defence);
		tail = head;
		//else add the new sprite to the tail's pointer then make the new sprite the tail
	}else{
		tail->next = gcnew EnemySprite(canvas,rGen,newXPos, newYPos, boundsLeft, boundsRight,stSpeed, spriteSheets,
			spriteCount,worldMap,player,health,baseAttack,damageModifyer,defence);
		tail = tail->next;
	}
}


//=================================================================================================================================
// calculate sprite state method
//will run throught the sprites in the list if the sprite is within the screen then it will have its sprite state calculated
//=================================================================================================================================
void SpriteList::calculateSpriteStates()
{

	if (isEmpty()  != true)
	{		
		//get the dimentions of the viewport
		Rectangle^ calculateArea = viewPort->getViewRect();
		EnemySprite^ nodeWalker = head;
		//is there any more sprites in the list
		while (nodeWalker != nullptr)
		{
			//is the sprite in the viewport?
			if (calculateArea->Contains(nodeWalker->getXPos(), nodeWalker->getYPos()))
			{
				nodeWalker->calculateSpriteState();

			}
			// go to the next sprite in the list
			nodeWalker = nodeWalker->next;
		}
	}
}

//=================================================================================================================================
// implement sprite state method
//will run throught the sprites in the list if the sprite is within the screen then it will have its sprite state implemented
//=================================================================================================================================
void SpriteList::implementSpriteStates()
{
	// is there any sprites to run this method on
	if (isEmpty()  != true)
	{
		// get the area of the view port
		Rectangle^ calculateArea = viewPort->getViewRect();
		EnemySprite^ nodeWalker = head;
		while (nodeWalker != nullptr)
		{
			// is the sprite in the viewport
			if (calculateArea->Contains(nodeWalker->getXPos(), nodeWalker->getYPos()))
			{
				nodeWalker->implementSpriteState();
			}
			// get the next sprite form the list
			nodeWalker = nodeWalker->next;
		}
	}
}
//============================================================================================================================
// isEmpty method
//	will check if the sprite list has any sprites in it
//============================================================================================================================
bool SpriteList::isEmpty()
{
	//if the head is empty then there cant be anything in the list
	if (head == nullptr)
	{
		return true;
	}
	return false;

}

//============================================================================================================================
//	clear list
//  does what you would expect, clears the linked list of all sprites.
//============================================================================================================================
void SpriteList::clearList()
{
	head = nullptr;
	tail = nullptr;
}

//============================================================================================================================
// Delete Sprite Method
// takes a sprite and will remove it index from the list, in doing this it will put the sprite ot of scope and the garbage collector
// will remove it from memory
//============================================================================================================================
void SpriteList::deleteSprite(EnemySprite^ spriteToDelete)
{
	EnemySprite^ nodeWalker = head;
	if (head == spriteToDelete)
	{
		// if the sprite to delete is the ead then the next sprite in the list becomes the head
		head = head->next;
	}else{
		//checking all the sprites next pointer to see if it is the sprite that you want to delete.
		while (nodeWalker->next != spriteToDelete)
		{
			nodeWalker = nodeWalker->next;
		}

		//if (tail == spriteToDelete)
		//{
		//	tail = nodeWalker;
		//}
	}
	// this will put the sprite to the right of the sprite to delete in the pointer of the sprite to the left of the sprite to
	// delete's next pointer, this is removing any reference to the sprite.
	nodeWalker->next = spriteToDelete->next;
}

//============================================================================================================================
// draw spritelist method
//	this method will check if the sprite is 
//============================================================================================================================
void SpriteList::drawViewPortSprites(Rectangle^ viewRect)
{
	EnemySprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		//calculate the dimentions of the sprite
		Rectangle temp = Rectangle (nodeWalker->getXPos(),nodeWalker->getYPos(),nodeWalker->getfWidth(),nodeWalker->getfHeight());
		//check if any part of the sprite is in the viewport
		if (viewRect->IntersectsWith(temp))
		{
			nodeWalker->draw(viewRect);
		}
		nodeWalker = nodeWalker->next;
	}
}

//============================================================================================================================
// spriteHit Method
// this occurs if the player sprite preforms a attack,
//============================================================================================================================
int SpriteList::spriteHit()
{
	int addScore = 0;
	if (isEmpty() != true)
	{
		// calculate what area that the attack will do damage in.
		Rectangle^ attackRect = player->getAttackArea();
		EnemySprite^ nodeWalker = head;
		while(nodeWalker != nullptr)
		{
			if (nodeWalker->getIsAlive() == true)
			{
				// checks the area the sprite can be hurt in intersects with the attack area
				if (nodeWalker->defend(attackRect))
				{
					//if successful a damage is calculated
					int damageDealt = player->calculateDamage();
					//add 5 to the players score for a hit
					addScore = 5;
					//sprites hit method is run to calculate damage done
					nodeWalker->Hit(damageDealt);
					//change the player off the attack state
					player->setAttackState(false);
				}
			}
			nodeWalker = nodeWalker->next;
		}
	}
	return addScore;
}

//============================================================================================================================
//	sprite attack method
// this method will run through all sprites to see if one is in a attacking state, if so it will see if it intersects withe the player
//============================================================================================================================
void SpriteList::spriteAttack()
{
	if (isEmpty() != true)
	{
		//initlize a rectangle
		Rectangle^ attackRect;
		EnemySprite^ nodeWalker = head;
		while(nodeWalker != nullptr)
		{
			//check if the sprites bool attack value is set to true
			if (nodeWalker->getIsAttacking() == true)
			{
				//will get the area that will deal damage from the sprite
				attackRect = nodeWalker->getAttackArea();
				//checks if that value intersects with the players area that he can be hurt in.
				if (player->defend(attackRect))
				{
					int damageDealt = nodeWalker->calculateDamage();
					player->Hit(damageDealt);
					nodeWalker->setAttackState(false);
				}
			}
			nodeWalker = nodeWalker->next;
		}
	}	
}

//============================================================================================================================
// bring out your dead method
// will check all the sprites is alive values, if false the sprite will be removed form the sprite list
//============================================================================================================================
void SpriteList::bringOutYourDead()
{
	if (isEmpty()  != true)
	{
		// get the area of the view port
		Rectangle^ calculateArea = viewPort->getViewRect();
		EnemySprite^ nodeWalker = head;
		while (nodeWalker != nullptr)
		{
			//need to keep the boss in the list to check that he is dead.
			if (nodeWalker != tail)
			{
				//checks nodewalkers x and y pos are not in the viewrect
				if (!calculateArea->Contains(nodeWalker->getXPos(), nodeWalker->getYPos()))
				{
					//checks if the sprite has been killed
					if(nodeWalker->getIsAlive() == false)
					{
						//removes the sprite from the spritelist and the garbage collector will distroy him as there are no more pointers to him.
						deleteSprite(nodeWalker);
					}
				}
			}
			// get the next sprite in the list.
			nodeWalker = nodeWalker->next;
		}
	}
}

//============================================================================================================================
// bring out your dead method
// will check all the sprites is alive values, if false the sprite will be removed form the sprite list
//============================================================================================================================
bool SpriteList::endGame()
{
	//if the boss which will always be at the end of the spriteList is no longer alive then return true to the game ending
	if (tail->getIsAlive() == false)
		return true;

	return false;

}