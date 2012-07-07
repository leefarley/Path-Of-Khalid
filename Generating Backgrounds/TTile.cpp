#include "StdAfx.h"
#include "TTile.h"

TTile::TTile(String^ stImage,bool stState)
{
	myImage = gcnew Bitmap(stImage);
	myState = stState;
}

void TTile::setTransparent()
{
	myImage->MakeTransparent(Color::FromArgb(255,0,255));
}
