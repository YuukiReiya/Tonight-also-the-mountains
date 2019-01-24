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


	//	1つの表示に何マス使うか(比率 = x:y)
	static const DirectX::XMINT2 c_Comp;
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
	std::unique_ptr<Texture>	m_pEntranceTex;
	std::unique_ptr<Sprite>		m_pSprite;
};