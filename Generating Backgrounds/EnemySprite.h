#pragma once
#include "Sprite.h"
#include "PlayerSprite.h"

// extended states for the enemySprite
//this is a problistic state that can be called from the fight state.
#define ATTACK 4
// this state is when the sprite is in range of the player.
#define FIGHT 5
// the offset is so the sprite does not have to intersect with the player to be able to attack
#define ATTACK_AREA_OFFSET 10
// will use this as the probiblity that the sprite will attack while standing and in attack area.
#define ATTACK_CHANCE 70

ref class EnemySprite : public Sprite
{
private:
	// will check if the sprite is in asent or desent so that the floor check will not hinder his progress when he begins the jump
	bool jumpDesent;
	// has a pointer to the player so the sprite can cheat and check his position relitive to the player.
	PlayerSprite^ player;

public:
	// used in the linked list so we can run through the list and call a common method
	EnemySprite^ next;
	

public:
	EnemySprite(Graphics^ stCanvas, Random^ stGen,int stXPos, int stYPos,int boundsLeft, int boundsRight,int stSpeed,
							array<String^,2>^ stSpriteSheets, array<int>^ stFrameCounts, TTileMap^ stMap, PlayerSprite^ stPlayer,
								int stHealth, int stBaseAtttack, int stDamMod, double stDefence);

	void calculateSpriteState (); //will check the enviroment and change the state according to the results
	void implementSpriteState (); // will run the state dependant on the state
	virtual void setSpriteState(int newSpriteState) override; // will change the sprite state and if needed for state other data properties
	virtual void standing() override;
	bool inAttackArea();
	void fight();
	void attack();
	void approch();
};
