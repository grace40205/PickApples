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
    TEXT("Space Out"), IDI_SPACEOUT, IDI_SPACEOUT_SM, 600, 450);
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

  g_pPlayerImage = new Image(hDC, TEXT("Res\\Car.bmp"));
  g_pSmCarBitmap = new Image(hDC, TEXT("Res\\SmCar.bmp"));
  g_pMissileBitmap = new Image(hDC, TEXT("Res\\Missile.bmp"));
  g_pBlobboBitmap = new Image(hDC, TEXT("Res\\Blobbo.png"));
  g_pBMissileBitmap = new Image(hDC, TEXT("Res\\BMissile.bmp"));
  g_pJellyBitmap = new Image(hDC, TEXT("Res\\Jelly.bmp"));
  g_pJMissileBitmap = new Image(hDC, TEXT("Res\\JMissile.bmp"));
  g_pTimmyBitmap = new Image(hDC, TEXT("Res\\Timmy.bmp"));
  g_pTMissileBitmap = new Image(hDC, TEXT("Res\\TMissile.bmp"));
  g_pSmExplosionBitmap = new Image(hDC, TEXT("Res\\SmExplosion.bmp"));
  g_pLgExplosionBitmap = new Image(hDC, TEXT("Res\\LgExplosion.bmp"));
  g_pGameOverBitmap = new Image(hDC, TEXT("Res\\GameOver.bmp"));

  g_pOpitonBackgroundImage = new Image(hDC, TEXT("Res\\OptionBackground.jpg"));
  g_pGameBackgroundImage = new Image(hDC, TEXT("Res\\GameBackground.jpg"));
  g_pSettingsBackgroundImage = new Image(hDC, TEXT("Res\\SettingsBackground.jpg"));
  g_pHelpBackgroundImage = new Image(hDC, TEXT("Res\\HelpBackground.jpg"));
  g_pRankBackgroundImage = new Image(hDC, TEXT("Res\\RankBackground.jpg"));

  
  // 默认情况下进入游戏选择界面
  g_uiState = UI_OPTION;

  // 这里应该读取xml文件获得开始游戏的模式：新游戏，上一个游戏
  g_gaState = GA_NEW;

  // Create the Game Option UI background
  g_pBackground = new Background(g_pOpitonBackgroundImage);

  // Play the background music
  g_pGame->PlayMIDISong(TEXT("Music.mid"));

  NewOption();
}

void NewOption() {
	// Obtain a device context for repainting the game
	HWND  hWindow = g_pGame->GetWindow();
	HDC   hDC = GetDC(hWindow);

	g_pGameImage = new Image(hDC, TEXT("Res\\Game.jpg"));
	g_pGameSprite = new Sprite(g_pGameImage);
	g_pGameSprite->SetPosition(200, 100);
	g_pGame->AddSprite(g_pGameSprite);

	g_pSettingsImage = new Image(hDC, TEXT("Res\\Settings.jpg"));
	g_pSettingsSprite = new Sprite(g_pSettingsImage);
	g_pSettingsSprite->SetPosition(200, 140);
	g_pGame->AddSprite(g_pSettingsSprite);

	g_pHelpImage = new Image(hDC, TEXT("Res\\Help.jpg"));
	g_pHelpSprite = new Sprite(g_pHelpImage);
	g_pHelpSprite->SetPosition(200, 180);
	g_pGame->AddSprite(g_pHelpSprite);

	g_pRankImage = new Image(hDC, TEXT("Res\\Rank.jpg"));
	g_pRankSprite = new Sprite(g_pRankImage);
	g_pRankSprite->SetPosition(200, 220);
	g_pGame->AddSprite(g_pRankSprite);

	g_pExitImage = new Image(hDC, TEXT("Res\\Exit.jpg"));
	g_pExitSprite = new Sprite(g_pExitImage);
	g_pExitSprite->SetPosition(200, 260);
	g_pGame->AddSprite(g_pExitSprite);
}

void RemoveOption()
{
	delete			g_pGameImage;
	delete			g_pSettingsImage;
	delete			g_pHelpImage;
	delete			g_pRankImage;
	delete			g_pExitImage;

	// Cleanup the sprites
	g_pGame->CleanupSprites();
}

void GameEnd()
{
  // Close the MIDI player for the background music
  g_pGame->CloseMIDIPlayer();

  // Cleanup the offscreen device context and bitmap
  DeleteObject(g_hOffscreenBitmap);
  DeleteDC(g_hOffscreenDC);  

  // Cleanup the bitmaps
  delete g_pPlayerImage;
  delete g_pSmCarBitmap;
  delete g_pMissileBitmap;
  delete g_pBlobboBitmap;
  delete g_pBMissileBitmap;
  delete g_pJellyBitmap;
  delete g_pJMissileBitmap;
  delete g_pTimmyBitmap;
  delete g_pTMissileBitmap;
  delete g_pSmExplosionBitmap;
  delete g_pLgExplosionBitmap;
  delete g_pGameOverBitmap;

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
		RECT  rect = { 460, 0, 510, 30 };
		wsprintf(szText, "%d", g_iScore);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		// Draw the number of remaining lives (cars)
		for (int i = 0; i < g_iNumLives; i++)
			g_pSmCarBitmap->Draw(hDC, 520 + (g_pSmCarBitmap->GetWidth() * i),
				10);

		// Draw the game over message, if necessary
		if (g_bGameOver)
			g_pGameOverBitmap->Draw(hDC, 190, 149);
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
	else if (g_uiState == UI_END)
	{
		
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
    if ((rand() % g_iDifficulty) == 0)
      AddAlien();

    // Update the background
    g_pBackground->Update();

    // Update the sprites
    g_pGame->UpdateSprites();

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
	return;
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
    POINT ptVelocity = g_pPlayerSprite->GetVelocity();
    if (GetAsyncKeyState(VK_LEFT) < 0)
    {
      // Move left
      ptVelocity.x = max(ptVelocity.x - 1, -4);
      g_pPlayerSprite->SetVelocity(ptVelocity);
    }
    else if (GetAsyncKeyState(VK_RIGHT) < 0)
    {
      // Move right
      ptVelocity.x = min(ptVelocity.x + 2, 6);
      g_pPlayerSprite->SetVelocity(ptVelocity);
    }

    // Fire missiles based upon spacebar presses
    if ((++g_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0)
    {
      // Create a new missile sprite
      RECT  rcBounds = { 0, 0, 600, 450 };
      RECT  rcPos = g_pPlayerSprite->GetPosition();
      Sprite* pSprite = new Sprite(g_pMissileBitmap, rcBounds, BA_DIE);
      pSprite->SetPosition(rcPos.left + 15, 400);
      pSprite->SetVelocity(0, -7);
      g_pGame->AddSprite(pSprite);

      // Play the missile (fire) sound
      PlaySound((LPCSTR)IDW_MISSILE, g_hInstance, SND_ASYNC |
        SND_RESOURCE | SND_NOSTOP);

      // Reset the input delay
      g_iFireInputDelay = 0;
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
				//记载新界面需要的资源(除背景图片外)
				NewGame();
			}
			else if (pSprite->GetImage() == g_pSettingsImage) {
				g_uiState = UI_SETTINGS;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//记载新界面需要的资源
			}
			else if (pSprite->GetImage() == g_pHelpImage) {
				g_uiState = UI_HELP;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//记载新界面需要的资源
			}
			else if (pSprite->GetImage() == g_pRankImage) {
				g_uiState = UI_RANK;

				//跳转界面 需先清理开始界面的五个按钮的资源
				RemoveOption();
				//记载新界面需要的资源
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
  // See if a player missile and an alien have collided
  Image* pHitter = pSpriteHitter->GetImage();
  Image* pHittee = pSpriteHittee->GetImage();
  if ((pHitter == g_pMissileBitmap && (pHittee == g_pBlobboBitmap ||
    pHittee == g_pJellyBitmap || pHittee == g_pTimmyBitmap)) ||
    (pHittee == g_pMissileBitmap && (pHitter == g_pBlobboBitmap ||
    pHitter == g_pJellyBitmap || pHitter == g_pTimmyBitmap)))
  {
    // Play the small explosion sound
    PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC |
      SND_RESOURCE);

    // Kill both sprites
    pSpriteHitter->Kill();
    pSpriteHittee->Kill();

    // Create a large explosion sprite at the alien's position
    RECT rcBounds = { 0, 0, 600, 450 };
    RECT rcPos;
    if (pHitter == g_pMissileBitmap)
      rcPos = pSpriteHittee->GetPosition();
    else
      rcPos = pSpriteHitter->GetPosition();
    Sprite* pSprite = new Sprite(g_pLgExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, TRUE);
    pSprite->SetPosition(rcPos.left, rcPos.top);
    g_pGame->AddSprite(pSprite);

    // Update the score
    g_iScore += 25;
    g_iDifficulty = max(80 - (g_iScore / 20), 20);
  }

  // See if an alien missile has collided with the car
  if ((pHitter == g_pPlayerImage && (pHittee == g_pBMissileBitmap ||
    pHittee == g_pJMissileBitmap || pHittee == g_pTMissileBitmap)) ||
    (pHittee == g_pPlayerImage && (pHitter == g_pBMissileBitmap ||
    pHitter == g_pJMissileBitmap || pHitter == g_pTMissileBitmap)))
  {
    // Play the large explosion sound
    PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC |
      SND_RESOURCE);

    // Kill the missile sprite
    if (pHitter == g_pPlayerImage)
      pSpriteHittee->Kill();
    else
      pSpriteHitter->Kill();

    // Create a large explosion sprite at the car's position
    RECT rcBounds = { 0, 0, 600, 480 };
    RECT rcPos;
    if (pHitter == g_pPlayerImage)
      rcPos = pSpriteHitter->GetPosition();
    else
      rcPos = pSpriteHittee->GetPosition();
    Sprite* pSprite = new Sprite(g_pLgExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, TRUE);
    pSprite->SetPosition(rcPos.left, rcPos.top);
    g_pGame->AddSprite(pSprite);

    // Move the car back to the start
    g_pPlayerSprite->SetPosition(300, 405);

    // See if the game is over
    if (--g_iNumLives == 0)
    {
      // Play the game over sound
      PlaySound((LPCSTR)IDW_GAMEOVER, g_hInstance, SND_ASYNC |
        SND_RESOURCE);
      g_bGameOver = TRUE;
    }
  }

  return FALSE;
}

void SpriteDying(Sprite* pSpriteDying)
{
  // See if an alien missile sprite is dying
  if (pSpriteDying->GetImage() == g_pBMissileBitmap ||
    pSpriteDying->GetImage() == g_pJMissileBitmap ||
    pSpriteDying->GetImage() == g_pTMissileBitmap)
  {
    // Play the small explosion sound
    PlaySound((LPCSTR)IDW_SMEXPLODE, g_hInstance, SND_ASYNC |
      SND_RESOURCE | SND_NOSTOP);

    // Create a small explosion sprite at the missile's position
    RECT rcBounds = { 0, 0, 600, 450 };
    RECT rcPos = pSpriteDying->GetPosition();
    Sprite* pSprite = new Sprite(g_pSmExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, TRUE);
    pSprite->SetPosition(rcPos.left, rcPos.top);
    g_pGame->AddSprite(pSprite);
  }
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
  // Clear the sprites
  g_pGame->CleanupSprites();

  // Create the car sprite
  RECT rcBounds = { 0, 0, 600, 450 };
  g_pPlayerSprite = new Sprite(g_pPlayerImage, rcBounds, BA_WRAP);
  g_pPlayerSprite->SetPosition(300, 405);
  g_pGame->AddSprite(g_pPlayerSprite);

  // Initialize the game variables
  g_iFireInputDelay = 0;
  g_iScore = 0;
  g_iNumLives = 3;
  g_iDifficulty = 80;
  g_bGameOver = FALSE;

  // Play the background music
  g_pGame->PlayMIDISong();
}

void AddAlien()
{
  // Create a new random alien sprite
  RECT          rcBounds = { 0, 0, 600, 410 };
  AlienSprite*  pSprite;
  switch(rand() % 3)
  {
  case 0:
    // Blobbo
    pSprite = new AlienSprite(g_pBlobboBitmap, rcBounds, BA_BOUNCE);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(((rand() % 2) == 0) ? 0 : 600, rand() % 370);
    pSprite->SetVelocity((rand() % 7) - 2, (rand() % 7) - 2);
    break;
  case 1:
    // Jelly
    pSprite = new AlienSprite(g_pJellyBitmap, rcBounds, BA_BOUNCE);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % 600, rand() % 370);
    pSprite->SetVelocity((rand() % 5) - 2, (rand() % 5) + 3);
    break;
  case 2:
    // Timmy
    pSprite = new AlienSprite(g_pTimmyBitmap, rcBounds, BA_WRAP);
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(rand() % 600, rand() % 370);
    pSprite->SetVelocity((rand() % 7) + 3, 0);
    break;
  }

  // Add the alien sprite
  g_pGame->AddSprite(pSprite);
}
