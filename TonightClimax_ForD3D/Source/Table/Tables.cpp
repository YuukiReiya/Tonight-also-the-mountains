#include "Tables.h"
#include "../Board/Board.h"

using namespace std;
using namespace DirectX;

const XMINT2 Tables::c_Num = { 3,3 };
const XMINT2 Tables::c_IntervalSquareNum{ 8,6 };

const float Tables::c_Mag = 1.4f;

Tables::Tables()
{
}


Tables::~Tables()
{
}

void Tables::Init()
{
	m_pTableSprite = make_unique<Sprite>();
	m_pTableTexture = make_unique<Texture>();
	m_pTableTexture->Load("../Resource/Image/A2-asinaga.png");
	m_pTableSprite->SetSpriteSize(Board::c_ChipSize.x, Board::c_ChipSize.y);
	m_pTableSprite->SetSizeScaling(Board::c_Scale*c_Mag);

	m_pChairSprite = make_unique<Sprite>();
	m_pChairTexture = make_unique<Texture>();
	m_pChairTexture->Load("../Resource/Image/chair.png");
	m_pChairSprite->SetSpriteSize(Board::c_ChipSize.x, Board::c_ChipSize.y);
	m_pChairSprite->SetSizeScaling(Board::c_Scale);
}

void Tables::Render()
{
	auto&board = Board::GetInstance();
	D3DXVECTOR2 vPos;

	XMINT2 offset = {
		4,
		3 
	};

	//	テーブル
	for (int y = 0; y < c_Num.y; ++y) {
		for (int x = 0; x < c_Num.x; ++x) {
			auto tmp = board.ConvertSquareCenter({ offset.x + x * c_IntervalSquareNum.x,offset.y + y * c_IntervalSquareNum.y });
			vPos = { tmp.x,tmp.y };
			m_pTableSprite->SetPos(vPos);
			m_pTableSprite->Render(m_pTableTexture->GetTexture());
		}
	}

	//	椅子
	for (int y = 0; y < c_Num.y; ++y) {
		for (int x = 0; x < c_Num.x; ++x) {

			//	左
			auto tmp = board.ConvertSquareCenter({ offset.x + x * c_IntervalSquareNum.x,offset.y + y * c_IntervalSquareNum.y });
			vPos = { tmp.x,tmp.y };
			vPos.x -= board.GetSquareSize().x;
			m_pChairSprite->SetPos(vPos);
			m_pChairSprite->Render(m_pChairTexture->GetTexture());

			//	右
			tmp = board.ConvertSquareCenter({ offset.x + x * c_IntervalSquareNum.x,offset.y + y * c_IntervalSquareNum.y });
			vPos = { tmp.x,tmp.y };
			vPos.x += board.GetSquareSize().x;
			m_pChairSprite->SetPos(vPos);
			m_pChairSprite->Render(m_pChairTexture->GetTexture());

		}
	}
}

