#include "Tile.h"
#include "../Board/Board.h"
#include "../Debug/DebugDraw.h"

using namespace std;
using namespace DirectX;

const string Tile::c_FilePath = "../Resource/Image/inhouse_tile.png";
const XMINT2 Tile::c_Comp = { 2,3 };

Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::Init()
{
	m_pTex		= make_unique<Texture>();
	m_pSprite	= make_unique<Sprite>();

	m_pTex->Load(c_FilePath);
	XMFLOAT2 size = { Board::c_ChipSize };
	size.x *= c_Comp.x;
	size.y *= c_Comp.y;
	m_pSprite->SetSpriteSize(size.x, size.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);
}

void Tile::Render()
{
	//for (int y = 0; y < c_Num.y; ++y) {
	//	for (int x = 0; x < c_Num.x; ++x) {

	auto& board = Board::GetInstance();

	XMINT2 overlapNum,loopNum;
	XMFLOAT2 size = {
		board.GetSquareSize().x*c_Comp.x,
		board.GetSquareSize().y*c_Comp.y
	};

	//	重複分
	overlapNum.x = Board::c_ChipNum.x%c_Comp.x;	
	overlapNum.y = Board::c_ChipNum.y%c_Comp.y;	

	//	繰り返し
	loopNum.x = Board::c_ChipNum.x / c_Comp.x;
	loopNum.y = Board::c_ChipNum.y / c_Comp.y;

	//	左上頂点
	XMFLOAT2 basicPos = board.GetLeftTop();

	//	画像の中心座標
	basicPos.x += size.x / 2;
	basicPos.y += size.y / 2;

	D3DXVECTOR2 vPos = { basicPos.x,basicPos.y };

	//	重複分

	//	x
	if (overlapNum.x != 0) {

		for (int x = 0; x < loopNum.x; ++x) {

			m_pSprite->SetPos({ vPos.x + size.x*x,vPos.y });
			m_pSprite->Render(m_pTex->GetTexture());
		}
		m_pSprite->SetPos({ vPos.x + size.x *(loopNum.x - 1) + board.GetSquareSize().x,vPos.y });
		m_pSprite->Render(m_pTex->GetTexture());
	}

	//	y
	if (overlapNum.y != 0) {
		for (int y = 0; y < loopNum.y; ++y) {
			m_pSprite->SetPos({ vPos.x,vPos.y + size.y *y });
			m_pSprite->Render(m_pTex->GetTexture());
		}
		m_pSprite->SetPos({ vPos.x,vPos.y + size.y *(loopNum.y - 1) + board.GetSquareSize().y });
		m_pSprite->Render(m_pTex->GetTexture());
	}

	//	補正して描画
	for (int y = 0; y < loopNum.y; y++)
	{
		for (int x = 0; x < loopNum.x; x++)
		{
			vPos = { basicPos.x,basicPos.y };

			//	重複部分のオフセット
			vPos.x += board.GetSquareSize().x*overlapNum.x;
			vPos.y += board.GetSquareSize().y*overlapNum.y;

			//	以降
			vPos.x += x * size.x;
			vPos.y += y * size.y;

			m_pSprite->SetPos(vPos);
			m_pSprite->Render(m_pTex->GetTexture());
		}
	}
	
}

DirectX::XMFLOAT2 Tile::GetBasicPos()
{
	XMFLOAT2 ret = Board::c_Pivot;
	//XMFLOAT2 length, offset;
	//------------------------------------------------------------
	//	床の左上算出
	//length.x = (c_ImageSize.x*c_Scale*c_Num.x);
	//length.y = (c_ImageSize.y*c_Scale*c_Num.y);
	//offset.x = c_ImageSize.x*c_Scale / 2;
	//offset.y = c_ImageSize.y*c_Scale / 2;
	//ret.x -= (length.x / 2) - offset.x;
	//ret.y -= (length.y / 2) - offset.y;
	//------------------------------------------------------------

	return ret;
}

DirectX::XMFLOAT2 Tile::ConevrtPos(int x, int y)
{
	XMFLOAT2 ret = Board::c_Pivot;

	//XMFLOAT2 length,offset;

	////	長さ
	//length.x = (c_ImageSize.x*c_Scale*c_Num.x);
	//length.y = (c_ImageSize.y*c_Scale*c_Num.y);

	////	オフセット
	//offset.x = c_ImageSize.x*c_Scale / 2;
	//offset.y = c_ImageSize.y*c_Scale / 2;

	////	戻り値
	//ret.x -= (length.x / 2) - offset.x;
	//ret.y -= (length.y / 2) - offset.y;

	////	添字分
	//ret.x += x * offset.x * 2;
	//ret.y += y * offset.y * 2;

	return ret;
}
