#pragma once

class MaoGameFramework
{
public:
    bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
    void OnDestroy();

    bool CreateDirect3DDisplay();
    bool CreateRenderTargetDepthStencilView();
    
    void FrameAdvance();

private:
    HINSTANCE Instance{ nullptr };
    HWND Wnd{ nullptr };

    ID3D11Device* D3DDevice{ nullptr };
    ID3D11DeviceContext* D3DDeviceContext{ nullptr };
    IDXGISwapChain* DXGISwapChain{ nullptr };
    ID3D11RenderTargetView* D3DRenderTargetView{ nullptr };
    ID3D11Texture2D* D3DDepthStencilBuffer{ nullptr };
    ID3D11DepthStencilView* D3DDepthStencilView{ nullptr };

    int WndClientWidth{ 0 };
    int WndClientHeight{ 0 };
};
