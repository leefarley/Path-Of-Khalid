#pragma once

#include "TTileList.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
		using namespace System::IO;

#define TILE_SIDE 32

ref class TTileMap
{
private:
	array<int,2>^ worldMap;
	TTileList^ tilesArray;
	Graphics^ canvas;
	Random^ rGen;
	int viewRows,viewCols;

public:
	TTileMap(Graphics^ stCanvas, Random^ stGen,int stViewCols,int stViewRows, int gridWidth, int gridHeight, int type);
	void drawMap(int stX,int stY, int xOffset, int yOffset);
	bool isWalkable(int col, int row);
	int getTileType(int col,int row);
};
