#include "StdAfx.h"
#include "TTileMap.h"

TTileMap::TTileMap(Graphics^ stCanvas, Random^ stGen,int stViewCols,int stViewRows, int gridWidth, int gridHeight, int type)
{
	canvas = stCanvas;
	tilesArray = gcnew TTileList();
	viewRows = stViewRows;
	viewCols = stViewCols;
	worldMap = gcnew array<int,2>(gridHeight,gridWidth);
	array<String^>^ temp = gcnew array<String^> (gridWidth);
	rGen = stGen;

	StreamReader^ sr = File::OpenText("tiles/tilemap.txt");
	String^ currentLine;

	int i = 0;
	while (currentLine = sr->ReadLine())
	{
		temp = currentLine->Split(',');
		for (int w = 0; w < temp->Length; w++)
		{
			//this has to be a ToInt32 in the SP1 for visual studio. there is no ToInt
			worldMap[i,w] = Convert::ToInt32(temp[w]);
		}
		i++;
	}
}

void TTileMap::drawMap(int stX,int stY, int xOffset, int yOffset)
{
	int temp;
	Bitmap^ tempBitmap;
	for (int y = 0; y < viewRows+1; y++)
	{
		for (int x = 0; x < viewCols+1; x++)
		{
			temp = worldMap[stY+y,stX+x];
			tempBitmap = tilesArray->getTTile(temp);
			canvas->DrawImage(tempBitmap,(TILE_SIDE * x)-xOffset, (TILE_SIDE * y)-yOffset);
		}
	}
}

bool TTileMap::isWalkable(int col,int row)
{
	int temp = worldMap[col,row];
	return tilesArray->isTileWalkable(temp);
}

int TTileMap::getTileType(int col,int row)
{
 	int temp = worldMap[col,row];
	return temp;
}