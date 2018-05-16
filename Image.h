#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <atlimage.h>
class Image
{
protected:
	// Member Variables
	CImage m_image;
	int     m_iWidth, m_iHeight;
	void Free();
public:
	Image();
	Image(HDC hDC, LPTSTR szFileName);
	Image(HDC hDC, int iWidth, int iHeight, LPTSTR szFileName);

	BOOL Create(HDC hDC, LPTSTR szFileName);
	BOOL Create(HDC hDC, int iWidth, int iHeight, LPTSTR szFileName);

	void Draw(HDC hDC, int x, int y);
	void DrawPart(HDC hDC, int x, int y, int xPart, int yPart,
		int wPart, int hPart);

	~Image();
	int  GetWidth() { return m_iWidth; };
	int  GetHeight() { return m_iHeight; };
};

