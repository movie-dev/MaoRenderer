#include "pch.h"
#include "MaoShader.h"

MaoShader::MaoShader()
{
}

MaoShader::~MaoShader()
{
    if (D3DVertexShader)
    {
        D3DVertexShader->Release();
    }
    if (D3DPixelShader)
    {
        D3DPixelShader->Release();
    }
    if (D3DGeometryShader)
    {
        D3DGeometryShader->Release();
    }
    if (D3DInputLayout)
    {
        D3DInputLayout->Release();
    }
}

void MaoShader::CreateShader(ID3D11Device* InD3DDevice)
{
}

void MaoShader::CreateVertexShaderFromFile(ID3D11Device* InD3DDevice, LPCWSTR InFileName, LPCSTR InShaderName, LPCSTR InShaderModel, ID3D11VertexShader** InD3DVertexShader, D3D11_INPUT_ELEMENT_DESC* InD3DInputLayout, UINT InElements, ID3D11InputLayout** InD3DVertexLayout)
{
    HRESULT Result;

    DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    ShaderFlags |= (D3DCOMPILE_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION);
#endif

    ID3DBlob* D3DVertexShaderBlob = nullptr;
    ID3DBlob* D3DErrorBlob = nullptr;
    if (SUCCEEDED(Result = D3DCompileFromFile(InFileName, nullptr, nullptr, InShaderName, InShaderModel, ShaderFlags, 0, &D3DVertexShaderBlob, &D3DErrorBlob)))
    {
        InD3DDevice->CreateVertexShader(D3DVertexShaderBlob->GetBufferPointer(), D3DVertexShaderBlob->GetBufferSize(), nullptr, InD3DVertexShader);
        InD3DDevice->CreateInputLayout(InD3DInputLayout, InElements, D3DVertexShaderBlob->GetBufferPointer(), D3DVertexShaderBlob->GetBufferSize(), InD3DVertexLayout);
        D3DVertexShaderBlob->Release();
    }
}

void MaoShader::CreatePixelShaderFromFile(ID3D11Device* InD3DDevice, LPCWSTR InFileName, LPCSTR InShaderName, LPCSTR InShaderModel, ID3D11PixelShader** InD3DPixelShader)
{
    HRESULT Result;

    DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    ShaderFlags |= (D3DCOMPILE_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION);
#endif

    ID3DBlob* D3DPixelShaderBlob = nullptr;
    ID3DBlob* D3DErrorBlob = nullptr;
    if (SUCCEEDED(Result = D3DCompileFromFile(InFileName, nullptr, nullptr, InShaderName, InShaderModel, ShaderFlags, 0, &D3DPixelShaderBlob, &D3DErrorBlob)))
    {
        InD3DDevice->CreatePixelShader(D3DPixelShaderBlob->GetBufferPointer(), D3DPixelShaderBlob->GetBufferSize(), nullptr, InD3DPixelShader);
        D3DPixelShaderBlob->Release();
    }
}

void MaoShader::CreateGeometryShaderFromFile(ID3D11Device* InD3DDevice, LPCWSTR InFileName, LPCSTR InShaderName, LPCSTR InShaderModel, ID3D11GeometryShader** InD3DGeometryShader)
{
    HRESULT Result;

    DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    ShaderFlags |= (D3DCOMPILE_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION);
#endif

    ID3DBlob* D3DGeometryShaderBlob = nullptr;
    ID3DBlob* D3DErrorBlob = nullptr;
    if (SUCCEEDED(Result = D3DCompileFromFile(InFileName, nullptr, nullptr, InShaderName, InShaderModel, ShaderFlags, 0, &D3DGeometryShaderBlob, &D3DErrorBlob)))
    {
        InD3DDevice->CreateGeometryShader(D3DGeometryShaderBlob->GetBufferPointer(), D3DGeometryShaderBlob->GetBufferSize(), nullptr, InD3DGeometryShader);
        D3DGeometryShaderBlob->Release();
    }
}
