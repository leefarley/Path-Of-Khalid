#pragma once

#include "TTile.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//this is the amount of different tiles in the tile list.
#define TILE_COUNT 42


ref class TTileList
{
private:
	array<TTile^>^ TileArray;


public:
	TTileList(void);
	Bitmap^ getTTile(int tileIndex);
	bool isTileWalkable (int TileIndex);
};
