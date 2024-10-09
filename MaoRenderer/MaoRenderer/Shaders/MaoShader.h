#pragma once

class MaoShader
{
public:
    MaoShader();
    virtual ~MaoShader();

    virtual void CreateShader(ID3D11Device* InD3DDevice);

protected:
    void CreateVertexShaderFromFile(ID3D11Device* InD3DDevice, LPCWSTR InFileName, LPCSTR InShaderName, LPCSTR InShaderModel, ID3D11VertexShader** InD3DVertexShader, D3D11_INPUT_ELEMENT_DESC* InD3DInputLayout, UINT InElements, ID3D11InputLayout** InD3DVertexLayout);
    void CreatePixelShaderFromFile(ID3D11Device* InD3DDevice, LPCWSTR InFileName, LPCSTR InShaderName, LPCSTR InShaderModel, ID3D11PixelShader** InD3DPixelShader);
    void CreateGeometryShaderFromFile(ID3D11Device* InD3DDevice, LPCWSTR InFileName, LPCSTR InShaderName, LPCSTR InShaderModel, ID3D11GeometryShader** InD3DGeometryShader);
    
protected:
    ID3D11VertexShader* D3DVertexShader{ nullptr };
    ID3D11InputLayout* D3DInputLayout{ nullptr };
    ID3D11PixelShader* D3DPixelShader{ nullptr };
    ID3D11GeometryShader* D3DGeometryShader{ nullptr };
};
