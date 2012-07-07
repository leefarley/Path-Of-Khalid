#pragma once

#include "TTileMap.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#define TILE_SIDE 32
#define GRID_WIDTH 200
#define GRID_HEIGH 30

#define SKY_OFFSET -20
#define BACKGROUND_OFFSET 200

ref class TViewport
{
private:
	int viewWorldX, viewWorldY;  // this is the coordinates of the Viewport relitive to the world in pixels
	int viewTilesWide, viewTilesHigh; // this is the amount of tiles in the viewport
	int viewXMax, viewYMax; // this is the amount of pixels in the viewport area
	int viewTileX, viewTileY; // this is the tile that is in the upper left of the tiles to be drawn
	int xOffset, yOffset;// this is the offset if the tiles dont fit neatly on the page
	Point centerPoint;
	TTileMap^ ground;
	Bitmap^ sky;
	Bitmap^ background;
	Graphics^ canvas;
	Random^ rGen;

public:
	TViewport(int stX, int stY,int stViewXMax,int stViewYMax,
	Graphics^ stCanvas, Random^ stGen);
	void viewportMove(int xMove, int yMove);
	void moveRelativeToPlayer(int playerWorldX, int playerWorldY);
	void viewportDraw();
	Rectangle^ getViewRect();

	bool isOnWall();
	TTileMap^ getWorldMap()				{return ground;}

};
