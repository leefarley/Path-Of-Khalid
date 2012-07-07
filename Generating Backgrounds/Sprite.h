#pragma once

#include "TTileMap.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

// this is the only input for the sprite direction varible
#define RIGHT 0
#define LEFT 1
//will be passed in to check methods but never into the spritesheet
#define DOWN 2
#define UP 3

//these define the basic stats that all sprites will have
#define DIE		 0
#define STANDING 1
#define RUNNING  2
#define FALLING  3

//sets the falling speed
#define GRAVITY 10

// this is to calculate the the offset on the tile check.
#define TILE_OFFSET 0.2

//resets the count to 0
#define RESET 0

//used with the check tile method to find if the sprite has fallen into lava
#define LAVA 30



ref class Sprite
{
protected:
	array<Bitmap^,2>^ spriteSheets; // will index the sprites dependat on th sprite direction and state
	array<int>^ spriteFrameCount;
	array<Point>^ vDirections;
	// we will use the world map to check what tiles are walkable
	TTileMap^ worldMap;
	Graphics^ canvas;
	Random^ rGen;
	// ints that will manage the sprites frame values
	int fHeight, fWidth, fCurrent,fNumber, spriteDirection, spriteState;
	// these data properties will manage the sprites position
	int xPos,yPos,xVel, yVel, speed;
	// data properties that manage the sprite damage and health during battle
	int health, baseDamage, damageModifyer; 
	double	defence;
	// the area that the sprite can move around in
	Rectangle^ bounds;

	int spritefModifyer;
	bool jumpDesent;
	bool isAlive;
	bool isAttacking;

public:
	Sprite^ next;


public:
	Sprite(Graphics^ stCanvas, Random^ stGen,int stXPos,int stYPos,int boundsLeft,int boundsRight,
			   int stSpeed, array<String^,2>^ stSpriteSheets, array<int>^ stFrameCounts, TTileMap^ stMap);

	virtual void setSpriteState(int newSpriteState); // will change the sprite state and if needed for state other data properties
	virtual void running(); // these are the common methods that will run when a sprite is in the corrosponding state
	virtual void die();

	void draw(Rectangle^ viewRect);// will draw to screen if within the viewPort
	void updateFrame();
	bool floorCheck(); // will check a point on the bottom of the sprite to see if it is on a walkabble tile
	bool wallCheck(); // will check dependat on the direction if the side of the sprite is able to walk in that direction
	bool boundsCheck(); // will check if the player will walk off the viewport
	int  calculateDamage();// will return an interger from the attacking sprite to plug into defending sprites hit method.
	void Hit(int damage); // will take the damage dealt by an enemy and modify it by defence and decrease health according
	void spritePlacement (); //will calculate the sprites yVel + fHeight to sit on top of the correct tile 
	bool checkTileType(int tileType); //will return true or false if the player intersects with the tile index passed in.

	

	virtual void standing(); //the players own version of standing.
	void falling(); //run on the players falling state
	void jumping(); // run on when in the players jumping state
	bool defend(Rectangle^ attackRect); // this checks if the attacking sprites attack area intersects with your defend area.
	Rectangle^ getAttackArea(); // this returns a retangle with the area that your sprite will damage.

	//Set Methods
	int  getSpriteState()								{return spriteState;}
	int  getXPos()										{return xPos;}
	int  getYPos()										{return yPos;}
	int  getSpriteWidth()								{return fWidth;}
	int  getHealth()									{return health;}
	bool getIsAttacking()								{return isAttacking;}
	bool getIsAlive()									{return isAlive;}
	int  getfWidth()									{return fWidth;}
	int  getfHeight()									{return fHeight;}

	//Get Methods
	void setSpriteDirection	(int newDirection)			{spriteDirection = newDirection;}
	void setXVel(int newXVel)							{xVel = newXVel;}
	void setYVel(int NewYVel)							{yVel = NewYVel;}
	void setAttackState(bool newState)					{isAttacking = newState;}

};
