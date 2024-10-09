#include "pch.h"
#include "MaoIlluminatedTexturedShader.h"

void MaoIlluminatedTexturedShader::CreateShader(ID3D11Device* InD3DDevice)
{
    MaoShader::CreateShader(InD3DDevice);

    D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    CreateVertexShaderFromFile(InD3DDevice, L"IlluminatedTexturedShader.fx", "VSTexturedLighting", "vs_5_1", &D3DVertexShader, InputElementDesc, ARRAYSIZE(InputElementDesc), &D3DInputLayout);
    CreatePixelShaderFromFile(InD3DDevice, L"IlluminatedTexturedShader.fx", "main", "vs_5_1", &D3DPixelShader);
}
