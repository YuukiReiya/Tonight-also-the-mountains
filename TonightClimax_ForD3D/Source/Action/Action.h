#pragma once
#include "ActionManager.h"

class ActionBase 
{
protected:
	int cnt;
	std::weak_ptr<Sprite>	m_pSprite;
	std::weak_ptr<Texture>	m_pCharacterTexture;
	std::weak_ptr<Texture>	m_pBalloonTexture;

	bool m_isBalloonRender;
	D3DXVECTOR2 m_CharaPos;
	D3DXVECTOR2 m_BalloonPos;
	DirectX::XMINT2 m_CharaAtlas;
	DirectX::XMINT2 m_BalloonAtlas;

	static const D3DXVECTOR2 c_basePos;
	static const D3DXVECTOR2 c_balloonOffset;
	static const float c_betweenLength;
	void SetPlayer();
	void SetOwner();
public:
	virtual void Init()abstract;
	virtual ActionBase* Update()abstract;
	void Render();

};

//	待機 Player
class PlayerWait
	:public ActionBase
{
public:
	void Init()override;
	ActionBase* Update()override;
};

//	待機 Owner
class OwnerWait
	:public ActionBase
{
public:
	void Init()override;
	ActionBase* Update()override;
};

//	足踏み Player
class PlayerStep 
	:public ActionBase
{
public:
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	足踏み Owner
class OwnerStep 
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;

};

//	呟く Player
class PlayerWord
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	呟く Owner

//	ジャンプ Player
class PlayerJump
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	float height;
	float rad;
};

//	ジャンプ Owner
class OwnerJump
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	float height;
	float rad;
};

//	怒る Owner
class OwnerAngry
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	悩む Player
class PlayerWorry
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	泣く Player
class PlayerCry
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};