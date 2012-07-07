#pragma once

#include "PickupSprite.h"
#include "PlayerSprite.h"
#include "TViewport.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//possible states that the non movible sprites can have, a pickup sprite can only have one state
#define POTION 0
//this is the amount of different types of pickup items the is.
#define PICKUP_TYPES 1

ref class pickupList
{
private:
	Graphics^ canvas;
	PickupSprite^ head;
	PickupSprite^ tail;
	PlayerSprite^ player;
	TViewport^ viewPort;
	array<Bitmap^>^ typeImages;

public:
	pickupList(Graphics^ stCanvas, PlayerSprite^ stPlayer , TViewport^ stViewPort);
	void addItem(int stXPos, int stYPos,int stType);
	void clearList();
	bool isEmpty();
	void deleteSprite(PickupSprite^ spriteToDelete);
	void draw(Rectangle^ viewRect);
	void bringOutYourDead();
	void PickedUp();
};
