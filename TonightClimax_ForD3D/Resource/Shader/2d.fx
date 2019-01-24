

cbuffer myObject : register( b0 )
{     
	float4x4 world;
}

// テクスチャとサンプラの設定
Texture2D  texDiffuse  : register( t0 );
SamplerState samDiffuse  : register( s0 );


struct VS_INPUT
{
    float4 Pos   		: POSITION;
    float4 Color  		: COLOR;
    float4 uv			: TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Pos   		: SV_POSITION;
    float4 Color   		: COLOR;
    float4 uv			: TEXCOORD0;
};

VS_OUTPUT vsMain( VS_INPUT In )
{
    VS_OUTPUT Output = (VS_OUTPUT)0;
    
    Output.Pos 		= mul(In.Pos, world);
    Output.Color    = In.Color;
    Output.uv 		= In.uv;
    return Output;    
}

float4 psMain( VS_OUTPUT In ) : SV_Target
{
	//return In.Color;
    return texDiffuse.Sample( samDiffuse, In.uv );
}

