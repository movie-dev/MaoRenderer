#include "pch.h"
#include "MaoWorld.h"

MaoWorld::MaoWorld()
{
}

MaoWorld::~MaoWorld()
{
}

void MaoWorld::BuildObjects(ID3D11Device* InD3DDevice)
{
    CreateShader(InD3DDevice);
}

void MaoWorld::CreateShader(ID3D11Device* InD3DDevice)
{
}
