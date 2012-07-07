#include "StdAfx.h"
#include "PickupSprite.h"
//============================================================================================================================
//  Pickup Sprite Constructor
//	Adds the classes Local references to the instance
//============================================================================================================================
PickupSprite::PickupSprite(Graphics^ stCanvas,int stXPos, int stYPos,Bitmap^ myItem,int stType)
{
	canvas = stCanvas;
	xPos = stXPos;
	yPos = stYPos;
	myImage = myItem;
	type = stType;
	isAlive = true;
	//this becomes null because every new sprite becomes the tail, when the next sprite is added this will point to him
	next = nullptr;
}
//============================================================================================================================
// Picked up method
//	checks if this sprite intersects with the player
//============================================================================================================================
bool PickupSprite::PickedUp(Rectangle^ playerRect)
{	
	//creating a rect with the dimentions of the potion
	Rectangle temp = Rectangle(xPos,yPos,fWidth,fHeight);
	//if the players rect intersects with then isAlive is set to false so it will be removed from the list.
	if (playerRect->IntersectsWith(temp))
	{
		isAlive = false;
		return true;
	}
	return false;
}

//============================================================================================================================
//  draw method
//	will alter the x and y values and draw
//============================================================================================================================
void PickupSprite::draw(Rectangle^ viewRect)
{
	int drawX = xPos - viewRect->X; //adjusts the sprites position from relitive to the worldmap to relitive to the viewport
	int drawY = yPos - viewRect->Y;
	//draws to the offscreem canvas.
	canvas->DrawImage(myImage,drawX,drawY);
}