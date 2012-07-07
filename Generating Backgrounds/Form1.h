#pragma once

#include "TViewport.h"
#include "PlayerSprite.h"
#include "SpriteList.h"
#include "pickupList.h"

//this is the size of the playing area of the game window
#define VIEW_WIDTH 800
#define VIEW_HEIGHT 600


namespace GeneratingBackgrounds {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		Graphics^ canvas;
		Graphics^ offScreenCanvas;
		Bitmap^ offScreenBitmap;
		Random^ rGen;
		TViewport^ myMap;
		PlayerSprite^ Khalid;
		SpriteList^ enemyList;
		pickupList^ pickUps;
		int score;

		array<String^>^ SpriteArrayLeft;
		array<String^>^ SpriteArrayRight;
		array<String^,2>^ temp;
		array<int>^ SpriteFrameCounts;

		bool move;
	private: System::Windows::Forms::Timer^  tmrGameTimer;


	private: System::Windows::Forms::Label^  lbHealth;
	private: System::Windows::Forms::Label^  lbScore;
	private: System::Windows::Forms::Label^  lbFeedback;
	private: System::Windows::Forms::Button^  btnPlay;
	private: System::Windows::Forms::Label^  lbButtonDetails;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;



	private: System::ComponentModel::IContainer^  components;








#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
				 this->tmrGameTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->lbHealth = (gcnew System::Windows::Forms::Label());
				 this->lbScore = (gcnew System::Windows::Forms::Label());
				 this->lbFeedback = (gcnew System::Windows::Forms::Label());
				 this->btnPlay = (gcnew System::Windows::Forms::Button());
				 this->lbButtonDetails = (gcnew System::Windows::Forms::Label());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->SuspendLayout();
				 // 
				 // tmrGameTimer
				 // 
				 this->tmrGameTimer->Interval = 70;
				 this->tmrGameTimer->Tick += gcnew System::EventHandler(this, &Form1::tmrChickenDraw_Tick);
				 // 
				 // lbHealth
				 // 
				 this->lbHealth->AutoSize = true;
				 this->lbHealth->BackColor = System::Drawing::Color::Transparent;
				 this->lbHealth->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 40, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->lbHealth->ForeColor = System::Drawing::Color::Black;
				 this->lbHealth->Location = System::Drawing::Point(871, 323);
				 this->lbHealth->Name = L"lbHealth";
				 this->lbHealth->Size = System::Drawing::Size(140, 90);
				 this->lbHealth->TabIndex = 0;
				 this->lbHealth->Text = L"100";
				 // 
				 // lbScore
				 // 
				 this->lbScore->AutoSize = true;
				 this->lbScore->BackColor = System::Drawing::Color::Transparent;
				 this->lbScore->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 40, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->lbScore->ForeColor = System::Drawing::Color::Black;
				 this->lbScore->Location = System::Drawing::Point(871, 151);
				 this->lbScore->Name = L"lbScore";
				 this->lbScore->Size = System::Drawing::Size(72, 90);
				 this->lbScore->TabIndex = 2;
				 this->lbScore->Text = L"0";
				 // 
				 // lbFeedback
				 // 
				 this->lbFeedback->AutoSize = true;
				 this->lbFeedback->BackColor = System::Drawing::Color::Transparent;
				 this->lbFeedback->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 40));
				 this->lbFeedback->Location = System::Drawing::Point(19, 360);
				 this->lbFeedback->MaximumSize = System::Drawing::Size(800, 0);
				 this->lbFeedback->MinimumSize = System::Drawing::Size(800, 0);
				 this->lbFeedback->Name = L"lbFeedback";
				 this->lbFeedback->Size = System::Drawing::Size(800, 90);
				 this->lbFeedback->TabIndex = 3;
				 this->lbFeedback->Visible = false;
				 // 
				 // btnPlay
				 // 
				 this->btnPlay->Location = System::Drawing::Point(894, 650);
				 this->btnPlay->Name = L"btnPlay";
				 this->btnPlay->Size = System::Drawing::Size(88, 34);
				 this->btnPlay->TabIndex = 4;
				 this->btnPlay->Text = L"Play";
				 this->btnPlay->UseVisualStyleBackColor = true;
				 this->btnPlay->Click += gcnew System::EventHandler(this, &Form1::btnPlay_Click);
				 // 
				 // lbButtonDetails
				 // 
				 this->lbButtonDetails->AutoSize = true;
				 this->lbButtonDetails->BackColor = System::Drawing::Color::Transparent;
				 this->lbButtonDetails->Location = System::Drawing::Point(883, 502);
				 this->lbButtonDetails->Name = L"lbButtonDetails";
				 this->lbButtonDetails->Size = System::Drawing::Size(111, 17);
				 this->lbButtonDetails->TabIndex = 5;
				 this->lbButtonDetails->Text = L"Movement: <- ->";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->BackColor = System::Drawing::Color::Transparent;
				 this->label1->Location = System::Drawing::Point(883, 565);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(111, 17);
				 this->label1->TabIndex = 6;
				 this->label1->Text = L"Jump: Spacebar";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->BackColor = System::Drawing::Color::Transparent;
				 this->label2->Location = System::Drawing::Point(893, 534);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(90, 17);
				 this->label2->TabIndex = 7;
				 this->label2->Text = L"Attack: X,Y,Z";
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
				 this->ClientSize = System::Drawing::Size(1023, 768);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->lbButtonDetails);
				 this->Controls->Add(this->btnPlay);
				 this->Controls->Add(this->lbFeedback);
				 this->Controls->Add(this->lbScore);
				 this->Controls->Add(this->lbHealth);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				 this->Name = L"Form1";
				 this->Text = L"Path of Khaild";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Move_Screen);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

				 canvas = CreateGraphics();
				 offScreenBitmap = gcnew Bitmap(800,600);
				 offScreenCanvas = Graphics::FromImage(offScreenBitmap);
				 rGen = gcnew Random();
				
				 //creating the viewport, imports all the images into ram 
				 myMap = gcnew TViewport(0,0,800,600,offScreenCanvas,rGen);
				
				 
				 


			 }

	private: System::Void Move_Screen(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyData == Keys::Left)
				 {
					 if (Khalid->getSpriteState() == STANDING){
						 Khalid->setSpriteState(RUNNING);
					 }
					 // if the key is pressed no matter the state then he will be set to moving
					 Khalid->setXVel(15);
					 Khalid->setSpriteDirection(LEFT);
					 move = true;
				 }
				 else if (e->KeyData == Keys::Right)
				 {
					 if (Khalid->getSpriteState() == STANDING){
						 Khalid->setSpriteState(RUNNING);
					}
					 // if the key is pressed no matter the state then he will be set to moving
					 Khalid->setXVel(15);
					 Khalid->setSpriteDirection(RIGHT);
					 move = true;
				 }
				 if (e->KeyData == Keys::Space){
					 if (Khalid->getSpriteState() != JUMPING)
					 {
						 Khalid->setSpriteState(JUMPING);
						 if(move == true)
							 Khalid->setXVel(10);
					 }
				 }else if(e->KeyData == Keys::Z){
					 if (Khalid->getSpriteState() == STANDING)
					 {
						Khalid->setSpriteState(CHAINATTACK);
					 }
				 }else if(e->KeyData == Keys::C){
					 if (Khalid->getSpriteState() == STANDING)
					 {
						 Khalid->setSpriteState(KICKFACE);
					 }

				 }else if (e->KeyData == Keys::X){
					if (Khalid->getSpriteState() == STANDING)
					 {
						 Khalid->setSpriteState(CHARGE);
					 }
				 }

			 }

	private: System::Void tmrChickenDraw_Tick(System::Object^  sender, System::EventArgs^  e) {
				 pickUps->PickedUp();
				 Khalid->calculateSpriteState();
				 enemyList->calculateSpriteStates();
				 Khalid->implementSpriteState();
				 enemyList->implementSpriteStates();
				 
				
				 if (Khalid->getIsAttacking() == true)
				 {
					 score += enemyList->spriteHit();
					 lbScore->Text = Convert::ToString(score);
				 }
				 else
					 enemyList->spriteAttack();

				 if (Khalid->getSpriteState() != STANDING)
				 {
					 myMap->moveRelativeToPlayer(Khalid->getXPos(),Khalid->getYPos());
				 }
				 lbHealth->Text = Convert::ToString(Khalid->getHealth());
				 //if Khalids is alive bool is false then the game will end
				 if(Khalid->getIsAlive() == false)
				 {
					 tmrGameTimer->Enabled = false;
					 lbFeedback->Text = ("You Died");
					 lbFeedback->Visible = true;
					 btnPlay->Enabled = true;
				 }
					//if killed the boss and move to the gate then the game will finsh
				 if ((enemyList->endGame() == true)&&(Khalid->checkTileType(END_TILE)))
				 {
					 tmrGameTimer->Enabled = false;
					 lbFeedback->Text = ("Congratulations. You Bet the Gatekeeper");
					 lbFeedback->Visible = true;
					 btnPlay->Enabled = true;
				 }
				 pickUps->bringOutYourDead();
				 enemyList->bringOutYourDead();
				 myMap->viewportDraw();
				 pickUps->draw(myMap->getViewRect());
				 enemyList->drawViewPortSprites(myMap->getViewRect());
				 Khalid->draw(myMap->getViewRect());
				 canvas->DrawImage(offScreenBitmap,18,145);
			 }

	private: System::Void Form1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 // if the player is running and releases the key then the state cahnges.
				 if (Khalid->getSpriteState() == RUNNING)
				 {
					 Khalid->setSpriteState(STANDING);
				 }
				 // if the player is moving in a different state and a direction key is released 
				 //then his x vel is decreased to 5 to make the jumping and falling more accurate.
				 if((e->KeyData == Keys::Left)||(e->KeyData == Keys::Right))
				 {
					 move = false;
					 Khalid->setXVel(5);
				 }
				 
			 }

void Form1::setupGame(){
					//setting up the arrays for the main player sprites
				 SpriteArrayRight = gcnew array<String^>{"playerSprites/dieRIGHT.png","playerSprites/idleRIGHT.png",
										"playerSprites/runRIGHT.png","playerSprites/jumpRIGHT.png","playerSprites/jumpRIGHT.png",
												"playerSprites/chainRIGHT.png","playerSprites/kickRIGHT.png","playerSprites/climbRIGHT.png",
										"playerSprites/waitingRIGHT.png","playerSprites/chargeRIGHT.png"};
				 SpriteArrayLeft = gcnew array<String^>{"playerSprites/dieRIGHT.png","playerSprites/idleLEFT.png",
										"playerSprites/runLEFT.png","playerSprites/jumpLEFT.png","playerSprites/jumpLEFT.png",
												"playerSprites/chainLEFT.png","playerSprites/kickLEFT.png","playerSprites/climbLEFT.png",
												"playerSprites/waitingLEFT.png","playerSprites/chargeLEFT.png"};
				 //add the number for each sprite sheet into this array.
				 SpriteFrameCounts = gcnew array<int>{19,7,9,8,8,9,5,7,8,10};
				 
				 //createing a 2 dimentional array of the two arrays of bitmap to pass to the sprite
				 temp = gcnew array<String^, 2> (2,SpriteFrameCounts->Length);

				 for (int i = 0;i<SpriteFrameCounts->Length;i++)
				 {
				 temp[0,i] = SpriteArrayRight[i];
				 temp[1,i] = SpriteArrayLeft[i];
				 }
					
				 //create a instance of the player sprite and make Khalid pointer point to it.
				 Khalid = gcnew PlayerSprite(offScreenCanvas,rGen,300,535,0,6400,12,temp,SpriteFrameCounts,myMap->getWorldMap());


				//use the same pointer for sprite arrays but create new arrays with the enemy sprites
				 SpriteArrayRight = gcnew array<String^>{"zombie/dieRIGHT.png","zombie/idleRIGHT.png",
								"zombie/walkRIGHT.png","zombie/walkRIGHT.png","zombie/attackRIGHT.png"};
				 SpriteArrayLeft = gcnew array<String^>{"zombie/dieLEFT.png","zombie/idleLEFT.png",
								"zombie/walkLEFT.png","zombie/walkLEFT.png","zombie/attackLEFT.png"};
				 SpriteFrameCounts = gcnew array<int>{3,3,8,8,7};
				
				
				 for (int i = 0;i<SpriteFrameCounts->Length;i++)
				 {
					temp[0,i] = SpriteArrayRight[i];
					temp[1,i] = SpriteArrayLeft[i];
				 }

				 //creating a management instace for the enemies
				 enemyList = gcnew SpriteList(offScreenCanvas,rGen, myMap->getWorldMap(),Khalid,myMap);
				 //adding the enemies to the management class and setting there varibles
				 enemyList->addSprite(600,535,300,900,10,temp,SpriteFrameCounts,50,20,10,0.2);
				 enemyList->addSprite(1180,110,1140,1515,7,temp,SpriteFrameCounts,50,20,10,0.2);
				 enemyList->addSprite(1600,520,1430,1925,12,temp,SpriteFrameCounts,50,20,10,0.2);
				 enemyList->addSprite(4100,520,4065,4335,14,temp,SpriteFrameCounts,50,20,10,0.2);
				 enemyList->addSprite(5000,500,4000,6000,5,temp,SpriteFrameCounts,50,20,10,0.2);
				
				 //use the same pointer for sprite arrays but create new arrays with the boss sprites
				 SpriteArrayRight = gcnew array<String^>{"Boss/dieRIGHT.png","Boss/standingRIGHT.png",
								"Boss/standingRIGHT.png","Boss/standingRIGHT.png","Boss/attackRIGHT.png"};
				 SpriteArrayLeft = gcnew array<String^>{"Boss/dieLEFT.png","Boss/standingLEFT.png",
								"Boss/standingLEFT.png","Boss/standingLEFT.png","Boss/attackLEFT.png"};
				 SpriteFrameCounts = gcnew array<int>{8,8,8,8,7};

				 for (int i = 0;i<SpriteFrameCounts->Length;i++)
				 {
					temp[0,i] = SpriteArrayRight[i];
					temp[1,i] = SpriteArrayLeft[i];
				 }
				 //adding the boss to the tail of the enemy sprite list
				 enemyList->addSprite(6030,408,5180,6290,9,temp,SpriteFrameCounts,200,20,10,0.2);
				
				 //createing a management class for objects that do not move, at the moment this is only potions.
				 pickUps = gcnew pickupList(offScreenCanvas,Khalid,myMap);
				 //adding the potions to the map, the constructor takes the sprites x Pos, y Pos and type.
				 pickUps->addItem(300,580,POTION);
				 pickUps->addItem(1350,165,POTION);
				 pickUps->addItem(2290,578,POTION);
				 pickUps->addItem(4855,354,POTION);
				
				 //reset the score
				 score = RESET;
				 lbScore->Text = Convert::ToString(score);
				 lbFeedback->Visible = false;
				 tmrGameTimer->Enabled = true;
			 }


private: System::Void btnPlay_Click(System::Object^  sender, System::EventArgs^  e) {

			 // this will setup all the sprites for the game.
				 setupGame();
				 btnPlay->Enabled = false;
		 }
};

}

