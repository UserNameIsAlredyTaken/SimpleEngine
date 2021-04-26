//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
};

cbuffer cbPass : register(b1)
{
    float4x4 gView;
    float4x4 gInvView;
    float4x4 gProj;
    float4x4 gInvProj;
    float4x4 gViewProj;
    float4x4 gInvViewProj;
    float3 gEyePosW;
    float cbPerObjectPad1;
    float2 gRenderTargetSize;
    float2 gInvRenderTargetSize;
    float gNearZ;
    float gFarZ;
    float gTotalTime;
    float gDeltaTime;
};

struct VertexIn
{
	float3 PosL  : POSITION;
	float3 NormL : NORMALS;
    float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	// Transform to homogeneous clip space.
    float4 posW = mul(float4(vin.PosL, 1.0f), gWorld);
    vout.PosH = mul(posW, gViewProj);

	// Just pass vertex color into the pixel shader.
    //vout.Color = vin.Color;
    
	vout.Color.r = (vin.NormL.r + 1) / 2;
	vout.Color.g = (vin.NormL.g + 1) / 2;
	vout.Color.b = (vin.NormL.b + 1) / 2;
	vout.Color.a = 1;
    
	//vout.Color.rgba = vin.NormL.bgrr;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	//pin.Color.rgb = (1, 1, 1);
    return pin.Color;
}
