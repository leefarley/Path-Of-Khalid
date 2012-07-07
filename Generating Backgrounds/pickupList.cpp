#include "StdAfx.h"
#include "pickupList.h"

//============================================================================================================================
//  Pickup List Constructor
//	This class manages the Pickup items, these are varibles that are needed to create and maintain these
//============================================================================================================================
pickupList::pickupList(Graphics^ stCanvas, PlayerSprite^ stPlayer , TViewport^ stViewPort)
{
	canvas = stCanvas;
	player = stPlayer;
	viewPort = stViewPort;

	head = nullptr;
	tail = nullptr;
	typeImages = gcnew array<Bitmap^>(PICKUP_TYPES);
	//this is the image for the first type.... there is only one type at the moment
	typeImages[0] = gcnew Bitmap("potion.bmp");
	//set the top left colour to be transparent
	typeImages[0]->MakeTransparent(typeImages[0]->GetPixel(0,0));
}


//============================================================================================================================
// add Item method
//	Adds a new item to the list.
//============================================================================================================================
void pickupList::addItem(int stXPos, int stYPos, int stType)
{
	//if none in the list the new item becomes both head and tail
	if (head == nullptr){
		head = gcnew PickupSprite(canvas, stXPos, stYPos,typeImages[stType],stType);
		tail = head;
	}else{
	//if there are already items in the list, add the new item to the tail then make it the new tail
		tail->next =  gcnew PickupSprite(canvas, stXPos, stYPos,typeImages[stType],stType);
		tail = tail->next;
	}
}

//============================================================================================================================
// isEmpty method
//	will check if the sprite list has any sprites in it
//============================================================================================================================
bool pickupList::isEmpty()
{
	//if there is nothing in the head then the list must be empty
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
void pickupList::clearList()
{
	head = nullptr;
	tail = nullptr;
}

//============================================================================================================================
// Delete Sprite Method
// takes a sprite and will remove it index from the list, in doing this it will put the sprite ot of scope and the garbage collector
// will remove it from memory
//============================================================================================================================
void pickupList::deleteSprite(PickupSprite^ spriteToDelete)
{
	PickupSprite^ nodeWalker = head;
	if (head == spriteToDelete)
	{
		// if the sprite to delete is the head then the next sprite in the list becomes the head
		head = head->next;
	}else{
		//checking all the sprites next pointer to see if it is the sprite that you want to delete.
		while (nodeWalker->next != spriteToDelete)
		{
			nodeWalker = nodeWalker->next;
		}

		if (tail == spriteToDelete)
		{
			tail = nodeWalker;
		}
	}
	// this will put the sprite to the right of the sprite to delete in the pointer of the sprite to the left of the sprite to
	// delete's next pointer, this is removing any reference to the sprite.
	nodeWalker->next = spriteToDelete->next;
}

void pickupList::draw(Rectangle^ viewRect)
{
	PickupSprite^ nodeWalker = head;
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
// bring out your dead method
// will check all the sprites is alive values, if false the sprite will be removed form the sprite list
//============================================================================================================================
void pickupList::bringOutYourDead()
{
	// is there items in the list to check?
	if (isEmpty()  != true)
	{
		PickupSprite^ nodeWalker = head;
		//loop through the items in the list
		while (nodeWalker != nullptr)
		{
				//if an item has had its isAlive bool set to false it is deleted
				if(nodeWalker->getIsAlive() == false)
				{
					deleteSprite(nodeWalker);
				}
				//increments the loop.
			nodeWalker = nodeWalker->next;
		}
	}
}

//============================================================================================================================
// PickedUp method
//	will check if there is a sprite collision with the player and an item
//============================================================================================================================
void pickupList::PickedUp()
{
	// is there items in the list to check?
	if (isEmpty() != true)
	{
		PickupSprite^ nodeWalker = head;
		//loop through the items in the list
		while (nodeWalker != nullptr)
		{
			//is that potion in the players pickup area
			if (nodeWalker->PickedUp(player->getPickUpArea()))
			{
				//if so the nodewalker will change its isAlive to false and the bring out your dead method will remove it
				//then the players health counter will be altered.
				player->addPotion();
			}
			//increments the loop
			nodeWalker = nodeWalker->next;
		}
	}
}