#pragma once

#include <map>
#include "MaoShaderDefine.h"

class MaoWorld
{
public:
    MaoWorld();
    virtual ~MaoWorld();

    void BuildObjects(ID3D11Device* InD3DDevice);
    virtual void CreateShader(ID3D11Device* InD3DDevice);

protected:
    std::map<MaoShaderType, class MaoShader*> Shaders;
};
