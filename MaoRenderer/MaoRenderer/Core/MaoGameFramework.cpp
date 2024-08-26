#include "pch.h"
#include "MaoGameFramework.h"

bool MaoGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
    Instance = hInstance;
    Wnd = hMainWnd;

    if (!CreateDirect3DDisplay())
    {
        return false;
    }
    
    return true;
}

void MaoGameFramework::OnDestroy()
{
    if (D3DDeviceContext)
    {
        D3DDeviceContext->ClearState();
    }
    if (D3DRenderTargetView)
    {
        D3DRenderTargetView->Release();
    }
    if (D3DDepthStencilBuffer)
    {
        D3DDepthStencilBuffer->Release();
    }
    if (D3DDepthStencilView)
    {
        D3DDepthStencilView->Release();
    }
    if (DXGISwapChain)
    {
        DXGISwapChain->Release();
    }
    if (D3DDeviceContext)
    {
        D3DDeviceContext->Release();
    }
    if (D3DDevice)
    {
        D3DDevice->Release();
    }
}

bool MaoGameFramework::CreateDirect3DDisplay()
{
    RECT rcClient;
	::GetClientRect(Wnd, &rcClient);
    WndClientWidth = rcClient.right - rcClient.left;
    WndClientHeight = rcClient.bottom - rcClient.top;

	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(dxgiSwapChainDesc));
    dxgiSwapChainDesc.BufferCount = 1;
    dxgiSwapChainDesc.BufferDesc.Width = WndClientWidth;
    dxgiSwapChainDesc.BufferDesc.Height = WndClientHeight;
    dxgiSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    dxgiSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    dxgiSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dxgiSwapChainDesc.OutputWindow = Wnd;
    dxgiSwapChainDesc.SampleDesc.Count = 1;
    dxgiSwapChainDesc.SampleDesc.Quality = 0;
    dxgiSwapChainDesc.Windowed = TRUE;

    UINT dwCreateDeviceFlags = 0;
#ifdef _DEBUG
    dwCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    constexpr D3D_DRIVER_TYPE d3dDriverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };
    constexpr auto DriverTypes = sizeof(d3dDriverTypes) / sizeof(D3D_DRIVER_TYPE);

    constexpr D3D_FEATURE_LEVEL d3dFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	constexpr auto FeatureLevels = sizeof(d3dFeatureLevels) / sizeof(D3D_FEATURE_LEVEL);

    HRESULT Result = S_OK;
	D3D_DRIVER_TYPE d3dDriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;
    for (UINT i = 0; i < DriverTypes; i++)
    {
        d3dDriverType = d3dDriverTypes[i];
        if (SUCCEEDED(Result = D3D11CreateDeviceAndSwapChain(nullptr, d3dDriverType, NULL, dwCreateDeviceFlags, d3dFeatureLevels, FeatureLevels, D3D11_SDK_VERSION, &dxgiSwapChainDesc, &DXGISwapChain, &D3DDevice, &d3dFeatureLevel, &D3DDeviceContext)))
        {
            break;
        }
    }

	if (!CreateRenderTargetDepthStencilView())
	{
	    return false;
	}

	return true;
}

bool MaoGameFramework::CreateRenderTargetDepthStencilView()
{
    HRESULT hResult = S_OK;

    ID3D11Texture2D* d3dBackBuffer;
    if (FAILED(hResult = DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID *>(&d3dBackBuffer))))
    {
        return false;
    }
    if (FAILED(hResult = D3DDevice->CreateRenderTargetView(d3dBackBuffer, NULL, &D3DRenderTargetView)))
    {
        return false;
    }
    if (d3dBackBuffer)
    {
        d3dBackBuffer->Release();
    }
    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC d3dDepthStencilBufferDesc;
    ZeroMemory(&d3dDepthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
    d3dDepthStencilBufferDesc.Width = WndClientWidth;
    d3dDepthStencilBufferDesc.Height = WndClientHeight;
    d3dDepthStencilBufferDesc.MipLevels = 1;
    d3dDepthStencilBufferDesc.ArraySize = 1;
    d3dDepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    d3dDepthStencilBufferDesc.SampleDesc.Count = 1;
    d3dDepthStencilBufferDesc.SampleDesc.Quality = 0;
    d3dDepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    d3dDepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    d3dDepthStencilBufferDesc.CPUAccessFlags = 0;
    d3dDepthStencilBufferDesc.MiscFlags = 0;
    if (FAILED(hResult = D3DDevice->CreateTexture2D(&d3dDepthStencilBufferDesc, NULL, &D3DDepthStencilBuffer)))
    {
        return false;
    }

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC d3dDepthStencilViewDesc;
    ZeroMemory(&d3dDepthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    d3dDepthStencilViewDesc.Format = d3dDepthStencilBufferDesc.Format;
    d3dDepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    d3dDepthStencilViewDesc.Texture2D.MipSlice = 0;
    if (FAILED(hResult = D3DDevice->CreateDepthStencilView(D3DDepthStencilBuffer, &d3dDepthStencilViewDesc, &D3DDepthStencilView)))
    {
        return false;
    }

    D3DDeviceContext->OMSetRenderTargets(1, &D3DRenderTargetView, D3DDepthStencilView);
 
    return true;
}

void MaoGameFramework::FrameAdvance()
{
    constexpr float fClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
    if (D3DRenderTargetView)
    {
        D3DDeviceContext->ClearRenderTargetView(D3DRenderTargetView, fClearColor);
    }
    if (D3DDepthStencilView)
    {
        D3DDeviceContext->ClearDepthStencilView(D3DDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    DXGISwapChain->Present(0, 0);
}
