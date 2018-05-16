//-----------------------------------------------------------------
// Space Out Application
// C++ Header - SpaceOut.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Image.h"
#include "Sprite.h"
#include "Background.h"
#include "AlienSprite.h"

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         g_hInstance;
GameEngine*       g_pGame;
HDC               g_hOffscreenDC;
HBITMAP           g_hOffscreenBitmap;
Image*			  g_pDesertBitmap;
Image*           g_pCarBitmap;
Image*           g_pSmCarBitmap;
Image*           g_pMissileBitmap;
Image*           g_pBlobboBitmap;
Image*           g_pBMissileBitmap;
Image*           g_pJellyBitmap;
Image*           g_pJMissileBitmap;
Image*           g_pTimmyBitmap;
Image*           g_pTMissileBitmap;
Image*           g_pSmExplosionBitmap;
Image*           g_pLgExplosionBitmap;
Image*           g_pGameOverBitmap;
StarryBackground* g_pBackground;
Sprite*           g_pCarSprite;
int               g_iFireInputDelay;
int               g_iNumLives, g_iScore, g_iDifficulty;
BOOL              g_bGameOver;

//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void AddAlien();
