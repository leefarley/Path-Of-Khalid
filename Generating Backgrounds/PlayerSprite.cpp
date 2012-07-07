#include "StdAfx.h"
#include "PlayerSprite.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Player Sprite Constructor.
//		takes in parameters, passes in parameters into perent constructor to be initilized and intilize all other local varibles
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PlayerSprite::PlayerSprite(Graphics^ stCanvas, Random^ stGen,int stXPos, int stYPos,int boundsLeft, int boundsRight,int stSpeed,
						   array<String^,2>^ stSpriteSheets, array<int>^ stFrameCounts, TTileMap^ stMap): 
Sprite (stCanvas,stGen,stXPos,stYPos,boundsLeft, boundsRight,stSpeed , stSpriteSheets, stFrameCounts, stMap)
{
	// set the players battle stats
	health = 100;
	baseDamage = 55;
	damageModifyer = 10;
	defence = 0.2;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Set Sprite State method.
//		Preforms operations to the data properties so that the new state will be operate correctly
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerSprite::setSpriteState(int newState)
{
 	spriteState = newState;
	fCurrent = RESET;
	fNumber = spriteFrameCount [spriteState];
	fWidth = spriteSheets[spriteDirection,spriteState]->Width/fNumber;
	fHeight = spriteSheets[spriteDirection,spriteState]->Height;
	yVel = RESET;
	xVel = RESET;
	waitTime = RESET;
	switch (spriteState){
		case (RUNNING):
			xVel = speed;
			spritePlacement();
			break;
		case (FALLING):
			yVel = GRAVITY;
			break;
		case (JUMPING):
			yVel = JUMP_HEIGHT;
			spritefModifyer = RESET;
			jumpDesent = false;
			break;
		case (CLIMBING):
			if (spriteDirection == RIGHT)
				xPos += CLIMB_OFFSET;
			yVel = CLIMB_SPEED;
			break;
		default:
			spritePlacement();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Calculate Sprite State method.
//		takes the current sprite state and checks the enviroment, if the enviroment means that the state cannot be used,
//		the sprite state will be changed approprately
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void PlayerSprite::calculateSpriteState()
{
	switch (spriteState)
	{
	case(STANDING):
		if (floorCheck() == false)
		{
			setSpriteState(FALLING);
		}else if (waitTime == WAIT_TIME)
		{
			setSpriteState(WAITING);
		}
		++waitTime;
		break;
	case(RUNNING):
		// if there is a wall next to the sprite then he will be set to standing.
		if (wallCheck() == false)
		{
			if ((checkTileType(CLIMBABLE_TILE1) == true)||(checkTileType(CLIMBABLE_TILE2) == true))
				setSpriteState(CLIMBING);
			else
				setSpriteState(STANDING);

			//if the player is not stoped by a wall, check he is not going off his bounds.
		}else if (boundsCheck() == false)
			setSpriteState(STANDING);
		// if there is not a walkable surface under player he will fall.
		if (floorCheck() == false)
		{
			setSpriteState(FALLING);
		}

		break;
	case (JUMPING):
		//is the player in desent and is he about to land
	if ((jumpDesent == true)&&(floorCheck() == true))
		{
			setSpriteState(STANDING);
		}
	//is there a wall in his way
		if ((wallCheck() == false)||(boundsCheck() == false))
			xVel = RESET;
		//am i in lava?
		else if(checkTileType(LAVA))
			setSpriteState(DIE);

		//have i reached the top arc of my jump
		if (yVel >= 0)
			jumpDesent = true;
		break;
	case(FALLING):
			//is there a wall in his way or am i going to go off the edge of the map
		if ((wallCheck() == false)||(boundsCheck() == false))
			xVel = RESET;
		else if(checkTileType(LAVA))
			setSpriteState(DIE);
		//if im not in lava is there a floor under my feet?
		else if (floorCheck() == true)
			setSpriteState(STANDING);
		break;
	case(CLIMBING):
		// checks if a there is a transperent tile to side of 
		if (checkTileType(NO_TILE) == true)
			setSpriteState(JUMPING);
		break;
	case (DIE):
		//once the die animation has played out set me to dead.
		if (fCurrent == fNumber-1)
		{
			isAlive = false;
		}
		break;
	default:
		//for all other sprites set my state to standing once the animation has played out.
		if (fCurrent == fNumber-1)
		{
			setSpriteState(STANDING);
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Implement Sprite State method.
//		takes the current sprite state and will call the approprate method for preforming the state
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerSprite::implementSpriteState()
{
	switch	(spriteState)
	{
	case (STANDING):
		standing();
		break;
	case (RUNNING):
		running();
		break;
	case (JUMPING):
		jumping();
		break;
	case(FALLING):
		falling();
		break;
	case(CHAINATTACK):
		chainAttack();
		break;
	case(KICKFACE):
		kickFace();
		break;
	case (CLIMBING):
		climb();
		break;
	case (WAITING):
		updateFrame();
		break;
	case (CHARGE):
		charge();
		break;
	case (DIE):
		die();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Kickface attack method.
//		Runs through the sprites frames, will ckeck for a collision when the correct frame is shown if collided
//		the sprite that is collided with will have his hit method called, and have the damage done passed with it
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerSprite::kickFace()
{
	updateFrame();
	//on the thrid frame sprite collision will be checked.
	if (fCurrent == 3)
		isAttacking = true;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		chain attack method.
//		Runs through the sprites frames, will ckeck for a collision when the correct 2 frames are shown, if collided
//		the sprite that is collided with will have his hit method called, and have the damage done passed with it
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerSprite::chainAttack()
{
	updateFrame();
	//on the two frame of the attack sprite that should damage sprite collision is done.
	if ((fCurrent == 3)||(fCurrent == 7))
		isAttacking = true;

}

void PlayerSprite::die()
{
	updateFrame();
}

void PlayerSprite::climb()
{
	//move the sprite up to look like he is climbing
	yPos += yVel * vDirections[UP].Y;
	updateFrame();
}

void PlayerSprite::charge()
{
	//if a direction key is pressed after the attack has begun then the sprite will move in that direction.
	xPos += xVel * vDirections[spriteDirection].X;
	updateFrame();
	//sprite collision ditection occurs between frames 4 to 6.
	if ((fCurrent >= 4)&&(fCurrent <= 6))
		isAttacking = true;

	
}

Rectangle^ PlayerSprite::getPickUpArea()
{
	//if the pickup item intersects with this rectangle then it will be piicked up.
	Rectangle^ temp = gcnew Rectangle(xPos-10,yPos,fWidth-10,fHeight);
	return temp;
}

void PlayerSprite::addPotion()
{
	//add 30 to the health count
	health += POTION_SIZE;
	//do not let health exceed its maximum.
	if (health > HEALTH_MAX)
		health = HEALTH_MAX;
}