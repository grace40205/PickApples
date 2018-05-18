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
// Custom Data Types
//-----------------------------------------------------------------
typedef WORD        GAMESTATE;
const GAMESTATE  GA_NEW			= 0x0000L, //开始新游戏
				 GA_DIE			= 0x0001L, //游戏失败
				 GA_CONTINUE	= 0x0002L; //上一次游戏

typedef WORD        UISTATE;
const UISTATE  UI_OPTION		= 0x0000L,
			   UI_GAME			= 0x0001L,
			   UI_SETTINGS		= 0x0002L,
			   UI_HELP			= 0x0003L,
			   UI_RANK			= 0x0004L,
			   UI_END			= 0x0005L, //游戏暂停
			   UI_PAUSE         = 0X0006L, //结束界面
			   UI_EXIT			= 0X0007L;

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         g_hInstance;
GameEngine*       g_pGame;
HDC               g_hOffscreenDC;
HBITMAP           g_hOffscreenBitmap;

int               g_iWidth	= 960;
int				  g_iHeight = 540;

Image*            g_pMissileBitmap;
Image*           g_pBlobboBitmap;
Image*           g_pBMissileBitmap;
Image*           g_pJellyBitmap;
Image*           g_pJMissileBitmap;
Image*           g_pTimmyBitmap;
Image*           g_pTMissileBitmap;
Image*           g_pSmExplosionBitmap;
Image*           g_pLgExplosionBitmap;

//游戏开始界面
Image*			g_pOpitonBackgroundImage;
Image*			g_pGameImage;
Image*			g_pSettingsImage;
Image*			g_pHelpImage;
Image*			g_pRankImage;
Image*			g_pExitImage;

//游戏场景
Image*			g_pGameBackgroundImage;
Image*			g_pAppleImage;
Image*			g_pStoneImage;

Image*			g_pGirlImage;
Sprite*         g_pGirlSprite;

Image*			g_pScoreImage;
Image*			g_pPauseImage;
Image*			g_pMusicOnImage;
Image*			g_pMusicOffImage;
Image*			g_pHeartImage;

Image*          g_pGameAlertImage;
Image*          g_pGameAgainImage;
Image*          g_pGameContinueImage;
Image*          g_pGameMainImage;
Image*          g_pCancelImage;

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

Background*		g_pBackground;

//决定绘制哪个界面
UISTATE			g_uiState;
//决定游戏开始模式
GAMESTATE		g_gaState;

int             g_iFireInputDelay;
int             g_iNumLives, g_iScore, g_iDifficulty;
BOOL            g_bGameOver, g_bMusicOn;



//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void NewOption();
void NewGameOver();
void NewGamePause();
void RemoveOption();
bool RemovePause();
void AddFalls();
