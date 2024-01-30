//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <memory>
//------------------------------------------------------------------------
#include "Physics.h"
#include "SlingShot.h"
#include "Utils.h"
#include "Wall.h"
#include "Mail.h"
#include "MailBox.h"
#include "Block.h"
#include "SlippyBlock.h"
#include "PhysicsBlock.h"
#include "BouncyBlock.h"
#include "StartButton.h"
#include "QuitButton.h"
#include "SpriteManager.h"
#include "KeyBoardInputHandler.h"
#include "UserInterface.h"
//------------------------------------------------------------------------

/*Declaring and Initializing Enum values*/
ObstacleType obstacleType = MAILBOXBLOCK;
State gameState = STARTSTATE;

Vector2 MousePosition;

CSimpleSprite* BackgoundSprite;

/*Creating Keyboard Input Handler Objects*/
KeyBoardInputHandler f1(VK_F1);					//BEGIN GAME FRAME -> CAN ONLY BE CALLED AFTER MAILBOX IS PLACED AND GAMESTATE = LEVELBUILDINGSTATE
KeyBoardInputHandler f2(VK_F2);					//RESET CHARACTER -> CAN ONLY BE CALLED WHEN CHARACTER HAS BEEN PLACED (SLINGSHOT RELEASE BUT NO WALL CONTACT)
KeyBoardInputHandler plus(VK_OEM_PLUS);			//INCREASES SPRITE SIZE -> CAN ONLY BE CALLED IN LEVEL BUILDER AND NOT ON MAILBOX
KeyBoardInputHandler minus(VK_OEM_MINUS);		//DECREASE SPRITE SIZE -> CAN ONLY BE CALLED IN LEVEL BUILDER AND NOT ON MAILBOX
KeyBoardInputHandler middleMouse(VK_MBUTTON);	//ROTATES SPRITE -> CAN ONLY BE CALLED IN LEVEL BUILDER AND NOT ON MAILBOX
KeyBoardInputHandler leftMouse(VK_LBUTTON);		//PRESSES BUTTONS ON START, LOSE AND WIN SCREEN. 
KeyBoardInputHandler rightMouse(VK_RBUTTON);	//HOLD DOWN RIGHT MOUSE TO AIM SLING SHOT -> CAN ONLY BE USED WHILE BIRD IS NOT PLACED

/*constexpr for setting location of the buttons on start, lose and win screen*/
constexpr float LEFT = -1.0f;
constexpr float RIGHT = 1.0f;
constexpr float TOP = 1.0f;
constexpr float BOTTOM = -1.0f;
constexpr float WIDTH = (RIGHT - LEFT);
constexpr float HEIGHT = (TOP - BOTTOM);
Vector2 play = { 0.0f, TOP * 0.5f }, quit = { 0.0f, BOTTOM * 0.5f }, instructions{};

/*Object of physics class -> used to update physics*/
Physics physics;

/*Declaring the player Character (mail)*/
PhysicsEntity* mail;


PhysicsEntity startButton, quitButton, instructionsButton;
PhysicsEntity tempEntity;
PhysicsEntities buttons;
PhysicsEntities entities;

constexpr float maxArea = 3.2f;
float areaOfCurrentBlock, areaLeft;
bool isShooting,isMailBoxPlaced;

//------------------------------------------STATE MACHINE--------------------------------------------------------//
void InitStartScene();
void InitGameScene();
void InitLevelBuilderScene();
void InitLoseScene();
void InitWinScene();

void ExitStartScene();
void ExitGameScene();
void ExitLevelBuilderScene();
void ExitLoseScene();
void ExitWinScene();

void UpdateStartScene(float deltaTime);
void UpdateGameScene(float deltaTime);
void UpdateLevelBuilderScene(float deltaTime);
void UpdateLoseScene(float deltaTime);
void UpdateWinScene(float deltaTime);

void DrawStartScene();
void DrawGameScene();
void DrawLevelBuilderScene();
void DrawLoseScene();
void DrawWinScene();
//------------------------------------------STATE MACHINE--------------------------------------------------------//

void CreateWalls();
void BuildLevelPlayerInput();
void UpdateTempEntityLocation(float deltaTime);
void UpdateEntities(float deltaTime);
void SpawnSprite();
void ChangeSprite();

void Init()
{
	InitStartScene();
}

void Update(float deltaTime)
{	
	switch (gameState)
	{
	case(STARTSTATE):
		UpdateStartScene(deltaTime);
		break;

	case(GAMESTATE):
		UpdateGameScene(deltaTime);
		break;

	case(LEVELBUILDINGSTATE):
		UpdateLevelBuilderScene(deltaTime);
		break;
	
	case(LOSESTATE):
		UpdateLoseScene(deltaTime);
		break;

	case(WINSTATE):
		UpdateWinScene(deltaTime);
		break;

	default:
		break;
	}	

	/*NON STATE SPECIFIC*/
	MousePosition = GetMouseNativeSpace();
	BackgoundSprite->Update(deltaTime);
}

void Render()
{
	BackgoundSprite->Draw();
	switch (gameState)
	{
	case(STARTSTATE):
		DrawStartScene();
		break;

	case(GAMESTATE):
		DrawGameScene();
		break;

	case(LEVELBUILDINGSTATE):
		DrawLevelBuilderScene();	
		break;

	case(LOSESTATE):
		DrawLoseScene();
		break;

	case(WINSTATE):
		DrawWinScene();
		break;
	}	
}

void InitStartScene()
{
	BackgoundSprite = CreateSprite(MAINBACKGROUND);
	BackgoundSprite->SetPosition(400.0f, 400.0f);

	buttons.push_back(startButton = StartButton::CreateStartButton(play, 0.8f, 0));
	buttons.push_back(quitButton = QuitButton::CreateQuitButton(quit, 0.8f, 0));
}
void InitLevelBuilderScene()
{
	entities.reserve(1024);
	CreateWalls();

	isShooting = false;
	isMailBoxPlaced = false;
	areaLeft = 3.0f;
	obstacleType = MAILBOXBLOCK;

	BackgoundSprite = CreateSprite(MAINBACKGROUND);
	BackgoundSprite->SetPosition(400.0f, 400.0f);

	/*Initializing the mail as a reference, This is needed to control the mail location via the slingshot*/
	entities.push_back(Mail::CreateMail({ -0.5f, -0.3f }));
	mail = &entities.back();
	mail->SetIsPlaced(false);
	mail->SetHasWon(false);
	SlingShot::initalPosition = mail->GetPosition();

	/*Setting tempEntity to be basic Block off start*/
	tempEntity = MailBox::CreateMailBox(Vector2Zero, tempEntity.GetMaxSize(), 0);
	tempEntity.SetIsPlaced(false);
}
void InitGameScene()
{

}
void InitLoseScene()
{
	BackgoundSprite = CreateSprite(LOSEBACKGROUND);
	BackgoundSprite->SetPosition(400.0f, 400.0f);

	buttons.push_back(startButton = StartButton::CreateStartButton(play, 0.8f, 0));
	buttons.push_back(quitButton = QuitButton::CreateQuitButton(quit, 0.8f, 0));
}
void InitWinScene()
{
	BackgoundSprite = CreateSprite(WINBACKGROUND);
	BackgoundSprite->SetPosition(400.0f, 400.0f);

	buttons.push_back(startButton = StartButton::CreateStartButton(play, 0.8f, 0));
	buttons.push_back(quitButton = QuitButton::CreateQuitButton(quit, 0.8f, 0));
}

void ExitStartScene()
{
	buttons.clear();
}
void ExitLevelBuilderScene()
{

}
void ExitGameScene()
{
	entities.clear();
	entities.shrink_to_fit();
}
void ExitLoseScene()
{
	buttons.clear();
	buttons.shrink_to_fit();
}
void ExitWinScene()
{
	buttons.clear();
}

void UpdateStartScene(float deltaTime)
{
	for (PhysicsEntity& button : buttons)
		button.GetSprite()->Update(deltaTime);

	for (PhysicsEntity& button : buttons)
	{
		Vector2 position = Vector2Zero;
		position = button.GetPosition();
		APP_NATIVE_TO_VIRTUAL_COORDS(position.x, position.y);
		button.GetSprite()->SetPosition(position.x, position.y);
	}

	/*Checks if overlapping with buttons.*/
	if (leftMouse.OnKeyPressed())
	{
		/*If Mouse is overlapping with Start button, close start scene and open level builder scene.*/
		if (CircleRect(MousePosition, 0.06f, startButton.GetPosition(), startButton.GetCollider().extents, nullptr))
		{
			ExitStartScene();
			InitLevelBuilderScene();
			gameState = LEVELBUILDINGSTATE;
		}
		else if (CircleRect(MousePosition, 0.06f, quitButton.GetPosition(), quitButton.GetCollider().extents, nullptr))
			exit(0);
	}
}
void UpdateGameScene(float deltaTime)
{
	physics.Update(deltaTime / 1000, entities); //Dividing by 1000 as Physics engine expects time in seconds 

	if (f2.OnKeyPressed())
	{
		if(mail->GetIsPlaced())
		mail->ResetPlayer();
	}
	if (!mail->GetIsPlaced())
	{

		if (App::IsKeyPressed(VK_RBUTTON))
		{
			isShooting = true;
			SlingShot::SlingshotSpringPhysics(mail);
		}
		else if (isShooting)
		{
			mail->SetIsPlaced(true);
			mail->SetGravityScale(1.0f);
			mail->SetVelocity(((((SlingShot::displacement * -1.0f) * 30.0f / mail->GetInvMass()))));
			isShooting = false;
		}
	}
	
	UpdateEntities(deltaTime);
}
void UpdateLevelBuilderScene(float deltaTime)
{
	BuildLevelPlayerInput();
	UpdateEntities(deltaTime);
	UpdateTempEntityLocation(deltaTime);
}
void UpdateLoseScene(float deltaTime)
{
	for (PhysicsEntity& button : buttons)
		button.GetSprite()->Update(deltaTime);

	for (PhysicsEntity& button : buttons)
	{
		Vector2 position = Vector2Zero;
		position = button.GetPosition();
		APP_NATIVE_TO_VIRTUAL_COORDS(position.x, position.y);
		button.GetSprite()->SetPosition(position.x, position.y);
	}

	/*Checks if overlapping with buttons.*/
	if (leftMouse.OnKeyPressed())
	{
		/*If Mouse is overlapping with Start button, close start scene and open level builder scene.*/
		if (CircleRect(MousePosition, 0.06f, startButton.GetPosition(), startButton.GetCollider().extents, nullptr))
		{
			App::PlaySound(".\\TestData\\Test.wav");

			ExitLoseScene();
			InitLevelBuilderScene();
			gameState = LEVELBUILDINGSTATE;
		}
		else if (CircleRect(MousePosition, 0.06f, quitButton.GetPosition(), quitButton.GetCollider().extents, nullptr))
			exit(0);
	}
}
void UpdateWinScene(float deltaTime)
{
	for (PhysicsEntity& button : buttons)
		button.GetSprite()->Update(deltaTime);

	for (PhysicsEntity& button : buttons)
	{
		Vector2 position = Vector2Zero;
		position = button.GetPosition();
		APP_NATIVE_TO_VIRTUAL_COORDS(position.x, position.y);
		button.GetSprite()->SetPosition(position.x, position.y);
	}

	/*Checks if overlapping with buttons.*/
	if (leftMouse.OnKeyPressed())
	{
		/*If Mouse is overlapping with Start button, close start scene and open level builder scene.*/
		if (CircleRect(MousePosition, 0.06f, startButton.GetPosition(), startButton.GetCollider().extents, nullptr))
		{
			App::PlaySound(".\\TestData\\Test.wav");

			ExitWinScene();
			InitLevelBuilderScene();
			gameState = LEVELBUILDINGSTATE;
		}
		else if (CircleRect(MousePosition, 0.06f, quitButton.GetPosition(), quitButton.GetCollider().extents, nullptr))
			exit(0);
	}
}

void DrawStartScene()
{
	for (PhysicsEntity& button : buttons)
		button.GetSprite()->Draw();
}
void DrawGameScene()
{
	for (PhysicsEntity& obj : entities)
		obj.GetSprite()->Draw();

	if (isShooting)
		SlingShot::DrawSlingshotTrajectoryLine();

	UserInterface::PrintIntVariableValue(10, 780, "Lives: ", mail->GetLivesLeft());
}
void DrawLevelBuilderScene()
{
	for (PhysicsEntity& obj : entities)
		obj.GetSprite()->Draw();

	tempEntity.GetSprite()->Draw();

	UserInterface::PrintFloatVariableValue(10, 780, "Area Left:", areaLeft);
	UserInterface::PrintFloatVariableValue(600, 780, "CurrentBlockArea:", tempEntity.GetSprite()->GetScale());
}
void DrawLoseScene()
{
	for (PhysicsEntity& button : buttons)
		button.GetSprite()->Draw();
}
void DrawWinScene()
{
	for (PhysicsEntity& button : buttons)
		button.GetSprite()->Draw();
}

void CreateWalls()
{
	entities.push_back(Wall::CreateWall({ 0.0f, 1.0f }, { 0.0f, -1.0f }, 0.0f));	// top
	entities.push_back(Wall::CreateWall({ 0.0f, -1.0f }, { 0.0f, 1.0f }, 0.0f));	// bottom
	entities.push_back(Wall::CreateWall({ -1.0f, 0.0f }, { 1.0f, 0.0f }, 90.0f));	// left
	entities.push_back(Wall::CreateWall({ 1.0f, 0.0f }, { -1.0f, 0.0f }, 90.0f));	// right
}

/*Manages player input during the building face, sprite scale, rotation, type and when to create and push them into the entities vector*/
void BuildLevelPlayerInput()
{
	/*Wrapper so the player cannot input unless the mailbox has been placed -> Non winnable levels made impossible with this*/
	if (isMailBoxPlaced)
	{
		/*Player is done placing blocks -> Swap to gamestate*/
		if (f1.OnKeyPressed())
		{
			gameState = GAMESTATE;
			InitGameScene();
			ExitLevelBuilderScene();
		}

		/*Rotate Sprite*/
		if (middleMouse.OnKeyPressed())
			FlipSprite(tempEntity);

		/*Shrink Sprite using - key*/
		if (minus.OnKeyPressed())
		{
			if (!CheckMinSizeReached(tempEntity, tempEntity.GetMinSize()))
				ShrinkSprite(tempEntity, tempEntity.GetMinSize());
		}

		/*Enlarge Sprite using + key*/
		if (plus.OnKeyPressed())
		{
			if (!CheckMaxSizeReached(tempEntity, tempEntity.GetMaxSize()))
				EnlargeSprite(tempEntity, tempEntity.GetMaxSize());
		}

		/*Cycle Through Available Sprite*/
		if (rightMouse.OnKeyPressed())
			ChangeSprite();
	}

	/*Spawn Sprite*/
	if (leftMouse.OnKeyPressed())
	{
		/*If all area has been used up force the player, place last block at max size within area and force the player into the play scene*/
		if (areaLeft - tempEntity.GetSprite()->GetScale() <= 0)
		{
			tempEntity.GetSprite()->SetScale(areaLeft > tempEntity.GetMinSize() ? areaLeft : tempEntity.GetMinSize());
			SpawnSprite();

			ExitLevelBuilderScene();
			InitGameScene();

			gameState = GAMESTATE;
		}
		else
		{
			areaLeft -= tempEntity.GetSprite()->GetScale();
			SpawnSprite();
		}
	}

	

}

void UpdateEntities(float deltaTime)
{
	for (PhysicsEntity& obj : entities)
	{
		obj.GetSprite()->Update(deltaTime);
		/*if mails lives reaches 0 we open the lose scene*/
		if (obj.GetTag() == MAIL && obj.GetLivesLeft() == 0)
		{
			ExitGameScene();
			InitLoseScene();
			gameState = LOSESTATE;
			break;
		}

		/*if any object hasWon (Happens when mail touches the mailbox) open win scene*/
		if (obj.GetHasWon())
		{
			ExitGameScene();
			InitWinScene();
			gameState = WINSTATE;
			break;
		}
	}

	for (PhysicsEntity& obj : entities)
	{
		Vector2 position;
		position = obj.GetPosition();
		APP_NATIVE_TO_VIRTUAL_COORDS(position.x, position.y);
		obj.GetSprite()->SetPosition(position.x, position.y); // Sprite needs virtual coords for position
	}

}

/*Ties the tempEntity position to the mouse position*/
void UpdateTempEntityLocation(float deltaTime)
{
	Vector2 tempPosition = MousePosition;
	APP_NATIVE_TO_VIRTUAL_COORDS(tempPosition.x, tempPosition.y);
	tempEntity.GetSprite()->SetPosition(tempPosition.x, tempPosition.y); // Sprite needs virtual coords for position

	tempEntity.GetSprite()->Update(deltaTime);
}

/*Pushes tempEntity into entities vector bases on the Create function of the designated obstacleType*/
void SpawnSprite()
{
	switch (obstacleType)
	{
	case(BASICBLOCK):
		entities.push_back(Block::CreateBlock(MousePosition, tempEntity.GetSprite()->GetScale(),
			tempEntity.GetSprite()->GetAngle()));
		break;

	case(MAILBOXBLOCK):
		entities.push_back(MailBox::CreateMailBox(MousePosition, tempEntity.GetSprite()->GetScale(),
			tempEntity.GetSprite()->GetAngle()));

		/*RESET TO BASIC BLOCK AFTER MAILBOX HAS BEEN PLACED*/
		isMailBoxPlaced = true;
		obstacleType = BASICBLOCK;
		tempEntity.GetSprite()->SetScale(0.2f);
		tempEntity.SetSprite(CreateSprite(REGULAR_BLOCK), tempEntity.GetSprite()->GetScale());
		break;

	case(ICEBLOCK):
		entities.push_back(SlippyBlock::CreateSlippyBlock(MousePosition, tempEntity.GetSprite()->GetScale(),
			tempEntity.GetSprite()->GetAngle()));
		break;

	case(BOUNCYBLOCK):
		entities.push_back(BouncyBlock::CreateBouncyBlock(MousePosition, tempEntity.GetSprite()->GetScale(),
			tempEntity.GetSprite()->GetAngle()));
		break;
	case(PHYSICSBLOCK):
		entities.push_back(PhysicsBlock::CreatePhysicsBlock(MousePosition, tempEntity.GetSprite()->GetScale(),
			tempEntity.GetSprite()->GetAngle()));
		break;

	default:
		break;
	}
}

/*Sets the tempEntity sprite* to the next sprite by cycling through available obstacleTypes */
void ChangeSprite()
{
	switch (obstacleType)
	{
	case (BASICBLOCK):
		obstacleType = ICEBLOCK;
		tempEntity.SetSprite(CreateSprite(ICE_BLOCK), tempEntity.GetSprite()->GetScale());
		break;

	case (ICEBLOCK):
		obstacleType = BOUNCYBLOCK;
		tempEntity.SetSprite(CreateSprite(BOUNCY_BLOCK), tempEntity.GetSprite()->GetScale());
		break;

	case (BOUNCYBLOCK):
		obstacleType = PHYSICSBLOCK;
		tempEntity.SetSprite(CreateSprite(PHYSICS_BLOCK), tempEntity.GetSprite()->GetScale());
		break;

	case (PHYSICSBLOCK):
		obstacleType = BASICBLOCK;
		tempEntity.SetSprite(CreateSprite(REGULAR_BLOCK), tempEntity.GetSprite()->GetScale());
		break;

	case (MAILBOXBLOCK):
		obstacleType = BASICBLOCK;
		tempEntity.SetSprite(CreateSprite(REGULAR_BLOCK), tempEntity.GetSprite()->GetScale());
		break;

	default:
		obstacleType = BASICBLOCK;
		tempEntity.SetSprite(CreateSprite(REGULAR_BLOCK), tempEntity.GetSprite()->GetScale());
		break;
	}
}

void Shutdown()
{
	ExitStartScene();
	ExitGameScene();
	ExitLevelBuilderScene();
	ExitWinScene();
	ExitLoseScene();
}



