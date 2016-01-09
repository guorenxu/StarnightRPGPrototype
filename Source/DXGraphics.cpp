#include <d3d9.h>
#include <d3dx9.h>
#include "dxgraphics.h"

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

int Init_Direct3D(HWND hwnd, int width, int height, int fullscreen)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.Windowed = (!fullscreen);
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = 0;
    d3dpp.BackBufferHeight = 0;
    d3dpp.hDeviceWindow = hwnd;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    d3d->CreateDevice(
        D3DADAPTER_DEFAULT, 
        D3DDEVTYPE_HAL, 
        hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, 
        &d3ddev);

    //d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

    return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(char *filename, D3DCOLOR transcolor)
{
    LPDIRECT3DSURFACE9 image = NULL;
    D3DXIMAGE_INFO info;
    HRESULT result;
    
    result = D3DXGetImageInfoFromFile(filename, &info);

    result = d3ddev->CreateOffscreenPlainSurface(
        info.Width,
        info.Height,
        D3DFMT_X8R8G8B8,
        D3DPOOL_DEFAULT,
        &image,
        NULL);

    result = D3DXLoadSurfaceFromFile(
        image,
        NULL,
        NULL,
        filename,
        NULL,
        D3DX_DEFAULT,
        transcolor,
        NULL);

    return image;
}


LPDIRECT3DTEXTURE9 LoadTexture(char *filename, D3DCOLOR transcolor)
{
    LPDIRECT3DTEXTURE9 texture = NULL;

    D3DXIMAGE_INFO info;

    HRESULT result;
    
    result = D3DXGetImageInfoFromFile(filename, &info);

	D3DXCreateTextureFromFileEx( 
        d3ddev,      
        filename, 
        info.Width,
        info.Height,
        1,
        D3DPOOL_DEFAULT,
        D3DFMT_UNKNOWN,
        D3DPOOL_DEFAULT,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        transcolor,
        &info,
        NULL,
        &texture );

    return texture;
}