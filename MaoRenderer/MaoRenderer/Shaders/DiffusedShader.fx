cbuffer ViewProjectionMatrix : register(b0)
{
    matrix gView : packoffset(c0);
    matrix gProjection : packoffset(c4);
};

cbuffer WorldMatrix : register(b1)
{
    matrix gWorld : packoffset(c0);
};

struct VS_DIFFUSED_COLOR_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR0;
};

struct VS_DIFFUSED_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VS_DIFFUSED_COLOR_OUTPUT VSDiffusedColor(VS_DIFFUSED_COLOR_INPUT input)
{
    VS_DIFFUSED_COLOR_OUTPUT output = (VS_DIFFUSED_COLOR_OUTPUT)0;
    matrix WorldViewProjection = mul(gWorld, gView);
    WorldViewProjection = mul(WorldViewProjection, gProjection);
    output.position = mul(float4(input.position, 1.0f), WorldViewProjection);
    output.color = input.color;
    
    return output;
}

float4 main(VS_DIFFUSED_COLOR_OUTPUT input) : SV_Target
{
    return input.color;
}