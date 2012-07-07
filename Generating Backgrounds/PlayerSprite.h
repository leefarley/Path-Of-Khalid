#pragma once
#include "Sprite.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

//define the extended states for the player
#define JUMPING 4
#define CHAINATTACK 5
#define KICKFACE 6
#define CLIMBING 7
#define WAITING 8
#define CHARGE 9
		// this will begin the sprite with a negitive velocity so it will look like he is jumping, the jumping method will increase this
	// value so it will slow down and then fall downward.
#define JUMP_HEIGHT -25
	// sets the yvel of the sprite so it will appear that he is climbing
#define CLIMB_SPEED 7
	// the climb needs to move the sprite to put the new sheet in the correct position to climb because it is not as thick 
	// as the other sprite sheets it will no detect the tile to climb and change state to falling
#define CLIMB_OFFSET 20
	/// this is the index to the tile on the map the the sprite will climb if he intersects with it.
#define CLIMBABLE_TILE1 16
#define CLIMBABLE_TILE2 35
	//this is a tile that is set to transparent so it will act like empty space. 
#define NO_TILE 1
	// this is to calculate if the sprite has been idle for 50 timer cycles.
#define WAIT_TIME 50

	//this is the amount that health is incremented by when there is a collision with a potion
#define POTION_SIZE 30

	//this is the maximum health that the player sprite can achieve
#define HEALTH_MAX 100

	//this is the tile that the player has to intersect with to complete the game.
#define END_TILE 38


ref class PlayerSprite : public Sprite
{
private:
	//this is a count of cycles that the player is standing, when it hits wait time then the state
	//changes to a idle animation and back to standing.
	int waitTime;



public:
	PlayerSprite(Graphics^ stCanvas, Random^ stGen,int xPos, int yPos,int boundsLeft, int boundsRight,int stSpeed,
					array<String^,2>^ stSpriteSheets, array<int>^ stFrameCounts, TTileMap^ stMap);

	void calculateSpriteState (); //will check the enviroment and change the state according to the results
	void implementSpriteState (); // will run the state dependant on the state
	virtual void setSpriteState(int newSpriteState) override; // will change the sprite state and if needed for state other data properties
	virtual void die() override;



	void kickFace(); // these are the extended sprite states for the player.
	void chainAttack();
	void climb();
	void charge();
	Rectangle^ getPickUpArea();
	void addPotion();

};
