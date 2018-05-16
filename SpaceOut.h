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
Image*			  g_pSmCarBitmap;
Image*            g_pMissileBitmap;
Image*           g_pBlobboBitmap;
Image*           g_pBMissileBitmap;
Image*           g_pJellyBitmap;
Image*           g_pJMissileBitmap;
Image*           g_pTimmyBitmap;
Image*           g_pTMissileBitmap;
Image*           g_pSmExplosionBitmap;
Image*           g_pLgExplosionBitmap;
Image*           g_pGameOverBitmap;

//游戏开始界面
Image*			g_pOpitonBackgroundImage;
Image*			g_pStartImage;
Image*			g_pSettingsImage;
Image*			g_pHelpImage;
Image*			g_pRankImage;
Image*			g_pExitImage;
//游戏场景
Image*			g_pSkyBackgroundImage;
Image*			g_pAppleImage;
Image*			g_pBombImage;
Image*			g_pPlayerImage;
Image*			g_pPauseImage;
Image*			g_pSoundImage;
//游戏结束/暂停界面
Image*			g_pEndBackgroundImage;
Image*			g_pBackToMainImage;
Image*			g_pContinueImage;
Image*			g_pRestartImage;
//游戏设置界面
Image*			g_pSettingsBackgroundImage;
Image*			g_pBGMImage;
Image*			g_pSoundEffectImage;
Image*			g_pDifficultyImage;
Image*			g_pCheckboxImage;
Image*			g_pTickImage;
//游戏帮助界面
Image*			g_pHelpBackgroundImage;
//游戏排行榜界面
Image*			g_pRankBackgroundImage;








Background*		 g_pBackground;
Sprite*           g_pPlayerSprite;
int               g_iFireInputDelay;
int               g_iNumLives, g_iScore, g_iDifficulty;
BOOL              g_bGameOver;

//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void AddAlien();
