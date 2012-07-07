#pragma once

#include "EnemySprite.h"
#include "TViewport.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

ref class SpriteList
{
private:
	EnemySprite^ head;
	EnemySprite^ tail;
	PlayerSprite^ player;
	Graphics^ canvas;
	TTileMap^ worldMap;
	Random^ rGen;
	TViewport^ viewPort;

public:
	SpriteList(Graphics^ stCanvas, Random^ stGen, TTileMap^ stMap, PlayerSprite^ stPlayer , TViewport^ stViewPort);

	void addSprite(int newXPos, int newYPos,int boundsLeft, int boundsRight,int stSpeed,
												array<String^,2>^ spriteSheets, array<int>^ spriteCount,int health,
													int baseAttack, int damageModifyer, double defence);
	void calculateSpriteStates();
	void implementSpriteStates();
	void clearList();
	bool isEmpty();
	void deleteSprite(EnemySprite^ spriteToDelete);
	void drawViewPortSprites(Rectangle^ viewRect);
	int spriteHit();
	void spriteAttack();
	void bringOutYourDead();
	bool endGame();
};
