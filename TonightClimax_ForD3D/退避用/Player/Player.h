#pragma once
#include "../Texture/Texture.h"
#include "../Sprite/Sprite.h"
#include <memory>
#include <DirectXMath.h>
#include "../Tile/Tile.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
private:

	static constexpr DirectX::XMINT2 c_SplitNum = { 3,4 };
	static const int c_ImageSize = 48;
	static constexpr float c_Scale = Tile::c_Scale;
	static const std::string c_FilePath;

	std::unique_ptr<Sprite>m_pSprite;
	std::unique_ptr<Texture>m_pTex;
};

