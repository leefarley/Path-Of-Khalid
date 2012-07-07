#pragma once


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



ref class PickupSprite
{
private:
	Graphics^ canvas;
	int xPos, yPos;
	int fWidth, fHeight, type;
	Bitmap^ myImage;
	bool isAlive;

public:
	PickupSprite^ next;

public:
	PickupSprite(Graphics^ stCanvas,int stXPos, int stYPos,Bitmap^ myItem,int stType);
	bool PickedUp(Rectangle^ playerRect);
	void draw(Rectangle^ viewRect);

	int getXPos ()			{return xPos;}
	int getYPos ()			{return yPos;}
	int getfWidth ()		{return fWidth;}
	int getfHeight ()		{return fHeight;}
	bool getIsAlive()		{return isAlive;}
};
