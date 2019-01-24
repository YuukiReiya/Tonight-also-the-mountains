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
private:

	//	1つの表示に何マス使うか(比率 = x:y)
	static const DirectX::XMINT2 c_Comp;
	DirectX::XMFLOAT2 ConevrtPos(int x,int y);

	std::unique_ptr<Texture>m_pTex;
	std::unique_ptr<Sprite>	m_pSprite;


	static const std::string c_FilePath; 
};

