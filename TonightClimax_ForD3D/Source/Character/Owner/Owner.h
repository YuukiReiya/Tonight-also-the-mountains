#pragma once
#include "../ICharacter.h"
#include "../../Sprite/Sprite.h"
#include "../../Texture/Texture.h"
#include <memory>
#include <DirectXMath.h>
#include <vector>

class Owner final
	:public ICharacter 
{
public:
	Owner();
	~Owner();


	void ICharacter::Init();
	void ICharacter::Update();
	void ICharacter::Render();
	void Move(DirectX::XMFLOAT2 vec)override;
private:
	void MoveFinish(DirectX::XMINT2 dir)override {}
	DirectX::XMINT2 GetNextDir();

	std::unique_ptr<Sprite>m_pSprite;
	std::unique_ptr<Texture>m_pTexture;

	static const std::string		c_FilePath;
	static const DirectX::XMINT2	c_SplitNum;
	static const DirectX::XMINT2	c_ltInitIndex;

	DirectX::XMFLOAT2	m_NextPos;
	DirectX::XMINT2		m_ltIndex;
	DirectX::XMINT2		m_Dir;
	bool m_isMoving;
	std::vector<DirectX::XMINT2>m_MoveDirList;
};

