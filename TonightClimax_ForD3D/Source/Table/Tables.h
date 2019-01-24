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

	//	テーブルの配置間隔
	static const DirectX::XMINT2 c_IntervalSquareNum;
	static const DirectX::XMINT2 c_Num;
	static const float c_Mag;
};

