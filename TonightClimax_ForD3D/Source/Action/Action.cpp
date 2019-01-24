#include "Action.h"

const D3DXVECTOR2 ActionBase::c_basePos = { 960,540 };
const D3DXVECTOR2 ActionBase::c_balloonOffset = { 50,-80 };
const float ActionBase::c_betweenLength = 125;


void ActionBase::SetPlayer()
{
	auto& am = ActionManager::GetInstance();
	m_pCharacterTexture = am.GetPlayerTex();
	m_pBalloonTexture = am.GetBalloonTex();
	m_pSprite = am.GetSprite();
	m_CharaPos = c_basePos - D3DXVECTOR2(c_betweenLength, 0);
	m_BalloonPos = m_CharaPos + c_balloonOffset;
	m_CharaAtlas = { 1,2 };

}

void ActionBase::SetOwner()
{
	auto& am = ActionManager::GetInstance();
	m_pCharacterTexture = am.GetOwnerTex();
	m_pBalloonTexture = am.GetBalloonTex();
	m_pSprite = am.GetSprite();
	m_CharaPos = c_basePos + D3DXVECTOR2(c_betweenLength, 0);
	m_BalloonPos = m_CharaPos + c_balloonOffset;
	m_CharaAtlas = { 1,1 };

}

void ActionBase::Render()
{
	auto sprite = m_pSprite.lock();
	auto ct = m_pCharacterTexture.lock();

	auto&am = ActionManager::GetInstance();
	auto cd = am.GetCharaData();
	sprite->SetSpriteSize(cd.size.x, cd.size.y);
	sprite->SetSizeScaling(cd.scale);
	sprite->SetSplit(cd.split.x, cd.split.y);
	sprite->SetPos(m_CharaPos);
	sprite->RenderAtlas(
		ct->GetTexture(),
		m_CharaAtlas.x,
		m_CharaAtlas.y
	);
	if (m_isBalloonRender) {

		auto bt = m_pBalloonTexture.lock();
		auto bd = am.GetBalloonData();
		sprite->SetSpriteSize(bd.size.x, bd.size.y);
		sprite->SetSizeScaling(bd.scale);
		sprite->SetSplit(bd.split.x, bd.split.y);
		sprite->SetPos(m_BalloonPos);
		sprite->RenderAtlas(
			bt->GetTexture(),
			m_BalloonAtlas.x,
			m_BalloonAtlas.y
		);

	}
	

}

void PlayerWait::Init()
{
	SetPlayer();
}

ActionBase* PlayerWait::Update()
{
	return this;
}

void OwnerWait::Init()
{
	SetOwner();
}

ActionBase* OwnerWait::Update()
{
	return this;
}

void PlayerStep::Init()
{
	SetPlayer();
	m_changeCnt = 12;
}

ActionBase* PlayerStep::Update()
{
	cnt++;
	if (cnt % m_changeCnt == 0) {
		m_CharaAtlas.x = m_CharaAtlas.x == 0 ? 2 : 0;
	}

	return this;
}

void OwnerStep::Init()
{
	SetOwner();
	m_changeCnt = 12;
}

ActionBase * OwnerStep::Update()
{
	cnt++;
	if (cnt % m_changeCnt == 0) {
		m_CharaAtlas.x = m_CharaAtlas.x == 0 ? 2 : 0;
	}
	return this;
}

void PlayerWord::Init()
{
	SetPlayer();
	m_changeCnt = 12;
	m_isBalloonRender = true;
	m_BalloonAtlas.x = 1;
	m_BalloonAtlas.y = 7;
}

ActionBase * PlayerWord::Update()
{
	cnt++;
	if (cnt%m_changeCnt == 0) {
		m_BalloonAtlas.x = m_BalloonAtlas.x == 7 ? 1 : ++m_BalloonAtlas.x;
	}
	return this;
}

void PlayerJump::Init()
{
	SetPlayer();
	height = 60;
	rad = 0;
}

ActionBase * PlayerJump::Update()
{
	rad += 0.35f;

	m_CharaPos = c_basePos - D3DXVECTOR2(c_betweenLength, 0);
	float mag = sin(rad);
	if (mag < 0) { mag = 0; }
	m_CharaPos.y -= mag * height;

	return this;
}

void OwnerJump::Init()
{
	SetOwner();
	height = 30;
	rad = 0;
}

ActionBase * OwnerJump::Update()
{
	rad += 0.3f;

	m_CharaPos = c_basePos + D3DXVECTOR2(c_betweenLength, 0);
	float mag = sin(rad);
	if (mag < 0) { mag = 0; }
	m_CharaPos.y -= mag * height;

	return this;
}

void OwnerAngry::Init()
{
	SetOwner();
	m_changeCnt = 8;
	m_isBalloonRender = true;
	m_BalloonAtlas.x = 1;
	m_BalloonAtlas.y = 4;
}

ActionBase * OwnerAngry::Update()
{
	cnt++;
	if (cnt%m_changeCnt == 0) {
		m_BalloonAtlas.x = m_BalloonAtlas.x == 7 ? 2 : ++m_BalloonAtlas.x;
	}
	return this;
}

void PlayerWorry::Init()
{
	SetPlayer();
	m_changeCnt = 8;
	m_isBalloonRender = true;
	m_BalloonAtlas.x = 1;
	m_BalloonAtlas.y = 6;
}

ActionBase * PlayerWorry::Update()
{
	cnt++;
	if (cnt%m_changeCnt == 0) {
		m_BalloonAtlas.x = m_BalloonAtlas.x == 7 ? 2 : ++m_BalloonAtlas.x;
	}
	return this;
}

void PlayerCry::Init()
{
	SetPlayer();
	m_changeCnt = 8;
	m_isBalloonRender = true;
	m_BalloonAtlas.x = 1;
	m_BalloonAtlas.y = 5;
}

ActionBase * PlayerCry::Update()
{
	cnt++;
	if (cnt%m_changeCnt == 0) {
		m_BalloonAtlas.x = m_BalloonAtlas.x == 7 ? 2 : ++m_BalloonAtlas.x;
	}
	return this;
}
