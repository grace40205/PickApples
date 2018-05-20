//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - AlienSprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AlienSprite.h"

//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------
extern Image* g_pStoneImage;
extern Image* g_pStoneImage;
extern int    g_iDifficulty;


//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
AlienSprite::AlienSprite(Bitmap* pBitmap, RECT& rcBounds,
  BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
  baBoundsAction)
{
}

AlienSprite::AlienSprite(Image * pImage, RECT & rcBounds, 
  BOUNDSACTION baBoundsAction): Sprite(pImage, rcBounds,
	  baBoundsAction)
{
}

AlienSprite::~AlienSprite()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION AlienSprite::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();

  // See if the alien should fire a missile
  if ((rand() % (g_iDifficulty / 2)) == 0)
    saSpriteAction |= SA_ADDSPRITE;

  return saSpriteAction;
}

Sprite* AlienSprite::AddSprite()
{
  // Create a new missile sprite
  RECT    rcBounds = { 0, 0, BoundsWidth, BoundsHeight };
  RECT    rcPos = GetPosition();
  Sprite* pSprite = NULL;
  if (GetImage() == g_pStoneImage)
  {
    // Blobbo missile
    pSprite = new Sprite(g_pStoneImage, rcBounds, BA_DIE);
    pSprite->SetVelocity(0, 7);
  }


  // Set the missile sprite's position and return it
  pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
  return pSprite;
}
