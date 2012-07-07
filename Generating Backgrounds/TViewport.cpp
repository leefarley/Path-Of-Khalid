#include "StdAfx.h"
#include "TViewport.h"



TViewport::TViewport(int stX, int stY,int stViewXMax,int stViewYMax, 
					 Graphics^ stCanvas, Random^ stGen)
{
	// this is the place where the screen will be drawn relitive to the world image
	viewWorldX = stX;
	viewWorldY = stY;

	// these values are the maximum limits for the viewport. will be the max of the screen for this example
	viewXMax = stViewXMax;
	viewYMax = stViewYMax;

	// calculates the amount of tiles that will fit on the screen at one time.
	viewTilesWide = (viewXMax/TILE_SIDE);
	viewTilesHigh = (viewYMax/TILE_SIDE);

	// passes in the canvas to be drawn to and the random generator.
	canvas = stCanvas;
	rGen = stGen;

	// creates a TTilemap that will take the x and y coordnates and draw only the image given to the canvas
	ground = gcnew TTileMap(canvas,rGen,viewTilesWide, viewTilesHigh ,GRID_WIDTH, GRID_HEIGH,0);
	
	background = gcnew Bitmap("midground.png");
	sky = gcnew Bitmap ("mountains.png");
	background->MakeTransparent(background->GetPixel(0,0));

	// these values will be calculated in the draw method, these values are just for initilization
	viewTileX = 0;
	viewTileY = 0;
	xOffset = 0;
	yOffset = 0;
	
	centerPoint.X = ((viewTilesWide*TILE_SIDE)/2);
	centerPoint.Y = ((viewTilesHigh*TILE_SIDE)/2);


}

void TViewport::viewportMove(int xMove, int yMove)
{
	//will check both left and right sides of the screen if deemed worthy the worlds x coordanate will be incremented
	if (((viewWorldX+xMove) > 0)&&((viewWorldX+xMove+viewXMax) < GRID_WIDTH*TILE_SIDE))
		viewWorldX += xMove;

	// same as abouve but with the Y axis
	if (((viewWorldY+yMove) > 0)&&((viewWorldY+viewYMax+yMove)<(GRID_HEIGH*TILE_SIDE)))
		viewWorldY += yMove;
}

void TViewport::moveRelativeToPlayer(int playerWorldX, int playerWorldY)
{
	int tempViewWorldX = (playerWorldX - centerPoint.X);
	int tempViewWorldY = (playerWorldY - centerPoint.Y);

	if ((tempViewWorldX > 0)&&((tempViewWorldX + viewXMax) < GRID_WIDTH * TILE_SIDE))
		viewWorldX = tempViewWorldX;

	if ((tempViewWorldY >0)&&((tempViewWorldY + viewYMax) < GRID_HEIGH * TILE_SIDE))
		viewWorldY = tempViewWorldY;
}

void TViewport::viewportDraw()
{
	//slow the scrolling of the two background images for paralax scrolling
	int backWorldX = (viewWorldX / 4);
	int skyWorldX = (viewWorldX / 17);

	//select the part of the image that is to be displayed
	Rectangle skybounds = Rectangle(skyWorldX,0,800,600);
	Rectangle backbounds = Rectangle(backWorldX,0,800,600);


	// calculates what tiles will be drawn at 0,0 of the ViewPort. 
	viewTileX = viewWorldX / TILE_SIDE; 
	viewTileY= viewWorldY / TILE_SIDE;


	//Calculates the offset of the Viewport
	xOffset = viewWorldX % TILE_SIDE;
	yOffset = viewWorldY % TILE_SIDE;


	
	//draw the images to the viewport.
	canvas->DrawImage(sky,0,SKY_OFFSET,skybounds,GraphicsUnit::Pixel);
	canvas->DrawImage(background,0,BACKGROUND_OFFSET,backbounds,GraphicsUnit::Pixel);
	// will pass the TTileMap the initial values that are needed to draw the correct tiles on the viewPort
	ground->drawMap(viewTileX,viewTileY,xOffset,yOffset);
	
}

bool TViewport::isOnWall()
{
	bool temp = false;
	if ((viewWorldX > 0)||(viewWorldX+viewXMax < GRID_WIDTH*TILE_SIDE))
		temp = true;

	if ((viewWorldY > 0)||(viewWorldY+viewYMax < GRID_WIDTH*TILE_SIDE))
		temp = true;

	return temp;

}

Rectangle^ TViewport::getViewRect()
{
	return Rectangle(viewWorldX, viewWorldY, viewXMax, viewYMax);
}
