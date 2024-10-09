#pragma once

#include "MaoShader.h"

class MaoDiffusedShader : public MaoShader
{
public:
    virtual void CreateShader(ID3D11Device* InD3DDevice) override;
};
