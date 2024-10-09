#include "Light.fx"

cbuffer ViewProjectionMatrix : register(b0)
{
    matrix gView : packoffset(c0);
    matrix gProjection : packoffset(c4);
};

cbuffer WorldMatrix : register(b1)
{
    matrix gWorld : packoffset(c0);
};

Texture2D gTexture : register(t0);
SamplerState gSamplerState : register(s0);

struct VS_TEXTURED_LIGHTING_INPUT
{
	float3	position    : POSITION;
	float3	normal		: NORMAL;
    float2  tex2dcoord	: TEXCOORD0;
};

struct VS_TEXTURED_LIGHTING_OUTPUT
{
	float4	position	: SV_POSITION;
    float3	positionW   : TEXCOORD0;
    float3	normalW		: TEXCOORD1;
    float2  tex2dcoord	: TEXCOORD2;
};

VS_TEXTURED_LIGHTING_OUTPUT VSTexturedLighting(VS_TEXTURED_LIGHTING_INPUT input)
{
    VS_TEXTURED_LIGHTING_OUTPUT output = (VS_TEXTURED_LIGHTING_OUTPUT)0;
	output.normalW = mul(input.normal, (float3x3)gWorld);
    output.positionW = mul(input.position, (float3x3)gWorld);
    output.positionW += float3(gWorld._41, gWorld._42, gWorld._43);
    matrix WorldViewProjection = mul(gWorld, gView);
	WorldViewProjection = mul(WorldViewProjection, gProjection);
    output.position = mul(float4(input.position, 1.0f), WorldViewProjection);
	output.tex2dcoord = input.tex2dcoord;

    return output;
}

float4 main(VS_TEXTURED_LIGHTING_OUTPUT input) : SV_Target
{ 
    input.normalW = normalize(input.normalW); 
	float4 Illumination = Lighting(input.positionW, input.normalW);
    float4 Color = gTexture.Sample(gSamplerState, input.tex2dcoord) * Illumination;

    return Color;
}