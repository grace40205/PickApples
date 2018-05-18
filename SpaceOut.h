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
const GAMESTATE  GA_NEW			= 0x0000L,
				 GA_DIE			= 0x0001L,
				 GA_CONTINUE	= 0x0002L;

typedef WORD        UISTATE;
const UISTATE  UI_OPTION		= 0x0000L,
			   UI_GAME			= 0x0001L,
			   UI_SETTINGS		= 0x0002L,
			   UI_HELP			= 0x0003L,
			   UI_RANK			= 0x0004L,
			   UI_END			= 0x0005L, //��Ϸ��ͣ����������
			   UI_EXIT			= 0X0006L;

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         g_hInstance;
GameEngine*       g_pGame;
HDC               g_hOffscreenDC;
HBITMAP           g_hOffscreenBitmap;

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

//��Ϸ��ʼ����
Image*			g_pOpitonBackgroundImage;
Image*			g_pGameImage;
Sprite*			g_pGameSprite;
Image*			g_pSettingsImage;
Sprite*			g_pSettingsSprite;
Image*			g_pHelpImage;
Sprite*			g_pHelpSprite;
Image*			g_pRankImage;
Sprite*			g_pRankSprite;
Image*			g_pExitImage;
Sprite*			g_pExitSprite;
//��Ϸ����
Image*			g_pGameBackgroundImage;
Image*			g_pAppleImage;
Image*			g_pBombImage;
Image*			g_pPlayerImage;
Sprite*         g_pPlayerSprite;
Image*			g_pPauseImage;
Image*			g_pSoundImage;
//��Ϸ����/��ͣ����
Image*			g_pEndBackgroundImage;
Image*			g_pBackToMainImage;
Image*			g_pContinueImage;
Image*			g_pRestartImage;
//��Ϸ���ý���
Image*			g_pSettingsBackgroundImage;
Image*			g_pBGMImage;
Image*			g_pSoundEffectImage;
Image*			g_pDifficultyImage;
Image*			g_pCheckboxImage;
Image*			g_pTickImage;
//��Ϸ��������
Image*			g_pHelpBackgroundImage;
//��Ϸ���а����
Image*			g_pRankBackgroundImage;

Background*		g_pBackground;

//GamePaint�о��������ĸ�����
UISTATE			g_uiState;
GAMESTATE		g_gaState;

int             g_iFireInputDelay;
int             g_iNumLives, g_iScore, g_iDifficulty;
BOOL            g_bGameOver;

//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void NewOption();
void RemoveOption();
void AddAlien();
