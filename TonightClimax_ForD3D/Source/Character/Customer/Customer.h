#pragma once
#include "../ICharacter.h"
#include "../../Sprite/Sprite.h"
#include "../../Texture/Texture.h"
#include <memory>
#include <DirectXMath.h>

class Customer final
	:public ICharacter
{
public:
	Customer();
	~Customer();

	void ICharacter::Init();
	void ICharacter::Update();
	void ICharacter::Render();
	void Move(DirectX::XMFLOAT2 vec)override;
	void MoveFinish(DirectX::XMINT2 dir)override;

	void SetSpriteWP(std::shared_ptr<Sprite> sprite) { m_pSprite = sprite; }
	void SetTextureWP(std::shared_ptr<Texture> texture) { m_pTex = texture; }
	void SetComp(DirectX::XMFLOAT2 comp) { m_Comp = comp; }
	void SetSplit(DirectX::XMINT2 split) { m_SplitNum = split; }
	void SetLTIndex(DirectX::XMINT2 ltIndex) { m_ltIndex = ltIndex; }
	void SetInitAtlasIndex(DirectX::XMINT2 index) { m_InitAtlasIndex = index; }

private:
	void SetSquare();

	std::weak_ptr<Sprite>m_pSprite;
	std::weak_ptr<Texture>m_pTex;
	DirectX::XMFLOAT2 m_Comp;
	DirectX::XMINT2 m_SplitNum;
	DirectX::XMINT2 m_AtlasIndex;
	DirectX::XMINT2 m_InitAtlasIndex;
};

