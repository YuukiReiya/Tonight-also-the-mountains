#pragma once
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include "../ResultState/ResultState.h"
#include <memory>
#include <DirectXMath.h>

class LastTrain
	:public IResultState
{
public:

	void Init();
	void Update();
	void Render();
	void SetPos(D3DXVECTOR2 pos) { m_Pos = pos; }
	void SetTargetPos(float horizontal) { m_Horizontal = horizontal; }
	bool GetIsMoveEnd() { return m_Pos.x == m_Horizontal; }
private:
	std::unique_ptr<Sprite> m_pSprite;
	std::unique_ptr<Texture> m_pTexture;

	D3DXVECTOR2 m_Pos;			//	先頭車両の描画の中心
	float m_TrainLength;		//	電車の長さ
	float m_Scale;				//	スケール
	DirectX::XMFLOAT2 m_Size;	//	サイズ
	float m_Horizontal;			//　移動先x座標
	float m_Speed;				//	移動速度

};