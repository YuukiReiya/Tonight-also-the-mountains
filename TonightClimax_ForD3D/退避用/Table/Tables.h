#pragma once
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include "../Tile/Tile.h"
#include <memory>
#include <DirectXMath.h>

class Tables
{
public:
	Tables();
	~Tables();

	void Init();
	void Render();
private:
	std::unique_ptr<Sprite>m_pTableSprite;
	std::unique_ptr<Sprite>m_pChairSprite;
	std::unique_ptr<Texture>m_pTableTexture;
	std::unique_ptr<Texture>m_pChairTexture;

	static constexpr DirectX::XMFLOAT2 c_ImageSize{ 48,48 };
	static constexpr float c_Scale = Tile::c_Scale*Tile::c_Scale;
};

