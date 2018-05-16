#include "Image.h"



Image::Image()
	:	m_iWidth(0), m_iHeight(0)
{

}
// Create a bitmap from a file
Image::Image(HDC hDC, LPTSTR szFileName)
	:  m_iWidth(0), m_iHeight(0)
{
	Create(hDC, szFileName);
}
Image::Image(HDC hDC, int iWidth, int iHeight, LPTSTR szFileName)
	: m_iWidth(0), m_iHeight(0)
{
	Create(hDC, iWidth, iHeight, szFileName);
}
BOOL Image::Create(HDC hDC, LPTSTR szFileName)
{
	// Free any previous bitmap info
	Free();

	m_image.Load(szFileName);
	m_iWidth = m_image.GetWidth();
	m_iHeight = m_image.GetHeight();
	return TRUE;
}
BOOL Image::Create(HDC hDC, int iWidth, int iHeight, LPTSTR szFileName)
{
	// Free any previous bitmap info
	Free();

	m_image.Load(szFileName);
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	return TRUE;
}
void Image::Draw(HDC hDC, int x, int y)
{
	if(m_image != NULL)
		m_image.Draw(hDC, x, y);
}
void Image::DrawPart(HDC hDC, int x, int y, int xPart, int yPart, int wPart, int hPart)
{
	if (m_image != NULL)
	{
		m_image.Draw(hDC, x, y, wPart, hPart, xPart, yPart, wPart, hPart);
	}
}
void Image::Free()
{
	// Delete the bitmap graphics object
	m_image.Destroy();
}
Image::~Image()
{
}
