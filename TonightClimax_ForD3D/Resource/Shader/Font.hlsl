//	グローバル
Texture2D		texDiffuse  : register(t0);
SamplerState	samDiffuse  : register(s0);

//	Cバッファ
cbuffer global : register(b0)
{
	matrix world;
}


struct VS_INPUT
{
	float4 Pos   		: SV_POSITION;
	float2 uv			: TEXCOORD;
};

VS_INPUT VS(float4 Pos : POSITION , float2 UV : TEXCOORD)
{
	VS_INPUT Out;

	{
		matrix m = transpose(world);
		Out.Pos = mul(Pos, m);
	}


	VS_INPUT Output = (VS_INPUT)0;

	Output.Pos = mul(Pos, world);
	Output.uv =UV;
	return Output;
}

float4 PS(VS_INPUT In) : SV_Target
{
	//return In.Color;
	return texDiffuse.Sample(samDiffuse, In.uv);
}

