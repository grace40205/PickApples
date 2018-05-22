//-----------------------------------------------------------------
// Space Out Application
// C++ Source - SpaceOut.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpaceOut.h"

Sprite* pEasySprite;
Sprite* pNormalSprite;
Sprite* pDifficultSprite;
//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
  // Create the game engine
  g_pGame = new GameEngine(hInstance, TEXT("接苹果"),
    TEXT("接苹果"), IDI_SPACEOUT, IDI_SPACEOUT_SM, g_iWidth, g_iHeight);
  if (g_pGame == NULL)
    return FALSE;

  // Set the frame rate
  g_pGame->SetFrameRate(30);

  // Store the instance handle
  g_hInstance = hInstance;

  return TRUE;
}

void GameStart(HWND hWindow)
{
  // Seed the random number generator
  srand(GetTickCount());

  // Create the offscreen device context and bitmap
  g_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  g_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
    g_pGame->GetWidth(), g_pGame->GetHeight());
  SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);

  // Create and load the images
  HDC hDC = GetDC(hWindow);

  g_pGirlImage = new Image(hDC, TEXT("Res\\game_girl.png"));

  g_pOpitonBackgroundImage = new Image(hDC, TEXT("Res\\main_bg.png"));
  g_pGameBackgroundImage = new Image(hDC, TEXT("Res\\game_bg.png"));

  //g_pSettingsBackgroundImage = new Image(hDC, TEXT("Res\\settings_alert.png"));
  //g_pHelpBackgroundImage = new Image(hDC, TEXT("Res\\help_alert.png"));
  //g_pRankBackgroundImage = new Image(hDC, TEXT("Res\\ranking_list_alert.png"));

  
  // 默认情况下进入游戏选择界面
  g_uiState = UI_OPTION;

  // 这里应该读取xml文件获得开始游戏的模式：新游戏，上一个游戏
  g_gaState = GA_NEW;

  // Create the Game Option UI background
  g_pBackground = new Background(g_pOpitonBackgroundImage);

  // 默认情况下音乐开启
  g_bMusicOn = true;
  g_bBGMOn = true;
  g_bSoundOn = true;

  // Play the background music
  if (g_bMusicOn == true||g_bBGMOn == true)
	g_pGame->PlayMIDISong(TEXT("Res\\Music.mid"));

  NewOption();
}

void NewOption() {
	// Clear the sprites
	g_pGame->CleanupSprites();

	// Obtain a device context for repainting the game
	HWND  hWindow = g_pGame->GetWindow();
	HDC   hDC = GetDC(hWindow);

	Sprite* pSprite;

	if (g_pGameImage == NULL || g_pSettingsImage == NULL || g_pHelpImage == NULL ||
		g_pRankImage == NULL || g_pExitImage == NULL|| g_pContinueImage == NULL)
	{
		g_pGameImage = new Image(hDC, TEXT("Res\\main_btn_start.png"));
		g_pSettingsImage = new Image(hDC, TEXT("Res\\main_btn_setting.png"));
		g_pHelpImage = new Image(hDC, TEXT("Res\\main_btn_help.png"));
		g_pRankImage = new Image(hDC, TEXT("Res\\main_btn_ranking_list.png"));
		g_pExitImage = new Image(hDC, TEXT("Res\\main_btn_exit.png"));
		g_pContinueImage = new Image(hDC, TEXT("Res\\main_btn_continue.png"));

	}

	pSprite = new Sprite(g_pGameImage);
	pSprite->SetPosition(650, 40);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pContinueImage);
	pSprite->SetPosition(650, 120);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pSettingsImage);
	pSprite->SetPosition(650, 200);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pHelpImage);
	pSprite->SetPosition(650, 280);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pRankImage);
	pSprite->SetPosition(650, 360);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pExitImage);
	pSprite->SetPosition(650, 440);
	g_pGame->AddSprite(pSprite);

	
}
void NewSetting() {
	// Clear the sprites
	g_pGame->CleanupSprites();

	if (g_pCancelImage == NULL|| g_pSettingsBackgroundImage == NULL|| g_pBGMOnImage == NULL ||
		g_pBGMOffImage == NULL || g_pSoundOnImage == NULL ||
		g_pSoundOffImage == NULL || g_pEasyOnImage == NULL || g_pNormalOnImage == NULL ||
		g_pDifficultOnImage == NULL|| g_pEasyOffImage == NULL || g_pNormalOffImage == NULL ||
		g_pDifficultOffImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);
		g_pSettingsBackgroundImage = new Image(hDC, TEXT("Res\\settings_alert.png"));
		g_pCancelImage = new Image(hDC, TEXT("Res\\cancel.png"));
		g_pBGMOnImage = new Image(hDC, TEXT("Res\\settings_box_on.png"));
		g_pBGMOffImage = new Image(hDC, TEXT("Res\\settings_box_off.png"));
		g_pSoundOnImage = new Image(hDC, TEXT("Res\\settings_box_on.png"));
		g_pSoundOffImage = new Image(hDC, TEXT("Res\\settings_box_off.png"));
		g_pEasyOnImage = new Image(hDC, TEXT("Res\\setting_easy_on.png"));
		g_pNormalOnImage = new Image(hDC, TEXT("Res\\setting_normal_on.png"));
		g_pDifficultOnImage = new Image(hDC, TEXT("Res\\setting_hard_on.png"));
		g_pEasyOffImage = new Image(hDC, TEXT("Res\\setting_easy_off.png"));
		g_pNormalOffImage = new Image(hDC, TEXT("Res\\setting_normal_off.png"));
		g_pDifficultOffImage = new Image(hDC, TEXT("Res\\setting_hard_off.png"));
	}

	Sprite* pSprite;

	pSprite = new Sprite(g_pSettingsBackgroundImage);
	pSprite->SetPosition(g_iWidth * 0.5 - 0.5 * g_pSettingsBackgroundImage->GetWidth(), g_iHeight * 0.5 - 0.5 * g_pSettingsBackgroundImage->GetHeight());
	g_pGame->AddSprite(pSprite);

	RECT position = pSprite->GetPosition();

	pSprite = new Sprite(g_pCancelImage);
	pSprite->SetPosition((int)(position.right - 0.1 * (position.right - position.left)), (int)(position.top + 0.05 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);

	if(g_bBGMOn == true)
		pSprite = new Sprite(g_pBGMOnImage);
	else
		pSprite = new Sprite(g_pBGMOffImage);
	pSprite->SetPosition(475,165);
	g_pGame->AddSprite(pSprite);

	if (g_bSoundOn == true)
		pSprite = new Sprite(g_pSoundOnImage);
	else
		pSprite = new Sprite(g_pSoundOffImage);
	pSprite->SetPosition(475, 245);
	g_pGame->AddSprite(pSprite);


	switch (g_sDifficulty)
	{
	case 1:
		pEasySprite = new Sprite(g_pEasyOnImage);
		pEasySprite->SetPosition(475, 325);
		g_pGame->AddSprite(pEasySprite);

		pNormalSprite = new Sprite(g_pNormalOffImage);
		pNormalSprite->SetPosition(545, 325);
		g_pGame->AddSprite(pNormalSprite);

		pDifficultSprite = new Sprite(g_pDifficultOffImage);
		pDifficultSprite->SetPosition(615, 325);
		g_pGame->AddSprite(pDifficultSprite);
		break;
	case 2:
		pEasySprite = new Sprite(g_pEasyOffImage);
		pEasySprite->SetPosition(475, 325);
		g_pGame->AddSprite(pEasySprite);

		pNormalSprite = new Sprite(g_pNormalOnImage);
		pNormalSprite->SetPosition(545, 325);
		g_pGame->AddSprite(pNormalSprite);

		pDifficultSprite = new Sprite(g_pDifficultOffImage);
		pDifficultSprite->SetPosition(615, 325);
		g_pGame->AddSprite(pDifficultSprite);
		break;
	default:
		pEasySprite = new Sprite(g_pEasyOffImage);
		pEasySprite->SetPosition(475, 325);
		g_pGame->AddSprite(pEasySprite);

		pNormalSprite = new Sprite(g_pNormalOffImage);
		pNormalSprite->SetPosition(545, 325);
		g_pGame->AddSprite(pNormalSprite);

		pDifficultSprite = new Sprite(g_pDifficultOnImage);
		pDifficultSprite->SetPosition(615, 325);
		g_pGame->AddSprite(pDifficultSprite);
		break;
	}

/*
	pEasySprite = new Sprite(g_pEasyOffImage);
	pEasySprite->SetPosition(475, 325);
	g_pGame->AddSprite(pEasySprite);

	pNormalSprite = new Sprite(g_pNormalOnImage);
	pNormalSprite->SetPosition(545, 325);
	g_pGame->AddSprite(pNormalSprite);

	pDifficultSprite = new Sprite(g_pDifficultOffImage);
	pDifficultSprite->SetPosition(615, 325);
	g_pGame->AddSprite(pDifficultSprite)*/;


}
void NewRank() {
	// Clear the sprites
	g_pGame->CleanupSprites();

	if (g_pCancelImage == NULL || g_pRankBackgroundImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);
		g_pRankBackgroundImage = new Image(hDC, TEXT("Res\\ranking_list_alert.png"));
		g_pCancelImage = new Image(hDC, TEXT("Res\\cancel.png"));
	}

	Sprite* pSprite;

	pSprite = new Sprite(g_pRankBackgroundImage);
	pSprite->SetPosition(g_iWidth * 0.5 - 0.5 * g_pRankBackgroundImage->GetWidth(), g_iHeight * 0.5 - 0.5 * g_pRankBackgroundImage->GetHeight());
	g_pGame->AddSprite(pSprite);

	RECT position = pSprite->GetPosition();

	pSprite = new Sprite(g_pCancelImage);
	pSprite->SetPosition((int)(position.right - 0.1 * (position.right - position.left)), (int)(position.top + 0.05 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
}
void NewHelp() {
	// Clear the sprites
	g_pGame->CleanupSprites();

	if (g_pCancelImage == NULL || g_pHelpBackgroundImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);
		g_pHelpBackgroundImage = new Image(hDC, TEXT("Res\\help_alert.png"));
		g_pCancelImage = new Image(hDC, TEXT("Res\\cancel.png"));
	}

	Sprite* pSprite;

	pSprite = new Sprite(g_pHelpBackgroundImage);
	pSprite->SetPosition(g_iWidth * 0.5 - 0.5 * g_pHelpBackgroundImage->GetWidth(), g_iHeight * 0.5 - 0.5 * g_pHelpBackgroundImage->GetHeight());
	g_pGame->AddSprite(pSprite);

	RECT position = pSprite->GetPosition();

	pSprite = new Sprite(g_pCancelImage);
	pSprite->SetPosition((int)(position.right - 0.1 * (position.right - position.left)), (int)(position.top + 0.05 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
}
void NewContinue() {
	// Clear the sprites
	g_pGame->CleanupSprites();
		
	
	if (g_pCancelImage == NULL || g_pContinueHintImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);
		g_pContinueHintImage = new Image(hDC, TEXT("Res\\continue_null.png"));
		g_pCancelImage = new Image(hDC, TEXT("Res\\cancel.png"));
	}

	Sprite* pSprite;

	pSprite = new Sprite(g_pContinueHintImage);
	pSprite->SetPosition(g_iWidth * 0.5 - 0.5 * g_pContinueHintImage->GetWidth(), g_iHeight * 0.5 - 0.5 * g_pContinueHintImage->GetHeight());
	g_pGame->AddSprite(pSprite);

	RECT position = pSprite->GetPosition();

	pSprite = new Sprite(g_pCancelImage);
	pSprite->SetPosition((int)(position.right - 0.1 * (position.right - position.left)), (int)(position.top + 0.05 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
}

void NewGameOver()
{
	// Clear the sprites
	g_pGame->CleanupSprites();

	if (g_pGameAlertImage == NULL || g_pGameAgainImage == NULL ||
		g_pGameMainImage == NULL || g_pCancelImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		g_pGameAlertImage = new Image(hDC, TEXT("Res\\puase_alert.png"));
		g_pGameAgainImage = new Image(hDC, TEXT("Res\\puase_again.png"));
		g_pGameMainImage = new Image(hDC, TEXT("Res\\puase_main.png"));
		g_pCancelImage = new Image(hDC, TEXT("Res\\cancel.png"));
	}

	Sprite* pSprite;
	
	pSprite = new Sprite(g_pGameAlertImage);
	pSprite->SetPosition(g_iWidth * 0.5 - 0.5 * g_pGameAlertImage->GetWidth(), g_iHeight * 0.5 - 0.5 * g_pGameAlertImage->GetHeight());
	g_pGame->AddSprite(pSprite);
	
	RECT position = pSprite->GetPosition();

	pSprite = new Sprite(g_pGameAgainImage);
	pSprite->SetPosition((int)(position.left + 0.1 * (position.right - position.left)), (int)(position.bottom - 0.35 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
	
	pSprite = new Sprite(g_pGameMainImage);
	pSprite->SetPosition((int)(position.left + 0.75 * (position.right - position.left)), (int)(position.bottom - 0.35 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
	
	pSprite = new Sprite(g_pCancelImage);
	pSprite->SetPosition((int)(position.right - 0.1 * (position.right - position.left)), (int)(position.top + 0.05 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
}


void NewGamePause()
{
	if (g_pGameAlertImage == NULL || g_pGameAgainImage == NULL ||
		g_pGameMainImage == NULL || g_pCancelImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		g_pGameAlertImage = new Image(hDC, TEXT("Res\\puase_alert.png"));
		g_pGameAgainImage = new Image(hDC, TEXT("Res\\puase_again.png"));
		g_pGameMainImage = new Image(hDC, TEXT("Res\\puase_main.png"));
		g_pCancelImage = new Image(hDC, TEXT("Res\\cancel.png"));
	}

	if (g_pGameContinueImage == NULL)
	{
		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		g_pGameContinueImage = new Image(hDC, TEXT("Res\\puase_continue.png"));
	}

	Sprite* pSprite;

	pSprite = new Sprite(g_pGameAlertImage);
	pSprite->SetPosition(g_iWidth * 0.5 - 0.5 * g_pGameAlertImage->GetWidth(), g_iHeight * 0.5 - 0.5 * g_pGameAlertImage->GetHeight());
	g_pGame->AddSprite(pSprite);

	RECT position = pSprite->GetPosition();

	pSprite = new Sprite(g_pGameAgainImage);
	pSprite->SetPosition((int)(position.left + 0.1 * (position.right - position.left)), (int)(position.bottom - 0.35 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pGameContinueImage);
	pSprite->SetPosition((int)(position.left + 0.43 * (position.right - position.left)), (int)(position.bottom - 0.35 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
	
	pSprite = new Sprite(g_pGameMainImage);
	pSprite->SetPosition((int)(position.left + 0.75 * (position.right - position.left)), (int)(position.bottom - 0.35 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pCancelImage);
	pSprite->SetPosition((int)(position.right - 0.1 * (position.right - position.left)), (int)(position.top + 0.05 * (position.bottom - position.top)));
	g_pGame->AddSprite(pSprite);
}

void RemoveOption()
{
	// Cleanup the sprites
	g_pGame->CleanupSprites();
}

bool RemovePause()
{
	if ( g_pGame->CleanupSprite(g_pGameAlertImage) &&
		g_pGame->CleanupSprite(g_pGameAgainImage) &&
		g_pGame->CleanupSprite(g_pGameMainImage) &&
		g_pGame->CleanupSprite(g_pGameContinueImage) &&
		g_pGame->CleanupSprite(g_pCancelImage))
	{
		return true;
	}
	return false;
}

void GameEnd()
{
  // Close the MIDI player for the background music
  g_pGame->CloseMIDIPlayer();

  // Cleanup the offscreen device context and bitmap
  DeleteObject(g_hOffscreenBitmap);
  DeleteDC(g_hOffscreenDC);  

  // Cleanup the images
  // 游戏开始界面
  delete			g_pOpitonBackgroundImage;
  delete			g_pGameImage;
  delete			g_pSettingsImage;
  delete			g_pHelpImage;
  delete			g_pRankImage;
  delete			g_pExitImage;

  // 游戏场景
  delete			g_pGameBackgroundImage;
  delete			g_pAppleImage;
  delete			g_pStoneImage;

  delete			g_pGirlImage;

  delete			g_pScoreImage;
  delete			g_pPauseImage;
  delete			g_pMusicOnImage;
  delete			g_pMusicOffImage;
  delete			g_pHeartImage;

  delete			g_pGameAlertImage;
  delete			g_pGameAgainImage;
  delete			g_pGameContinueImage;
  delete			g_pGameMainImage;
  delete			g_pCancelImage;

  // 游戏设置界面
  delete			g_pSettingsBackgroundImage;
  delete			g_pBGMOnImage;
  delete			g_pBGMOffImage;
  delete			g_pSoundOnImage;
  delete			g_pSoundOffImage;
  delete			g_pEasyOnImage;
  delete			g_pNormalOnImage;
  delete			g_pDifficultOnImage;
  delete			g_pEasyOffImage;
  delete			g_pNormalOffImage;
  delete			g_pDifficultOffImage;
  // 游戏帮助界面
  delete			g_pHelpBackgroundImage;
  // 游戏排行榜界面
  delete			g_pRankBackgroundImage;

  // Cleanup the background
  delete g_pBackground;

  // Cleanup the sprites
  g_pGame->CleanupSprites();

  // Cleanup the game engine
  delete g_pGame;
}

void GameActivate(HWND hWindow)
{
  // Resume the background music
  if (g_bMusicOn == true||g_bBGMOn == true)
	  g_pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
  // Pause the background music
  g_pGame->PauseMIDISong();
}
void DrawString(const HDC &hDC, RECT& rect, LONG32 height, LONG32 width, string str)
{
	LOGFONT lonfont;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lonfont);
	/*lonfont.lfHeight = 48;
	lonfont.lfWidth = 37;*/
	lonfont.lfHeight = height;
	lonfont.lfWidth = width;
	lonfont.lfCharSet = GB2312_CHARSET;//国标2312  
	wsprintf(lonfont.lfFaceName, TEXT("%s"), TEXT("黑体"));
	HFONT hfont = CreateFontIndirect(&lonfont);

	TCHAR szText[64];
	wsprintf(szText, "%s", str);

	SelectObject(hDC, hfont);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(26, 26, 26));
	DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteObject(hfont);
}

void DrawNumber(const HDC &hDC,RECT& rect, LONG32 height, LONG32 width, int number)
{
	LOGFONT lonfont;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lonfont);
	/*lonfont.lfHeight = 48;
	lonfont.lfWidth = 37;*/
	lonfont.lfHeight = height;
	lonfont.lfWidth = width;
	lonfont.lfCharSet = GB2312_CHARSET;//国标2312  
	wsprintf(lonfont.lfFaceName, TEXT("%s"), TEXT("黑体"));
	HFONT hfont = CreateFontIndirect(&lonfont);

	TCHAR szText[64];
	wsprintf(szText, "%d", number);

	SelectObject(hDC, hfont);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(26, 26, 26));
	DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteObject(hfont);
}

void DrawNumber1(const HDC &hDC, RECT& rect, LONG32 height, LONG32 width, int number)
{
	LOGFONT lonfont;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lonfont);
	/*lonfont.lfHeight = 48;
	lonfont.lfWidth = 37;*/
	lonfont.lfHeight = height;
	lonfont.lfWidth = width;
	lonfont.lfCharSet = GB2312_CHARSET;//国标2312  
	wsprintf(lonfont.lfFaceName, TEXT("%s"), TEXT("黑体"));
	HFONT hfont = CreateFontIndirect(&lonfont);

	TCHAR szText[64];
	wsprintf(szText, "%d", number);

	SelectObject(hDC, hfont);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(26, 26, 26));
	DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteObject(hfont);
}

void GamePaint(HDC hDC)
{
	//必须自己管理动态生成的资源
	delete g_pBackground;

	//根据g_uiState的值决定绘制哪个界面
	if (g_uiState == UI_OPTION)
	{
		g_pBackground = new Background(g_pOpitonBackgroundImage);
		g_pBackground->Draw(hDC);

		// Draw the sprites
		g_pGame->DrawSprites(hDC);
	}
	else if (g_uiState == UI_GAME)
	{
		// Draw the background
		g_pBackground = new Background(g_pGameBackgroundImage);
		g_pBackground->Draw(hDC);

		// Draw the sprites
		g_pGame->DrawSprites(hDC);

		// Draw the score
		RECT  rect = { (int)(g_iWidth * 0.1) , (int)(g_iHeight * 0.0), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		DrawNumber(hDC,rect,48,37,g_iScore);

		// Draw the number of remaining lives (cars)
		for (int i = 0; i < g_iNumLives; i++)
			g_pHeartImage->Draw(hDC, 520 + (g_pHeartImage->GetWidth() * i),
				10);
	}
	else if (g_uiState == UI_SETTINGS)
	{
		g_pBackground = new Background(g_pOpitonBackgroundImage);
		g_pBackground->Draw(hDC);
		g_pGame->DrawSprites(hDC);
	}
	else if (g_uiState == UI_HELP)
	{
		g_pBackground = new Background(g_pOpitonBackgroundImage);
		g_pBackground->Draw(hDC);
		g_pGame->DrawSprites(hDC);
	}
	else if (g_uiState == UI_RANK)
	{
		g_pBackground = new Background(g_pOpitonBackgroundImage);
		g_pBackground->Draw(hDC);
		g_pGame->DrawSprites(hDC);

		//从BestRecord.xml里获取三个难度的数据
		string BestScore_easy_str = getdata(BEST_RECORD_XMLPATH, "best_easy");
		char bestscore_easy_char[20];
		strcpy(bestscore_easy_char, BestScore_easy_str.c_str());
		int BestScore_easy = atoi(bestscore_easy_char);

		string BestScore_medium_str = getdata(BEST_RECORD_XMLPATH, "best_medium");
		char bestscore_medium_char[20];
		strcpy(bestscore_medium_char, BestScore_medium_str.c_str());
		int BestScore_medium = atoi(bestscore_medium_char);

		string BestScore_hard_str = getdata(BEST_RECORD_XMLPATH, "best_hard");
		char bestscore_hard_char[20];
		strcpy(bestscore_hard_char, BestScore_hard_str.c_str());
		int BestScore_hard = atoi(bestscore_hard_char);


		/*string last_score_str = getdata(LATEST_RECORD_XMLPATH, "score");
		char last_score_char[20];
		strcpy(last_score_char, last_score_str.c_str());
		int last_score_num = atoi(last_score_char);
		g_iScore = last_score_num;*/


	/*	string BestScore_medium = getdata(BEST_RECORD_XMLPATH, "best_medium");
		string BestScore_hard = getdata(BEST_RECORD_XMLPATH, "best_hard");*/

		//在排行榜上绘制（显示）数据
		RECT  rect1 = { (int)(g_iWidth * 0.85) , (int)(g_iHeight * 0.84), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		DrawNumber(hDC, rect1, 48, 37, BestScore_easy);

		RECT  rect2 = { (int)(g_iWidth * 0.85) , (int)(g_iHeight * 1.08), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		DrawNumber(hDC, rect2, 48, 37, BestScore_medium);

		RECT  rect3 = { (int)(g_iWidth * 0.85) , (int)(g_iHeight * 1.32), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		DrawNumber(hDC, rect3, 48, 37, BestScore_hard);

		//RECT  rect4 = { (int)(g_iWidth * 0.1) , (int)(g_iHeight * 0.0), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		//DrawString(hDC, rect4, 48, 37, BestScore_easy);

		//RECT  rect5 = { (int)(g_iWidth * 0.1) , (int)(g_iHeight * 0.0), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		//DrawString(hDC, rect5, 48, 37, BestScore_medium);

		//RECT  rect6 = { (int)(g_iWidth * 0.1) , (int)(g_iHeight * 0.0), (int)(g_iWidth * 0.2), (int)(g_iHeight * 0.1) };
		//DrawString(hDC, rect6, 48, 37, BestScore_hard);
	}

	else if (g_uiState == UI_END || g_uiState == UI_PAUSE)
	{
		g_pBackground = new Background(g_pGameBackgroundImage);
		g_pBackground->Draw(hDC);

		// Draw the sprites
		g_pGame->DrawSprites(hDC);

		
		RECT  rect = { (int)(g_iWidth * 0.4) , (int)(g_iHeight * 0.38), (int)(g_iWidth * 0.6), (int)(g_iHeight * 0.5) };
		DrawNumber(hDC, rect, 48, 37, g_iScore);
	}
	else if (g_uiState == UI_CONTINUE) {
		g_pBackground = new Background(g_pGameBackgroundImage);
		g_pBackground->Draw(hDC);
		g_pGame->DrawSprites(hDC);
	}
}

void GameCycle()
{
  if (g_uiState == UI_OPTION) {
	  //需要更新的话

  }
  else if (g_uiState == UI_GAME && !g_bGameOver)
  {
    // Randomly add aliens
    if ((rand() % g_iDifficulty) < 20)
      AddFalls();

    // Update the background
    g_pBackground->Update();

    // Update the sprites
    g_pGame->UpdateSprites();
  }
  else if (g_uiState == UI_SETTINGS) {
	 //需要更新的话

  }
  else if (g_uiState == UI_HELP) {
	 //需要更新的话
	 
  }
  else if (g_uiState == UI_RANK) {
	 //需要更新的话
	  
  }
  else if (g_uiState == UI_END) {
	  NewGameOver();
  }
  else if (g_uiState == UI_PAUSE) {
	  
  }

  // Obtain a device context for repainting the game
  HWND  hWindow = g_pGame->GetWindow();
  HDC   hDC = GetDC(hWindow);

  // Paint the game to the offscreen device context
  GamePaint(g_hOffscreenDC);

  // Blit the offscreen bitmap to the game screen
  BitBlt(hDC, 0, 0, g_pGame->GetWidth(), g_pGame->GetHeight(),
	  g_hOffscreenDC, 0, 0, SRCCOPY);

  // Cleanup
  ReleaseDC(hWindow, hDC);
}

void HandleKeys()
{
  
  if (g_uiState == UI_GAME && !g_bGameOver)
  {
    // Move the girl based upon left/right key presses
    POINT ptVelocity = g_pGirlSprite->GetVelocity();
    if (GetAsyncKeyState(VK_LEFT) < 0)
    {
      // Move left
      ptVelocity.x = max(ptVelocity.x - 1, -4);
      g_pGirlSprite->SetVelocity(ptVelocity);
    }
	else if (GetAsyncKeyState(VK_RIGHT) < 0)
	{
		// Move right
		ptVelocity.x = min(ptVelocity.x + 2, 6);
		g_pGirlSprite->SetVelocity(ptVelocity);
	}
  }

  // Start a new game based upon an Enter (Return) key press
  if (g_bGameOver && (GetAsyncKeyState(VK_RETURN) < 0))
    // Start a new game
    NewGame();
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
	if (g_uiState == UI_OPTION && bLeft) {
		//确定点击的是哪个图标
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			//此处添加点击图标的音效			
			PlayMouseClickSound();
			if (pSprite->GetImage() == g_pGameImage) {
				g_uiState = UI_GAME;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源(除背景图片外)
				NewGame();
			}
			else if (pSprite->GetImage() == g_pSettingsImage) {
				PlayMouseClickSound();
				g_uiState = UI_SETTINGS;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源
				NewSetting();
				

			}
			else if (pSprite->GetImage() == g_pHelpImage) {
				PlayMouseClickSound();
				g_uiState = UI_HELP;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源
				NewHelp();

			}
			else if (pSprite->GetImage() == g_pRankImage) {
				PlayMouseClickSound();
				g_uiState = UI_RANK;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源
				NewRank();
			}
			else if (pSprite->GetImage() == g_pExitImage) {
				PlayMouseClickSound();
				g_uiState = UI_EXIT;
				
				//由开始界面退出程序 清理开始界面的五个按钮的资源
				RemoveOption();

				g_pGame->Quit();
			}
			else if (pSprite->GetImage() == g_pContinueImage) {
				PlayMouseClickSound();
				//——————————————————-读取保存文档的xml中的	g_gaState的值

				//有记录时，开始游戏
				if (getdata(LATEST_RECORD_XMLPATH, "difficulty")!="0")
				{	
					//设置相关资源
					NewGame();

					//读取上次游戏数据
					//string转int
					string last_score_str = getdata(LATEST_RECORD_XMLPATH, "score");
					char last_score_char[20];
					strcpy(last_score_char, last_score_str.c_str());
					int last_score_num = atoi(last_score_char);
					g_iScore = last_score_num;

					string last_diff_str = getdata(LATEST_RECORD_XMLPATH, "difficulty");
					char last_diff_char[20];
					strcpy(last_diff_char, last_diff_str.c_str());
					int last_diff_num = atoi(last_diff_char);
					g_sDifficulty = last_diff_num;

					string last_lives_str = getdata(LATEST_RECORD_XMLPATH, "lives");
					char last_lives_char[20];
					strcpy(last_lives_char, last_lives_str.c_str());
					int last_lives_num = atoi(last_lives_char);
					g_iNumLives = last_lives_num;

					//进入游戏
					g_uiState = UI_GAME;

				}
				//没有记录时，提示暂无记录
				else {
					g_uiState = UI_CONTINUE;
					
					//跳转界面 需先清理开始界面的五个按钮的资源
					RemoveOption();
					//加载新界面需要的资源
					NewContinue();
				}
			}
			else
				return;
		}
	}	
	else if (g_uiState == UI_RANK && bLeft) {
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pCancelImage) {
				PlayMouseClickSound();
				// 红叉
				g_uiState = UI_OPTION;

				NewOption();
			}
		}
	}
	else if (g_uiState == UI_CONTINUE && bLeft) {
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {

			if (pSprite->GetImage() == g_pCancelImage) {
				PlayMouseClickSound();
				// 红叉
				g_uiState = UI_OPTION;

				NewOption();
			}
		}
	}
	else if(g_uiState == UI_SETTINGS && bLeft){
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pCancelImage) {
				PlayMouseClickSound();
				// 红叉
				g_uiState = UI_OPTION;

				NewOption();
			}
			else if (pSprite->GetImage() == g_pBGMOnImage) {
				PlayMouseClickSound();
				g_bBGMOn = false;
				g_bMusicOn = false;

				pSprite->SetImage(g_pBGMOffImage);

				// Close the MIDI player for the background music
				g_pGame->PauseMIDISong();
			}
			else if (pSprite->GetImage() == g_pBGMOffImage) {
				PlayMouseClickSound();
				g_bBGMOn = true;
				g_bMusicOn = true;

				pSprite->SetImage(g_pBGMOnImage);

				// Open the MIDI player for the background music
				g_pGame->PlayMIDISong();
			}
			else if (pSprite->GetImage() == g_pSoundOnImage) {
				PlayMouseClickSound();
				g_bSoundOn = false;
				g_bMusicOn = false;

				pSprite->SetImage(g_pSoundOffImage);

			}
			else if (pSprite->GetImage() == g_pSoundOffImage) {
				PlayMouseClickSound();
				g_bSoundOn = true;
				g_bMusicOn = true;

				pSprite->SetImage(g_pSoundOnImage);
			}
			else if (pSprite->GetImage() == g_pEasyOffImage) {
				PlayMouseClickSound();
				pSprite->SetImage(g_pEasyOnImage);
				pNormalSprite->SetImage(g_pNormalOffImage);
				pDifficultSprite->SetImage(g_pDifficultOffImage);
				g_sDifficulty = 1;
			}
			else if (pSprite->GetImage() == g_pNormalOffImage) {
				PlayMouseClickSound();
				pSprite->SetImage(g_pNormalOnImage);
				pEasySprite->SetImage(g_pEasyOffImage);
				pDifficultSprite->SetImage(g_pDifficultOffImage);
				g_sDifficulty = 2;
			}
			else if (pSprite->GetImage() == g_pDifficultOffImage) {
				PlayMouseClickSound();
				pSprite->SetImage(g_pDifficultOnImage);
				pNormalSprite->SetImage(g_pNormalOffImage);
				pEasySprite->SetImage(g_pEasyOffImage);
				g_sDifficulty = 3;
			}
		}
	}
	else if (g_uiState == UI_HELP && bLeft) {
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pCancelImage) {
				PlayMouseClickSound();
				// 红叉
				g_uiState = UI_OPTION;

				NewOption();
			}
		}
	}
	else if (g_uiState == UI_GAME && bLeft) {
		//确定点击的是哪个图标
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pMusicOnImage) {
				PlayMouseClickSound();
				g_bMusicOn = false;
				g_bBGMOn = false;
				g_bSoundOn = false;

				// 更换图片
				pSprite->SetImage(g_pMusicOffImage);

				// Close the MIDI player for the background music
				g_pGame->PauseMIDISong();
			}
			else if (pSprite->GetImage() == g_pMusicOffImage) {
				PlayMouseClickSound();
				g_bMusicOn = true;
				g_bBGMOn = true;
				g_bSoundOn = true;

				// 更换图片
				pSprite->SetImage(g_pMusicOnImage);

				// Open the MIDI player for the background music
				g_pGame->PlayMIDISong();
			}
			else if (pSprite->GetImage() == g_pPauseImage) {
				PlayMouseClickSound();
				// 暂停界面
				g_uiState = UI_PAUSE;

				NewGamePause();
			}
		}
	}
	else if (g_uiState == UI_END && bLeft) {
		//确定点击的是哪个图标
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pGameAgainImage) {
				PlayMouseClickSound();
				// 重新开始
				g_uiState = UI_GAME;
				g_gaState = GA_NEW;

				NewGame();
			}
			else if (pSprite->GetImage() == g_pGameMainImage) {
				PlayMouseClickSound();
				// 主页
				g_uiState = UI_OPTION;
				
				NewOption();
			}
			else if (pSprite->GetImage() == g_pCancelImage) {
				PlayMouseClickSound();
				// 红叉
				g_uiState = UI_OPTION;
				
				NewOption();
			}
		}
	}
	else if (g_uiState == UI_PAUSE && bLeft) {
		//确定点击的是哪个图标
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pGameAgainImage) {
				PlayMouseClickSound();
				// 重新开始
				g_uiState = UI_GAME;
				g_gaState = GA_NEW;

				NewGame();
			}
			else if (pSprite->GetImage() == g_pGameContinueImage) {
				PlayMouseClickSound();
				// 继续
				g_uiState = UI_GAME;
				g_gaState = GA_CONTINUE;

				// 清除暂停界面的几个sprite
				if(!RemovePause())
					NewOption();
			}
			else if (pSprite->GetImage() == g_pGameMainImage) {
				PlayMouseClickSound();
				// 返回主页
				g_uiState = UI_OPTION;
				
				//存档到Latest_Record.xml中，保存最近一次记录
				//int转换为char*
				char *num_score= (char*)malloc(100 * sizeof(char));
				itoa(g_iScore, num_score, 10);
				char *num_diff= (char*)malloc(100 * sizeof(char));
				itoa(g_sDifficulty, num_diff, 10);
				char *num_lives = (char*)malloc(100 * sizeof(char));
				itoa(g_iNumLives, num_lives, 10);
		
				Modify(LATEST_RECORD_XMLPATH, "score", num_score);
				Modify(LATEST_RECORD_XMLPATH, "difficulty", num_diff);
				Modify(LATEST_RECORD_XMLPATH, "lives", num_lives);
			
				NewOption();
			}
			else if (pSprite->GetImage() == g_pCancelImage) {
				PlayMouseClickSound();
				// 红叉
				g_uiState = UI_GAME;
				g_gaState = GA_CONTINUE;

				// 清除暂停界面的几个sprite
				if(!RemovePause())
					NewOption();
			}
		}
	}
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{
}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
  Image* pHitter = pSpriteHitter->GetImage();
  Image* pHittee = pSpriteHittee->GetImage();
  
  // See if the girl and an apple have collided
  if (pHitter == g_pGirlImage && pHittee == g_pAppleImage)
  {
    // Play the small explosion sound
	if(g_bMusicOn == true||g_bSoundOn == true)
		PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC |
			SND_RESOURCE);

    // Kill apple sprite
	pSpriteHittee->Kill();

    // Update the score
    g_iScore += 1;
    g_iDifficulty = max(80 - (g_iScore / 20), 20);
  }

  // See if a stone has collided with the girl
  if (pHitter == g_pGirlImage && pHittee == g_pStoneImage)
  {
    // Play the large explosion sound
	if (g_bMusicOn == true || g_bSoundOn == true)
		PlaySound((LPCSTR)IDW_SMEXPLODE, g_hInstance, SND_ASYNC |
			SND_RESOURCE);

    // Kill the stone sprite
	pSpriteHittee->Kill();

    // Move the girl back to the start
    g_pGirlSprite->SetPosition((int)g_iWidth * 0.3, (int)(g_iHeight - g_pGirlImage->GetHeight()));

    // See if the game is over
    if (--g_iNumLives == 0)
    {
		//重置lastRecord记录为0
		Modify(LATEST_RECORD_XMLPATH, "score", "0");
		Modify(LATEST_RECORD_XMLPATH, "difficulty", "0");
		Modify(LATEST_RECORD_XMLPATH, "lives", "0");

		//比较最高得分，存档
		//string转int
		string score_easy_str = getdata(BEST_RECORD_XMLPATH, "best_easy");
		char score_easy_char[20];
		strcpy(score_easy_char, score_easy_str.c_str());
		int score_easy_num = atoi(score_easy_char);

		string score_medium_str = getdata(BEST_RECORD_XMLPATH, "best_medium");
		char score_medium_char[20];
		strcpy(score_medium_char, score_medium_str.c_str());
		int score_medium_num = atoi(score_medium_char);
		
		string score_hard_str = getdata(BEST_RECORD_XMLPATH, "best_hard");
		char score_hard_char[20];
		strcpy(score_hard_char, score_hard_str.c_str());
		int score_hard_num = atoi(score_hard_char);

		char *score = (char*)malloc(100 * sizeof(char));
		itoa(g_iScore, score, 10);

		switch(g_sDifficulty) {
			case 1:
				if(g_iScore>score_easy_num){
					Modify(BEST_RECORD_XMLPATH, "best_easy", score);
				}
				break;
			case 2:
				if (g_iScore > score_medium_num) {
					Modify(BEST_RECORD_XMLPATH, "best_medium", score);
				}
				break;
			case 3:
				if (g_iScore > score_hard_num) {
					Modify(BEST_RECORD_XMLPATH, "best_hard", score);
				}
				break;
			default:
				Modify(BEST_RECORD_XMLPATH, "best_easy", "0");
				Modify(BEST_RECORD_XMLPATH, "best_medium", "0");
				Modify(BEST_RECORD_XMLPATH, "best_hard", "0");
				break;
		}

      // Play the game over sound
	  if (g_bMusicOn == true || g_bSoundOn == true)
		PlaySound((LPCSTR)IDW_GAMEOVER, g_hInstance, SND_ASYNC |
			SND_RESOURCE);
      g_bGameOver = TRUE;
	  g_uiState = UI_END;
	  g_gaState = GA_DIE;


    }
  }

  return FALSE;
}

void SpriteDying(Sprite* pSpriteDying)
{
  // See if an apple sprite is dying
  if (pSpriteDying->GetImage() == g_pAppleImage)
  {
    // Play sound
	if (g_bMusicOn == true || g_bSoundOn == true)
		PlaySound((LPCSTR)IDW_MISSILE, g_hInstance, SND_ASYNC |
			SND_RESOURCE | SND_NOSTOP);
  }
  // See if a stone prite is dying
  else if (pSpriteDying->GetImage() == g_pStoneImage)
  {
	  // Play sound
	  if (g_bMusicOn == true|| g_bSoundOn == true)
		  PlaySound((LPCSTR)IDW_MISSILE, g_hInstance, SND_ASYNC |
			  SND_RESOURCE | SND_NOSTOP);
  }
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
  g_gaState = GA_NEW;

  // Clear the sprites
  g_pGame->CleanupSprites();

  // 加载苹果 石头的图片资源
  if (g_pAppleImage == NULL || g_pStoneImage == NULL)
  {
	  // Obtain a device context for repainting the game
	  HWND  hWindow = g_pGame->GetWindow();
	  HDC   hDC = GetDC(hWindow);

	  g_pAppleImage = new Image(hDC, TEXT("Res\\game_apple.png"));
	  g_pStoneImage = new Image(hDC, TEXT("Res\\game_stone.png"));
  }

  // 加载分数 生命 暂停 音乐 的图片资源
  if (g_pScoreImage == NULL || g_pPauseImage == NULL ||
	  g_pMusicOnImage == NULL || g_pMusicOffImage == NULL ||
	  g_pHeartImage == NULL)
  {
	  // Obtain a device context for repainting the game
	  HWND  hWindow = g_pGame->GetWindow();
	  HDC   hDC = GetDC(hWindow);

	  g_pScoreImage = new Image(hDC, TEXT("Res\\game_socre.png"));
	  g_pPauseImage = new Image(hDC, TEXT("Res\\game_pause.png"));
	  g_pMusicOnImage = new Image(hDC, TEXT("Res\\game_music_on.png"));
	  g_pMusicOffImage = new Image(hDC, TEXT("Res\\game_music_off.png"));
	  g_pHeartImage = new Image(hDC, TEXT("Res\\game_heart.png"));	  
  }

  // 添加分数 暂停 音乐Sprite
  Sprite* pScoreSprite = new Sprite(g_pScoreImage);
  pScoreSprite->SetPosition(0, 0);
  g_pGame->AddSprite(pScoreSprite);

  Sprite* pPauseSprite = new Sprite(g_pPauseImage);
  pPauseSprite->SetPosition((int)(g_iWidth - 3 * g_pPauseImage->GetWidth() - 20), 10);
  g_pGame->AddSprite(pPauseSprite);

  Sprite* pMusicSprite;
  if (g_bMusicOn == true|| g_bBGMOn == true)
	  pMusicSprite = new Sprite(g_pMusicOnImage);
  else
	  pMusicSprite = new Sprite(g_pMusicOffImage);
  pMusicSprite->SetPosition((int)(g_iWidth - 1.5 * g_pMusicOnImage->GetWidth() - 10), 10);
  g_pGame->AddSprite(pMusicSprite);

  // Create the girl sprite
  RECT rcBounds = { 0, 0, g_iWidth, g_iHeight };
  g_pGirlSprite = new Sprite(g_pGirlImage, rcBounds, BA_BOUNCE);
  g_pGirlSprite->SetPosition((int)g_iWidth * 0.3, (int)(g_iHeight - g_pGirlImage->GetHeight()));
  g_pGame->AddSprite(g_pGirlSprite);

  // Initialize the game variables
  g_iFireInputDelay = 0;
  g_iScore = 0;
  g_iNumLives = 3;

  switch (g_sDifficulty)
  {
  case 1:
	  g_iDifficulty = 300;
	  break;
  case 2:
	  g_iDifficulty = 170;
	  break;
  default:
	  g_iDifficulty = 20;
	  break;
  }

  g_bGameOver = FALSE;

  // Play the background music
  if (g_bMusicOn == true||g_bBGMOn == true)
	g_pGame->PlayMIDISong();
}

void AddFalls()
{
  // Create a new random alien sprite
  RECT          rcBounds = { 0, 0, g_iWidth, g_iHeight };
  Sprite*  pSprite = NULL;
  switch(rand() % 5)
  {
  case 0:
    // Apple
    pSprite = new Sprite(g_pAppleImage, rcBounds, BA_DISAPPEAR);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % g_iWidth, rand() % 10);
    pSprite->SetVelocity(0, (rand() % 5) + 3);
	pSprite->SetDieDelay(20);
	pSprite->SetCollidable(TRUE);
    break;
  case 1:
  case 2:
  case 3:
	break;
  case 4:
    // Stone
    pSprite = new Sprite(g_pStoneImage, rcBounds, BA_DISAPPEAR);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % g_iWidth, rand() % 10);
    pSprite->SetVelocity(0, (rand() % 5) + 5);
	pSprite->SetDieDelay(0);
	pSprite->SetCollidable(TRUE);
    break;
  }

  // Add the sprite
  if(pSprite != NULL)
	g_pGame->AddSprite(pSprite);
}

void PlayMouseClickSound() {
	if (g_bMusicOn == true || g_bSoundOn == true)
	PlaySound((LPCSTR)IDW_CLICK, g_hInstance, SND_ASYNC |
		SND_RESOURCE | SND_NOSTOP);
}

//通过根节点和节点名获取节点指针。
//param pRootEle   xml文件的根节点。
//param strNodeName  要查询的节点名
//param Node      需要查询的节点指针
//return 是否找到。true为找到相应节点指针，false表示没有找到相应节点指针。
bool GetNodePointerByName(TiXmlElement *pRootEle, const std::string& strNodeName, TiXmlElement* &Node)
{
	if (strNodeName == pRootEle->Value()) {
		Node = pRootEle;
		return true;
	}

	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {
		if (GetNodePointerByName(pEle, strNodeName, Node))
			return true;
	}
	return false;
}

//修改xml数据
//param XmlFile 
//param strNodeName
//param strText
bool Modify(const char *XmlFile, const std::string strNodeName, const char* strText)
{
	TiXmlDocument *pDoc = new TiXmlDocument();
	if (NULL == pDoc)
	{
		return false;
	}
	pDoc->LoadFile(XmlFile, TIXML_ENCODING_UTF8);
	TiXmlElement *pRootEle = pDoc->RootElement();
	if (NULL == pRootEle) {
		return false;
	}

	TiXmlElement *pNode = NULL;
	GetNodePointerByName(pRootEle, strNodeName, pNode);

	if (NULL != pNode) {
		pNode->Clear();
		TiXmlText *pValue = new TiXmlText(strText);
		pNode->LinkEndChild(pValue);
		pDoc->SaveFile(XmlFile);
		return true;
	}
	else {
		return false;
	}
}

string getdata(const char *XmlFile, const std::string strNodeName) {
	TiXmlDocument *pDoc = new TiXmlDocument();
	if (NULL == pDoc)
	{
		return false;
	}
	pDoc->LoadFile(XmlFile, TIXML_ENCODING_UTF8);
	TiXmlElement *pRootEle = pDoc->RootElement();
	if (NULL == pRootEle) {
		return false;
	}
	TiXmlElement *pNode = NULL;
	GetNodePointerByName(pRootEle, strNodeName, pNode);
	if (NULL != pNode) {
//		printf(pNode->FirstChild.GetText());
		return pNode->GetText();
		//return pNode->FirstChild.GetText();
	}
}

