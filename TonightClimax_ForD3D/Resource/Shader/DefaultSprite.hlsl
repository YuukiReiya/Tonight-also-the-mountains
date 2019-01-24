//�O���[�o��

Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global
{
	matrix g_WVP;		/*!< ���[���h����ˉe�܂ł̕ϊ��s�� */
	float2 g_DivNum;	/*!< �e�N�X�`���̕����� */
	float2 g_useIndexUV;/*!< ���������e�N�X�`���̕`��C���f�b�N�X */
	float4 g_Color;		/*!< �F */
};
//�\����
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

//
//
//�o�[�e�b�N�X�V�F�[�_�[
PS_INPUT VS( float4 Pos : POSITION ,float2 UV : TEXCOORD) 
{
	/*! �錾 */
	PS_INPUT Out;

	/*! ���W�v�Z */
	{
		matrix m = transpose(g_WVP);/*!< �]�u�s�� */

		Out.Pos = mul(Pos, m);
	}
	
	/*! UV�v�Z */
	{
		float x, y;
		x = UV.x *(1.0f / g_DivNum.x) + (g_useIndexUV.x / g_DivNum.x);
		y = UV.y *(1.0f / g_DivNum.y) + (g_useIndexUV.y / g_DivNum.y);

		Out.UV.x = x;
		Out.UV.y = y;
		//�؂蔲��
		//Out.UV = UV * float2(0.5f, 0.5f) + float2(0.2f, 0.2f);
	}

	return Out;
}
//
//
//�s�N�Z���V�F�[�_�[
float4 PS( PS_INPUT Input ) : SV_Target
{
	float4 ret;

	/*! �F */
	{
		ret = g_Texture.Sample(g_Sampler, Input.UV);

		//	�`���臒l
		if (ret.a <= 0.5)discard;

	}

	return ret*g_Color;
}