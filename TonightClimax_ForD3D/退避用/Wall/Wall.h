#pragma once
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include <DirectXMath.h>
#include <memory>
#include "../Tile/Tile.h"

class UpWall
{
public:
	UpWall() {};
	~UpWall() {};
	void Init();
	void Render();
private:
	std::unique_ptr<Texture>	m_pLWallTex;
	std::unique_ptr<Texture>	m_pRWallTex;
	std::unique_ptr<Texture>	m_pMWallTex;
	std::unique_ptr<Sprite>		m_pSprite;


	static constexpr DirectX::XMFLOAT2 c_ImageSize = { 48,144 };
	static constexpr int c_Num = static_cast<int>(Tile::c_Num.x*(Tile::c_ImageSize.x / c_ImageSize.x));
	static constexpr float c_Scale = Tile::c_Scale;

	DirectX::XMFLOAT2 ConvertPos(int x);
};

class LeftWall
{
public:
	LeftWall() {};
	~LeftWall() {};
	void Init();
	void Render();
private:
	std::unique_ptr<Texture>	m_pUWallTex;
	std::unique_ptr<Texture>	m_pMWallTex;
	std::unique_ptr<Texture>	m_pDWallTex;
	std::unique_ptr<Sprite>		m_pSprite;


	static constexpr DirectX::XMFLOAT2 c_ImageSize = { 48,144 };
	static constexpr float c_Scale = Tile::c_Scale;
};

class DownWall {
public:
	DownWall() {};
	~DownWall() {};
	void Init();
	void Render();
private:
	std::unique_ptr<Texture>	m_pLWallTex;
	std::unique_ptr<Texture>	m_pRWallTex;
	std::unique_ptr<Texture>	m_pMWallTex;
	std::unique_ptr<Sprite>		m_pSprite;

	static constexpr DirectX::XMFLOAT2 c_ImageSize = { 48,48 };
	static constexpr int c_Num = static_cast<int>(Tile::c_Num.x*(Tile::c_ImageSize.x / c_ImageSize.x));
	static constexpr float c_Scale = Tile::c_Scale;

	DirectX::XMFLOAT2 ConvertPos(int x);

};

class RightWall
{
public:
	RightWall() {};
	~RightWall() {};
	void Init();
	void Render();
private:
	std::unique_ptr<Texture>	m_pUWallTex;
	std::unique_ptr<Texture>	m_pMWallTex;
	std::unique_ptr<Texture>	m_pDWallTex;
	std::unique_ptr<Sprite>		m_pSprite;


	static constexpr DirectX::XMFLOAT2 c_ImageSize = { 48,144 };
	static constexpr float c_Scale = Tile::c_Scale;
};