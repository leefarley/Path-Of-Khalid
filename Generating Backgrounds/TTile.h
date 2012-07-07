#pragma once
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

ref class TTile
{
private:
	Bitmap^ myImage; 
	bool myState;
public:
	TTile(String^ stImage,bool stState);
	void setTransparent();
	Bitmap^ getImage ()				{return myImage;}
	bool getMyState()				{return myState;}
	void setMyState(bool newState)	{myState = newState;}
};
