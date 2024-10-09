#include "pch.h"
#include "MaoDiffusedShader.h"

void MaoDiffusedShader::CreateShader(ID3D11Device* InD3DDevice)
{
    MaoShader::CreateShader(InD3DDevice);

    D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    CreateVertexShaderFromFile(InD3DDevice, L"DiffusedShader.fx", "VSDiffusedColor", "vs_5_1", &D3DVertexShader, InputElementDesc, ARRAYSIZE(InputElementDesc), &D3DInputLayout);
    CreatePixelShaderFromFile(InD3DDevice, L"DiffusedShader.fx", "main", "vs_5_1", &D3DPixelShader);
}
