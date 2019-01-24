#pragma once
#include "../Singleton.h"
#include <DirectXMath.h>
#include <memory>
#include "../Tile/Tile.h"
#include "../Wall/Wall.h"
#include "../Table/Tables.h"
#include <vector>

struct Square
{
	DirectX::XMINT2 index;
	int info;
};

class Board
	:public Singleton<Board>
{
public:
	Board();
	~Board();

	void Init();
	void Render();
	void Load();
	Square*GetSquare(DirectX::XMINT2 index);

	//	マップチップのサイズ
	static const DirectX::XMFLOAT2 c_ChipSize;

	//	拡大縮小の倍率
	static const float c_Scale;

	//	画面の基準点(画面の中心)
	static const DirectX::XMFLOAT2 c_Pivot;

	//	縦横に敷き詰めるマップチップの数(正方形のためxとyで同じ値を使用)
	static const DirectX::XMINT2 c_ChipNum;


	//	1マスの大きさ
	DirectX::XMFLOAT2 GetSquareSize() { return { c_ChipSize.x * c_Scale, c_ChipSize.y * c_Scale }; }

	//	左上
	DirectX::XMFLOAT2 GetLeftTop();

	//	インデックスをその座標の中心に変換
	DirectX::XMFLOAT2 ConvertSquareCenter(DirectX::XMINT2 index);

	enum Info :int{
		EMPTY		= 0,	// 通路
		OBJECT		= 1,	// オブジェクト
		CUSTOMER	= 2,	// 客
	};

private:
	friend class Singleton<Board>;

	std::unique_ptr<Tile>m_pTile;
	std::unique_ptr<UpWall>m_pUWall;
	std::unique_ptr<LeftWall>m_pLWall;
	std::unique_ptr<DownWall>m_pDWall;
	std::unique_ptr<RightWall>m_pRWall;
	std::unique_ptr<Tables>m_pTable;

	std::vector<Square>m_Square;
};

