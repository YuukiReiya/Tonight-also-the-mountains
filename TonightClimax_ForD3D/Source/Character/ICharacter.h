#pragma once
#include <DirectXMath.h>

class ICharacter
{
public:
	virtual void Init()abstract;
	virtual void Update()abstract;
	virtual void Render()abstract;
	virtual void Move(DirectX::XMFLOAT2 velocity)abstract;
	virtual void MoveFinish(DirectX::XMINT2 dir)abstract;
	DirectX::XMINT2 GetLTIndex()const { return m_ltIndex; }
	DirectX::XMFLOAT2 GetPos()const { return m_CharaPos; }
protected:
	DirectX::XMINT2 m_ltIndex;
	DirectX::XMFLOAT2 m_CharaPos;
};

