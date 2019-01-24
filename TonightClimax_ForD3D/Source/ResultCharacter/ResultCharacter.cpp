#include "ResultCharacter.h"

using namespace std;


void ResultCharacter::Init()
{
	m_pTexture		= make_unique<Texture>();
	m_pBalloonTex	= make_unique<Texture>();
	m_pSprite		= make_unique<Sprite>();


	m_pTexture->Load("../Resource/Image/chara_player.png");
	m_pBalloonTex->Load("../Resource/Image/Balloon.png");

	m_BalloonOffset = {40,-60 };
	m_BalloonSize = { 32,32 };
	m_Size = { 32,32 };
	m_BalloonScale = 2.5f;
	m_Scale = 2.5f;
	m_Split = { 3,4 };
	m_BalloonSplit = { 8,10 };
	m_Speed = 15;

	cnt = 0;
	changeBalloonCnt = 8;
	m_eBalloonState = BalloonState::NONE;
	m_Target = m_Pos = { -m_Size.x*m_Scale / 2,720 };
}

void ResultCharacter::Render()
{
	//	Character
	m_pSprite->SetSpriteSize(m_Size.x, m_Size.y);
	m_pSprite->SetSplit(m_Split.x, m_Split.y);
	m_pSprite->SetSizeScaling(m_Scale);
	m_pSprite->SetPos(m_Pos);
	m_pSprite->RenderAtlas(
		m_pTexture->GetTexture(),
		m_Atlas.x,
		m_Atlas.y
	);

	//	Balloon
	if (m_eBalloonState != BalloonState::NONE) {
		m_pSprite->SetSpriteSize(m_BalloonSize.x, m_BalloonSize.y);
		m_pSprite->SetSplit(m_BalloonSplit.x, m_BalloonSplit.y);
		m_pSprite->SetSizeScaling(m_BalloonScale);
		m_pSprite->SetPos(m_Pos + m_BalloonOffset);
		m_pSprite->RenderAtlas(
			m_pBalloonTex->GetTexture(),
			m_BalloonAtlas.x,
			m_BalloonAtlas.y
		);
	}
}

void ResultCharacter::Update()
{
	BalloonUpdate();
	Move();
}

void ResultCharacter::Move()
{
	if (m_Pos == m_Target) { return; }

	//	移動方向の符号
	int sign = (m_Target.x - m_Pos.x) >= 0 ? 1 : -1;

	//	移動
	m_Pos.x += m_Speed * sign;

	////////////
	//	補正　//
	////////////

	//	右
	if (sign > 0) {
		if (m_Pos.x > m_Target.x) {
			m_Pos.x = m_Target.x;
		}
	}
	//	左
	else {
		if (m_Pos.x < m_Target.x) {
			m_Pos.x = m_Target.x;
		}
	}

	//	移動方向の符号
	sign = (m_Target.y - m_Pos.y) >= 0 ? 1 : -1;

	//	移動
	m_Pos.y += m_Speed * sign;

	//	下
	if (sign > 0) {
		if (m_Pos.y > m_Target.y) {
			m_Pos.y = m_Target.y;
		}
	}
	//	上
	else {
		if (m_Pos.y < m_Target.y) {
			m_Pos.y = m_Target.y;
		}
	}

	////////////////
	//	アトラス　//
	////////////////

	auto tmp = m_Target - m_Pos;
	
	//	移動量が大きい方向に向ける

	//	上下方向
	if (abs(tmp.x) <= abs(tmp.y)) {
		m_Atlas.y = tmp.y < 0 ? 3 : 0;
	}
	//	左右方向
	else {
		m_Atlas.y = tmp.x < 0 ? 1 : 2;
	}
}

void ResultCharacter::BalloonUpdate()
{
	cnt++;

	//	Chara
	if (m_Pos != m_Target) {
		if (cnt % 8 == 0)
		m_Atlas.x = m_Atlas.x == 0 ? 2 : 0;
	}

	//	Balloon
	if (m_eBalloonState == BalloonState::NONE) {
		m_BalloonAtlas.x = 1;
		return;
	}

	switch (m_eBalloonState)
	{
		case ResultCharacter::CRY:	m_BalloonAtlas.y = 5; break;
		case ResultCharacter::WORD:	m_BalloonAtlas.y = 7; break;
		case ResultCharacter::HAPPY:m_BalloonAtlas.y = 2; break;
	}
	if (cnt%changeBalloonCnt == 0) {
		m_BalloonAtlas.x = m_BalloonAtlas.x == 7 ? 1 : ++m_BalloonAtlas.x;
	}
}
