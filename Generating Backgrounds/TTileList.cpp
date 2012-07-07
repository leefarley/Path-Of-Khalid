#include "StdAfx.h"
#include "TTileList.h"

TTileList::TTileList(void)
{
	TileArray = gcnew array<TTile^>(TILE_COUNT);

	for (int i = 0;i<TileArray->Length;i++)
	{
		//the tiles are numbered from 0 - TILE_COUNT so this for loop will add them to the array
		TileArray[i] = gcnew TTile("tiles/"+i+".png",true);
	}
	//tile 0 & 1 are just magenta, these are the tiles that the player cannot collide with
	TileArray[0]->setMyState(false);
	TileArray[1]->setMyState(false);
	//tile 30 is lava, the player can fall through this and another method picks up the collison detection
	TileArray[30]->setMyState(false);

	// set any magenta clour on the tiles to be transparent.
	for (int i = 0;i<TileArray->Length;i++)
		TileArray[i]->setTransparent();
}

Bitmap^ TTileList::getTTile(int tileIndex)
{
	//returns the image that has the corrosponding index to the one passed in.
	return TileArray[tileIndex]->getImage();
}

bool TTileList::isTileWalkable(int TileIndex)
{
	//returns if the tile is walkable or not.
	return TileArray[TileIndex]->getMyState();
}
