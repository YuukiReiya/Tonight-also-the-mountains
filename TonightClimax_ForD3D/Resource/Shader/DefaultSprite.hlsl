//グローバル

Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global
{
	matrix g_WVP;		/*!< ワールドから射影までの変換行列 */
	float2 g_DivNum;	/*!< テクスチャの分割数 */
	float2 g_useIndexUV;/*!< 分割したテクスチャの描画インデックス */
	float4 g_Color;		/*!< 色 */
};
//構造体
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

//
//
//バーテックスシェーダー
PS_INPUT VS( float4 Pos : POSITION ,float2 UV : TEXCOORD) 
{
	/*! 宣言 */
	PS_INPUT Out;

	/*! 座標計算 */
	{
		matrix m = transpose(g_WVP);/*!< 転置行列 */

		Out.Pos = mul(Pos, m);
	}
	
	/*! UV計算 */
	{
		float x, y;
		x = UV.x *(1.0f / g_DivNum.x) + (g_useIndexUV.x / g_DivNum.x);
		y = UV.y *(1.0f / g_DivNum.y) + (g_useIndexUV.y / g_DivNum.y);

		Out.UV.x = x;
		Out.UV.y = y;
		//切り抜き
		//Out.UV = UV * float2(0.5f, 0.5f) + float2(0.2f, 0.2f);
	}

	return Out;
}
//
//
//ピクセルシェーダー
float4 PS( PS_INPUT Input ) : SV_Target
{
	float4 ret;

	/*! 色 */
	{
		ret = g_Texture.Sample(g_Sampler, Input.UV);

		//	描画の閾値
		if (ret.a <= 0.5)discard;

	}

	return ret*g_Color;
}