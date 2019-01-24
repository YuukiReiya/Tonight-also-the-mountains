#pragma once
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"	
#include <memory>
#include <DirectXMath.h>

//	Resultシーン上のキャラクター
class ResultCharacter
{
public:

	enum BalloonState
	{
		NONE,
		CRY,
		WORD,
		HAPPY,
	};

	void Init();
	void Render();
	void Update();
	void SetBalloonState(BalloonState state) { m_eBalloonState = state; }
	void SetTargetPos(D3DXVECTOR2 pos) { m_Target = pos; }
private:
	void BalloonUpdate();
	void Move();

	std::unique_ptr<Sprite> m_pSprite;
	std::unique_ptr<Texture> m_pTexture;
	std::unique_ptr<Texture> m_pBalloonTex;

	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Target;
	D3DXVECTOR2 m_BalloonOffset;
	DirectX::XMINT2		m_BalloonSplit;
	DirectX::XMINT2		m_BalloonAtlas;
	DirectX::XMFLOAT2	m_BalloonSize;
	float				m_BalloonScale;

	DirectX::XMINT2		m_Split;
	DirectX::XMINT2		m_Atlas;
	DirectX::XMFLOAT2	m_Size;
	float				m_Scale;
	float m_Speed;
	int cnt;
	int changeBalloonCnt;
	BalloonState m_eBalloonState;
};