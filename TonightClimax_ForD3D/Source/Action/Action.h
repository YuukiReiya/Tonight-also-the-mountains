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

//	�ҋ@ Player
class PlayerWait
	:public ActionBase
{
public:
	void Init()override;
	ActionBase* Update()override;
};

//	�ҋ@ Owner
class OwnerWait
	:public ActionBase
{
public:
	void Init()override;
	ActionBase* Update()override;
};

//	������ Player
class PlayerStep 
	:public ActionBase
{
public:
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	������ Owner
class OwnerStep 
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;

};

//	�ꂭ Player
class PlayerWord
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	�ꂭ Owner

//	�W�����v Player
class PlayerJump
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	float height;
	float rad;
};

//	�W�����v Owner
class OwnerJump
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	float height;
	float rad;
};

//	�{�� Owner
class OwnerAngry
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	�Y�� Player
class PlayerWorry
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};

//	���� Player
class PlayerCry
	:public ActionBase
{
	void Init()override;
	ActionBase* Update()override;
private:
	int m_changeCnt;
};