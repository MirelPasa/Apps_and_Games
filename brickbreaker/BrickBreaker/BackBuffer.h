#ifndef BACKBUFFER_H
#define BACKBUFFER_H
#include <Windows.h>

class	BackBuffer
{

public:
    BackBuffer ( HWND hWnd, int width, int height );
    ~BackBuffer ( void );
    void	present ( void );
    void	reset ( void );
    HDC getDC ( void ) const
    {
        return mhDC;
    }
    HWND getHWND ( void ) const
    {
        return mhWnd;
    }
    int width ( void ) const
    {
        return mWidth;
    }
    int height ( void ) const
    {
        return mHeight;
    }

private:
    BackBuffer ( const BackBuffer &rhs );
    BackBuffer &operator	= ( const BackBuffer &rhs );
    HWND	mhWnd;
    HDC		mhDC;
    HBITMAP mhSurface;
    HBITMAP mhOldObject;
    int		mWidth;
    int		mHeight;
};
#endif 
