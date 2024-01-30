#pragma once

enum Shape
{
	CIRCLE,
	PLANE,
	AABB
};

enum SpriteType
{
	MAINBACKGROUND,
	LOSEBACKGROUND,
	WINBACKGROUND,
	REGULAR_BLOCK,
	TELEPORT_BLOCK,
	ICE_BLOCK,
	PHYSICS_BLOCK,
	BOUNCY_BLOCK,
	WALL,
	MAIL,
	ICYMAIL,
	MAILBOX,
	STARTBUTTON,
	QUITBUTTON,
	INVALID
};

enum ObstacleType
{
	BASICBLOCK,
	PHYSICSBLOCK,
	ICEBLOCK,
	MAILBOXBLOCK,
	BOUNCYBLOCK,
	TELEPORTBLOCK,
	NOBLOCK
};

enum State
{
	STARTSTATE,
	LEVELBUILDINGSTATE,
	GAMESTATE,
	WINSTATE,
	LOSESTATE
};

extern State gameState; 
