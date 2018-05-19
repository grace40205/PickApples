//-----------------------------------------------------------------
// Space Out Application
// C++ Source - SpaceOut.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpaceOut.h"

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
  // Create the game engine
  g_pGame = new GameEngine(hInstance, TEXT("Space Out"),
    TEXT("Space Out"), IDI_SPACEOUT, IDI_SPACEOUT_SM, g_iWidth, g_iHeight);
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
  g_pSettingsBackgroundImage = new Image(hDC, TEXT("Res\\settings_alert.png"));
  g_pHelpBackgroundImage = new Image(hDC, TEXT("Res\\help_alert.png"));
  g_pRankBackgroundImage = new Image(hDC, TEXT("Res\\ranking_list_alert.png"));

  
  // 默认情况下进入游戏选择界面
  g_uiState = UI_OPTION;

  // 这里应该读取xml文件获得开始游戏的模式：新游戏，上一个游戏
  g_gaState = GA_NEW;

  // Create the Game Option UI background
  g_pBackground = new Background(g_pOpitonBackgroundImage);

  // 默认情况下音乐开启
  g_bMusicOn = true;

  // Play the background music
  if (g_bMusicOn == true)
	g_pGame->PlayMIDISong(TEXT("Music.mid"));

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
		g_pRankImage == NULL || g_pExitImage == NULL)
	{
		g_pGameImage = new Image(hDC, TEXT("Res\\Game.jpg"));
		g_pSettingsImage = new Image(hDC, TEXT("Res\\Settings.jpg"));
		g_pHelpImage = new Image(hDC, TEXT("Res\\Help.jpg"));
		g_pRankImage = new Image(hDC, TEXT("Res\\Rank.jpg"));
		g_pExitImage = new Image(hDC, TEXT("Res\\Exit.jpg"));
	}

	pSprite = new Sprite(g_pGameImage);
	pSprite->SetPosition(200, 100);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pSettingsImage);
	pSprite->SetPosition(200, 140);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pHelpImage);
	pSprite->SetPosition(200, 180);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pRankImage);
	pSprite->SetPosition(200, 220);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pExitImage);
	pSprite->SetPosition(200, 260);
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
  delete			g_pBGMImage;
  delete			g_pSoundEffectImage;
  delete			g_pDifficultyImage;
  delete			g_pCheckboxImage;
  delete			g_pTickImage;
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
  if (g_bMusicOn == true)
	  g_pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
  // Pause the background music
  g_pGame->PauseMIDISong();
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
		TCHAR szText[64];
		RECT  rect = { 430, 0, 460, 30 };
		wsprintf(szText, "%d", g_iScore);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		// Draw the number of remaining lives (cars)
		for (int i = 0; i < g_iNumLives; i++)
			g_pHeartImage->Draw(hDC, 520 + (g_pHeartImage->GetWidth() * i),
				10);
	}
	else if (g_uiState == UI_SETTINGS)
	{
		g_pBackground = new Background(g_pSettingsBackgroundImage);
		g_pBackground->Draw(hDC);
	}
	else if (g_uiState == UI_HELP)
	{
		g_pBackground = new Background(g_pHelpBackgroundImage);
		g_pBackground->Draw(hDC);
	}
	else if (g_uiState == UI_RANK)
	{
		g_pBackground = new Background(g_pRankBackgroundImage);
		g_pBackground->Draw(hDC);
	}
	else if (g_uiState == UI_END || g_uiState == UI_PAUSE)
	{
		g_pBackground = new Background(g_pGameBackgroundImage);
		g_pBackground->Draw(hDC);

		// Draw the sprites
		g_pGame->DrawSprites(hDC);

		// Draw the score
		TCHAR szText[64];
		RECT  rect = { 430, 0, 460, 30 };
		wsprintf(szText, "%d", g_iScore);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);		
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
    // Move the car based upon left/right key presses
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

			if (pSprite->GetImage() == g_pGameImage) {
				g_uiState = UI_GAME;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源(除背景图片外)
				NewGame();
			}
			else if (pSprite->GetImage() == g_pSettingsImage) {
				g_uiState = UI_SETTINGS;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源

			}
			else if (pSprite->GetImage() == g_pHelpImage) {
				g_uiState = UI_HELP;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源

			}
			else if (pSprite->GetImage() == g_pRankImage) {
				g_uiState = UI_RANK;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//加载新界面需要的资源

			}
			else if (pSprite->GetImage() == g_pExitImage) {
				g_uiState = UI_EXIT;
				
				//由开始界面退出程序 清理开始界面的五个按钮的资源
				RemoveOption();

				g_pGame->Quit();
			}
			else
				return;
		}
	}	
	else if (g_uiState == UI_GAME && bLeft) {
		//确定点击的是哪个图标
		Sprite* pSprite;
		if ((pSprite = g_pGame->IsPointInSprite(x, y)) != NULL) {
			if (pSprite->GetImage() == g_pMusicOnImage) {
				g_bMusicOn = false;

				// 更换图片
				pSprite->SetImage(g_pMusicOffImage);

				// Close the MIDI player for the background music
				g_pGame->PauseMIDISong();
			}
			else if (pSprite->GetImage() == g_pMusicOffImage) {
				g_bMusicOn = true;

				// 更换图片
				pSprite->SetImage(g_pMusicOnImage);

				// Open the MIDI player for the background music
				g_pGame->PlayMIDISong();
			}
			else if (pSprite->GetImage() == g_pPauseImage) {
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
				// 重新开始
				g_uiState = UI_GAME;
				g_gaState = GA_NEW;

				NewGame();
			}
			else if (pSprite->GetImage() == g_pGameMainImage) {
				// 主页
				g_uiState = UI_OPTION;
				
				NewOption();
			}
			else if (pSprite->GetImage() == g_pCancelImage) {
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
				// 重新开始
				g_uiState = UI_GAME;
				g_gaState = GA_NEW;

				NewGame();
			}
			else if (pSprite->GetImage() == g_pGameContinueImage) {
				// 继续
				g_uiState = UI_GAME;
				g_gaState = GA_CONTINUE;

				// 清除暂停界面的几个sprite
				if(!RemovePause())
					NewOption();
			}
			else if (pSprite->GetImage() == g_pGameMainImage) {
				// 主页
				g_uiState = UI_OPTION;

				NewOption();
			}
			else if (pSprite->GetImage() == g_pCancelImage) {
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
	if(g_bMusicOn == true)
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
	if (g_bMusicOn == true)
		PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC |
			SND_RESOURCE);

    // Kill the stone sprite
	pSpriteHittee->Kill();

    // Move the car back to the start
    g_pGirlSprite->SetPosition((int)g_iWidth * 0.3, (int)(g_iHeight - g_pGirlImage->GetHeight()));

    // See if the game is over
    if (--g_iNumLives == 0)
    {
      // Play the game over sound
	  if (g_bMusicOn == true)
		PlaySound((LPCSTR)IDW_GAMEOVER, g_hInstance, SND_ASYNC |
			SND_RESOURCE);
      g_bGameOver = TRUE;
	  g_uiState = UI_END;
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
	if (g_bMusicOn == true)
		PlaySound((LPCSTR)IDW_SMEXPLODE, g_hInstance, SND_ASYNC |
			SND_RESOURCE | SND_NOSTOP);
  }
  // See if a stone prite is dying
  else if (pSpriteDying->GetImage() == g_pStoneImage)
  {
	  // Play sound
	  if (g_bMusicOn == true)
		  PlaySound((LPCSTR)IDW_SMEXPLODE, g_hInstance, SND_ASYNC |
			  SND_RESOURCE | SND_NOSTOP);
  }
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
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
  if (g_bMusicOn == true)
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
  g_iDifficulty = 80;
  g_bGameOver = FALSE;

  // Play the background music
  if (g_bMusicOn == true)
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
	pSprite->SetDieDelay(50);
	pSprite->SetCollidable(TRUE);
    break;
  }

  // Add the sprite
  if(pSprite != NULL)
	g_pGame->AddSprite(pSprite);
}
