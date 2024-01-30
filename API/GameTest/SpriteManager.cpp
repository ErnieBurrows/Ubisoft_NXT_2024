#include "stdafx.h"
#include "SpriteManager.h"

/// <summary>
/// Allows you to instantiate a new sprite based on an ENUM rather then a hard coded file address.
/// You will need to add the sprite into Spritemanager.cpp and Enums.h
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
CSimpleSprite* CreateSprite(SpriteType type)
{
    switch (type)
    {
    case MAINBACKGROUND:
        return App::CreateSprite(".\\TestData\\BackGround.png", 1, 1);
    case LOSEBACKGROUND:
        return App::CreateSprite(".\\TestData\\LoseBackground.png", 1, 1);
    case WINBACKGROUND:
        return App::CreateSprite(".\\TestData\\WinBackground.png", 1, 1);
    case MAIL:
        return App::CreateSprite(".\\TestData\\Mail.png", 1, 1);
    case ICYMAIL:
        return App::CreateSprite(".\\TestData\\IcyMail.png", 1, 1);
    case MAILBOX:
        return App::CreateSprite(".\\TestData\\MailBox.png", 1, 1);
    case ICE_BLOCK:
        return App::CreateSprite(".\\TestData\\IceBlock.png", 1, 1);
    case REGULAR_BLOCK:
        return App::CreateSprite(".\\TestData\\RegularBlock.png", 1, 1);
    case PHYSICS_BLOCK:
        return App::CreateSprite(".\\TestData\\PhysicsBlock.png", 1, 1); 
    case BOUNCY_BLOCK:
        return App::CreateSprite(".\\TestData\\BouncyBlock.png", 1, 1);
    case TELEPORT_BLOCK:
        return App::CreateSprite(".\\TestData\\TeleportBlock.png", 1, 1);
    case WALL:
        return App::CreateSprite(".\\TestData\\Wall.png", 1, 1);
    case STARTBUTTON:
        return App::CreateSprite(".\\TestData\\StartButton.png", 1, 1);
    case QUITBUTTON:
        return App::CreateSprite(".\\TestData\\QuitButton.png", 1, 1);
    default:
        return nullptr;
    }
}