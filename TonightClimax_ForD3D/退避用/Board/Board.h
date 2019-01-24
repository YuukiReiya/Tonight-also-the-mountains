#pragma once
#include "../Singleton.h"
#include <DirectXMath.h>
#include <memory>
#include "../Tile/Tile.h"
#include "../Wall/Wall.h"
#include "../Table/Tables.h"

class Board
	:public Singleton<Board>
{
public:
	Board();
	~Board();

	void Init();
	void Render();

	//	
	static constexpr DirectX::XMFLOAT2 c_SquareSize = { 48,48 };

	//	‰æ–Ê‚ÌŠî€“_(‰æ–Ê‚Ì’†S)
	static constexpr DirectX::XMFLOAT2 c_Pivot = { 
		static_cast<float>(1920) / 2,
		static_cast<float>(1080) / 2 -100
	};
	
private:
	friend class Singleton<Board>;

	std::unique_ptr<Tile>m_pTile;
	std::unique_ptr<UpWall>m_pUWall;
	std::unique_ptr<LeftWall>m_pLWall;
	std::unique_ptr<DownWall>m_pDWall;
	std::unique_ptr<RightWall>m_pRWall;
	std::unique_ptr<Tables>m_pTable;
};

