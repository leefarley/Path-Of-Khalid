#include "StdAfx.h"
#include "EnemySprite.h"

EnemySprite::EnemySprite(Graphics^ stCanvas, Random^ stGen,int stXPos, int stYPos,int boundsLeft, int boundsRight,int stSpeed,
						 array<String^,2>^ stSpriteSheets, array<int>^ stFrameCounts, TTileMap^ stMap,PlayerSprite^ stPlayer,
						 int stHealth, int stBaseAtttack, int stDamMod, double stDefence): 
Sprite (stCanvas,stGen,stXPos,stYPos, boundsLeft, boundsRight,stSpeed, stSpriteSheets, stFrameCounts,stMap)
{
	//set the enemys base attack and defence stats
	health = stHealth;
	baseDamage = stBaseAtttack;
	damageModifyer = stDamMod;
	defence = stDefence;
	player = stPlayer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Set Sprite State method.
//		Will change the state varible and any other varible that need to be changed for the state to operate correctly
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySprite::setSpriteState(int newState)
{
	spriteState = newState;
	fNumber = spriteFrameCount [spriteState];
	fCurrent = RESET;
	fWidth = spriteSheets[spriteDirection,spriteState]->Width/fNumber;
	fHeight = spriteSheets[spriteDirection,spriteState]->Height;
	yVel = RESET;
	xVel = RESET;
	spritePlacement();
	switch (spriteState){
		case (RUNNING):
			xVel = speed;
			break;
		case (FALLING):
			yVel = GRAVITY;
			break;
			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Calculate Sprite State method.
//		takes the current sprite state and checks the enviroment, if the enviroment means that the state cannot be used,
//		the sprite state will be changed approprately
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySprite::calculateSpriteState()
{
	switch (spriteState)
	{
	case (STANDING):

		if (floorCheck() == false){
			setSpriteState(FALLING);
		}else if (bounds->Contains(player->getXPos(),player->getYPos())){

			if (inAttackArea() == true)
				fight();
			else
				if (wallCheck() == true)
					setSpriteState(RUNNING);
		}
		break;
	case(RUNNING):
		if (wallCheck() == false)
			setSpriteState(STANDING);
		else if (floorCheck() == false)
			setSpriteState(FALLING);
		else if (inAttackArea() == true)
			setSpriteState(STANDING);
		break;
	case(ATTACK) :
		if (fCurrent == fNumber-1)
			setSpriteState(STANDING);
		break;
	case(FALLING):
		if(checkTileType(LAVA))
			setSpriteState(DIE);
		else if (floorCheck() == true)
			setSpriteState(STANDING);
		 break;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Implement Sprite State method.
//		takes the current sprite state and will call the approprate method for preforming the state
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySprite::implementSpriteState()
{
	switch	(spriteState)
	{
	case (DIE):
		die();
		break;
	case (STANDING):
		standing();
		break;
	case (RUNNING):
		approch();
		break;
	case(FALLING):
		falling();
		break;
	case(ATTACK):
		attack();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		approch player method.
//		will calculate what side that the sprite is on and move toward him. if the player is higher than this sprite 
//		a jump state will be set.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySprite::approch()
{
	//calculate what side of the player you are on
	int xDelta = player->getXPos() - xPos;

	// set sprite direction dependant on your side of the player, xDelta will be negitive if you are to the left of player so direction
	// will become right.
	if (xDelta > 0)
		spriteDirection = RIGHT;
	else
		spriteDirection = LEFT;

	//add the velocities to xpos  depending on the new position
	xPos += (xVel * vDirections[spriteDirection].X);
	yPos += (yVel * vDirections[spriteDirection].Y);
	updateFrame();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		attack method.
//		will run through the sprites attack and check for a collision with the player during the correct frame cycle
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySprite::attack()
{
	updateFrame();
	if (fCurrent == 4)
		isAttacking = true;
}

//======================================================================================
//		fight method
//		will randomly chage state to ATTACK when in the players attack area or stay standing.
//======================================================================================
void EnemySprite::fight()
{
	int attackProb = rGen->Next(100);

	if (attackProb > ATTACK_CHANCE )
		setSpriteState(ATTACK);
}

//======================================================================================
//		in attack area method
//		will check if the sprite is in close proximity of the player.
//======================================================================================
bool EnemySprite::inAttackArea()
{
	//create a retangle arould your position
	Rectangle^ attackArea = gcnew Rectangle(xPos + ATTACK_AREA_OFFSET, yPos, fWidth + ATTACK_AREA_OFFSET, fHeight);
	/// create a rectangle of the players position and size
	Rectangle checkRect = Rectangle(player->getXPos(),player->getYPos(), player->getfWidth(), player->getfHeight());

	// checks if the two rectangles intersect
	if (attackArea->IntersectsWith(checkRect))
		return true;

	return false;
}

//======================================================================================
//		standing method
//		he will update frame and check if he is faceing the player.
//======================================================================================
void EnemySprite::standing()
{
		//calculate what side of the player you are on
	int xDelta = player->getXPos() - xPos;

	// set sprite direction dependant on your side of the player, xDelta will be negitive if you are to the left of player so direction
	// will become right.
	if (xDelta > 0)
		spriteDirection = RIGHT;
	else
		spriteDirection = LEFT;
	updateFrame();
}

