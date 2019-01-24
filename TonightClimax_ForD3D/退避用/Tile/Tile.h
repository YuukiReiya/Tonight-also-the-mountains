#pragma once
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include <DirectXMath.h>
#include <memory>

class Tile
{
public:
	Tile();
	~Tile();

	void Init();
	void Render();

	static DirectX::XMFLOAT2 GetBasicPos();
	static constexpr DirectX::XMINT2 c_Num = { 6,3 };
	static constexpr DirectX::XMFLOAT2 c_ImageSize = { 96,144 };
	static constexpr float c_Scale = 1.5f;
private:

	DirectX::XMFLOAT2 ConevrtPos(int x,int y);

	std::unique_ptr<Texture>m_pTex;
	std::unique_ptr<Sprite>	m_pSprite;


	static const std::string c_FilePath; 
};

