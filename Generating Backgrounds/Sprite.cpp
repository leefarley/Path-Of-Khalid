#include "StdAfx.h"
#include "Sprite.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Sprite Constructor
//		This constructor will not be called directly 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sprite::Sprite(Graphics^ stCanvas, Random^ stGen,int stXPos, int stYPos,int boundsLeft, int boundsRight,
			   int stSpeed, array<String^,2>^ stSpriteSheets, array<int>^ stFrameCounts, TTileMap^ stMap)
{
	// sets local pointers to equal the passed in pointers
	canvas = stCanvas;
	rGen = stGen;
	worldMap = stMap;

	// sets the local Position to = the positions passed in.
	xPos = stXPos;
	yPos = stYPos;

	// setup of the bounds
	bounds = gcnew Rectangle(boundsLeft, 0,(boundsRight-boundsLeft),800);

	// will set as RIGHT,LEFT,DOWN,UP
	vDirections = gcnew array<Point> {Point(1,0),Point(-1,0),Point(0,1),Point(0,-1)};


		// set beginning x and y vels to 0 so they will not move in STANDING state
	xVel = 0;
	yVel = 0;
	
	// define how many sprites you have for yor sprite sheet and your counts
	spriteSheets = gcnew array<Bitmap^, 2> (2,stFrameCounts->Length);
	spriteFrameCount = stFrameCounts;

	// will create the Bitmap for both left and right sprite and and set top cnr color to transparent
	// loops through all the different states
	for (int i = 0;i<spriteFrameCount->Length;i++)
	{
		spriteSheets[RIGHT,i] = gcnew Bitmap(stSpriteSheets[RIGHT,i]);
		spriteSheets[RIGHT,i]->MakeTransparent(spriteSheets[RIGHT,i]->GetPixel(0,0));
		spriteSheets[LEFT,i] = gcnew Bitmap(stSpriteSheets[LEFT,i]);
		spriteSheets[LEFT,i]->MakeTransparent(spriteSheets[LEFT,i]->GetPixel(0,0));
	}


		// set sprites starting state to STANDING and all the other data properties that need to be set when changeing state
	spriteState = STANDING;
	spriteDirection = RIGHT;
	fNumber = spriteFrameCount[spriteState];
	fCurrent = 0; // sprite will begin form first position
	fWidth = spriteSheets[spriteDirection,spriteState]->Width / fNumber;
	fHeight = spriteSheets[spriteDirection,spriteState]->Height;
	spritefModifyer=0;
	jumpDesent = false;
	isAttacking = false;
	isAlive = true;
	
	speed = stSpeed;



}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic Draw method that will Draw all sprites.
//		The enemy list should make sure only sprites in the viewport are called.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::draw(Rectangle^ viewRect)
{
		
	int drawX = xPos - viewRect->X; //adjusts the sprites position from relitive to the worldmap to relitive to the viewport
	int drawY = yPos - viewRect->Y;

	if ((spriteState == 5) && (spriteDirection == LEFT))
		drawX -= 70;

	if (spriteState == 9)
		drawY -= 20;
	Bitmap^ spriteToDraw = spriteSheets[spriteDirection,spriteState]; // gets the bitmap to draw to screen
	Rectangle myRect = Rectangle(fWidth*fCurrent,0,fWidth,fHeight);//creates a rect of where in the sprite sheet to draw
	canvas->DrawImage(spriteToDraw,drawX,drawY,myRect,GraphicsUnit::Pixel);// draws to the canvas
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic update Frame.
//		increaments the fcurrent 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::updateFrame()
{
	fCurrent = (fCurrent+1) % spriteFrameCount[spriteState];
}


bool Sprite::checkTileType(int tileType)
{

		Point directCnr;
		switch (spriteDirection)
		{
		case (RIGHT):
			//adds a point to the Right of the new sprite location
			directCnr = Point(xPos + fWidth - TILE_OFFSET, yPos );
			break;
		case (LEFT):
			//adds a point to the left of the new sprite location
			directCnr = Point(xPos + TILE_OFFSET, yPos);
			break;
		}

		//will get the index of the tile that the Point is on
		directCnr.X /= TILE_SIDE;
		directCnr.Y /= TILE_SIDE; 
		
		//checks tiles iswalkable property
		if (worldMap->getTileType(directCnr.Y,directCnr.X) == tileType) 
			return true; // if we can walk left or right check returns true 
	return false;//else if wall is in the way or we are about to go off the screen we will return false
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic FloorCheck method.
//		Will check that sprites next position will not land him inside a walkable tile.
//		if tile is walkable return true else return false
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sprite::floorCheck()
{
	//set new X and Y to = Xpos next position
	int newY = yPos + (yVel * vDirections[DOWN].Y);
	int newX = xPos + (xVel * vDirections[spriteDirection].X);

	int offset = 15;
		Point directCnr;
		switch (spriteDirection){
			case (RIGHT) :
				//adds a point to the right of the new sprite location
				directCnr = Point(newX + offset , newY + fHeight);  
				break;
			case (LEFT):
				//adds a point to the left of the new sprite location
				directCnr = Point(newX + (fWidth - offset), newY + fHeight);
				break;
		}


		// calculate what tile that the point is on
		directCnr.X /= TILE_SIDE;
		directCnr.Y /= TILE_SIDE; 

		if (worldMap->isWalkable(directCnr.Y,directCnr.X)) //checks tiles iswalkable property
		{  
			//yPos = (tempy * TILE_SIDE)-fHeight ; // this will make sure that the char will sit flat on the top of the tile.
			return true;
		}
	return false;//else the function will return false
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic WallCheck method.
//		Will check that sprites next position will not land him inside a walkable tile.
//		if tile is walkable return true else return false
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sprite::wallCheck()
{	
	//caluclates the sprites next X pos

	int newX = xPos + xVel * vDirections[spriteDirection].X;
		Point directCnr;
		switch (spriteDirection)
		{
		case (RIGHT):
			//adds a point to the Right of the new sprite location
			directCnr = Point(newX + (fWidth * 0.5), yPos + (fHeight-20));
			break;
		case (LEFT):
			//adds a point to the left of the new sprite location
			directCnr = Point(newX + (fWidth * 0.5), yPos + (fHeight-20));
			break;
		}

		//will get the index of the tile that the Point is on
		directCnr.X /= TILE_SIDE;
		directCnr.Y /= TILE_SIDE; 
		
		//checks tiles iswalkable property, passes in the Col then the row in.
		if (!worldMap->isWalkable(directCnr.Y,directCnr.X)) 
			return true; // if we can walk left or right check returns true 
	return false;//else if wall is in the way or we are about to go off the screen we will return false
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic boundsCheck method.
//		Will check that sprites next position will not land him outside of his bounds
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sprite::boundsCheck()
{
	//calculate the x and y pos on next draw cycle
	int newX = xPos + xVel * vDirections[spriteDirection].X;
	int newY = yPos + yVel * vDirections[spriteDirection].Y;


	Rectangle temp = Rectangle(newX,newY,fWidth,fHeight); 
	if (bounds->Contains(temp)) // checking if the new pos will put the sprite out of bounds
			return true; // if the whole sprite is in the viewport
	return false;//the sprite is partailly outside of the viewport.
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic Standing method.
//		preforms functions to make the sprite stand
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::standing()
{
	updateFrame();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic Running method.
//		preforms functions to make the sprite run
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::running()
{
	updateFrame();
	xPos += (xVel * vDirections[spriteDirection].X);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic Jumping method.
//		preforms functions to make the sprite run
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::jumping()
{
	//will change frame when spritefModifyer is 0
	if (spritefModifyer == 0)
		updateFrame();

	spritefModifyer++;
	
	//will return spritefModifyer to 0 every 3 game cycles
	spritefModifyer = (spritefModifyer+1) % 3;

	if (yVel < 15)
		yVel += 2;

	// set the sprites new position in the world
	xPos += (xVel * vDirections[spriteDirection].X);
	yPos += (yVel * vDirections[2].Y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic falling method.
//		preforms functions to make the sprite fall
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::falling()
{
	
	updateFrame();

	// if the fall velocity is less than 15 increment.
	if (yVel < 15)
		yVel += 1;

	// set the sprites new position in the world
	xPos += (xVel * vDirections[spriteDirection].X);
	yPos += (yVel * vDirections[2].Y);
}




void Sprite::setSpriteState(int newSpriteState)
{

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		Generic Hit Method.
//		This method will be run when the sprite has been hit. it will modify the hit damage by the sprites defence rating.
//		it will also set the sprite state to HIT to run the animation and dependant on the type of attack will be knocked back. 
//		a check to see if the sprite is dead is also invoked.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sprite::Hit(int damage)
{
	//set new health
	health -= (damage * defence);
	if (health <= 0)
	{
		health = 0;
		if(spriteState != DIE)
			setSpriteState(DIE);
	}
	

	
}

//======================================================================================
//		get Attack area method
//		will return the area on the map that that if intersected will cause damage to other sprites
//======================================================================================
Rectangle^ Sprite::getAttackArea()
{
	Rectangle^ temp ;
	switch (spriteDirection)
	{
		//is the sprite faceing left or right.
	case (RIGHT):
		temp = gcnew Rectangle (xPos + (fWidth /2 ),yPos,fWidth/2,fHeight);
		break;
	case (LEFT):
		temp = gcnew Rectangle (xPos,yPos,fWidth/2,fHeight);
		break;
	}
	return temp;
}

//======================================================================================
//		defend method
//		will return the area on the map that the sprite in theroy is situated
//======================================================================================
bool Sprite::defend(Rectangle^ attackRect)
{

	Rectangle defendRect;
	switch (spriteDirection)
	{
	case (RIGHT):
		defendRect = Rectangle (xPos + (fWidth/2),yPos,fWidth/2,fHeight);
		break;
	case (LEFT):
		defendRect = Rectangle (xPos,yPos,fWidth/2,fHeight);
		break;
	}

	if (attackRect->IntersectsWith(defendRect))
		return true;
	
	return false;

}

//======================================================================================
//		calculate damage method
//		will return the area on the map that the sprite in theroy is situated
//======================================================================================
int Sprite::calculateDamage()
{
	int damage = baseDamage + rGen->Next(damageModifyer);
	return damage;
}

void Sprite::die()
{

	if (fCurrent == fNumber-1)
		isAlive = false;
	else
		updateFrame();
}


//======================================================================================
//		calculate Sprite Placement method
//		will set the yPos of the sprite so it will appear that the sprite is standing the tile
//		no matter the sprite size.
//======================================================================================
void Sprite::spritePlacement()
{
	Point spriteBottom (xPos,yPos + fHeight);

	spriteBottom.X /= TILE_SIDE;
	spriteBottom.Y /= TILE_SIDE;

		if (!worldMap->isWalkable(spriteBottom.Y,spriteBottom.X)) //checks tiles iswalkable property
			++spriteBottom.Y;

		yPos = (spriteBottom.Y * TILE_SIDE)-fHeight ; // this will make sure that the char will sit flat on the top of the tile.
}