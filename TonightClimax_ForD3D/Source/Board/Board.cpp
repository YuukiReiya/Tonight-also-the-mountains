#include "Board.h"
#include "../MyGame.h"
#include "../Debug/DebugDraw.h"
#include "../CSV/CSVReader.h"
#include <algorithm>

using namespace std;
using namespace DirectX;

const XMFLOAT2 Board::c_ChipSize{ 
	48,
	48
};

const XMFLOAT2 Board::c_Pivot{
		static_cast<float>(1920) / 2,
		static_cast<float>(1080) / 2
};


const XMINT2 Board::c_ChipNum{ 13,10 };


const float Board::c_Scale = 1.3f;

Board::Board()
{
}


Board::~Board()
{
}

void Board::Init()
{
	m_pTile = make_unique<Tile>();
	m_pUWall = make_unique<UpWall>();
	m_pLWall = make_unique<LeftWall>();
	m_pDWall = make_unique<DownWall>();
	m_pRWall = make_unique<RightWall>();
	m_pTable= make_unique<Tables>();

	m_pTile->Init();
	m_pUWall->Init();
	m_pLWall->Init();
	m_pDWall->Init();
	m_pRWall->Init();
	m_pTable->Init();

	m_Square.clear();
	Load();

	DebugDraw::GetInstance().Init();
}

#define Rendering
#define detailed
void Board::Render()
{
	m_pTile->Render();
	m_pRWall->Render();
	m_pUWall->Render();
	m_pLWall->Render();
	m_pDWall->Render();
	m_pTable->Render();
	//ƒ}ƒX‚ÌƒŒƒ“ƒ_ƒŠƒ“ƒO
#ifdef Rendering
	auto& drawer = DebugDraw::GetInstance();
	for (int y = 0; y < c_ChipNum.y; ++y) {
		for (int x = 0; x < c_ChipNum.x; ++x) {


			XMFLOAT2 size = GetSquareSize();

			//	[0][0]‚Ì”Âƒ|ƒŠƒSƒ“¶ã
			XMFLOAT2 pos = c_Pivot;
			pos.x -= size.x*c_ChipNum.x / 2;
			pos.y -= size.y*c_ChipNum.y / 2;

			//	[0][0]‚Ì”Âƒ|ƒŠƒSƒ“’†S
			pos.x += size.x / 2;
			pos.y += size.y / 2;

			//	ˆÈ~
			pos.x += size.x * x;
			pos.y += size.y * y;

			D3DXVECTOR2 vPos{ pos.x,pos.y };
			drawer.DrawSquare(vPos, size.x, size.y);


#ifdef detailed


			//	1/4
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {

					pos = GetLeftTop();

					//	ˆÈ~
					pos.x += size.x * x;
					pos.y += size.y * y;

					//	¶ã
					pos.x += size.x / 4;
					pos.y += size.y / 4;

					//	ˆÈ~
					pos.x += size.x / 2 * j;
					pos.y += size.y / 2 * i;

					vPos = { pos.x,pos.y };
					drawer.DrawSquare(vPos, size.x / 2, size.y / 2, drawer.BLUE);
				}
			}
#endif // detailed
		}
	}
#endif
}

void Board::Load()
{
	for (int y = 0; y < c_ChipNum.y * 2; y++) {
		for (int x = 0; x < c_ChipNum.x * 2; x++) {
			Square data;
			data.index = { x,y };
			m_Square.push_back(data);
		}
	}

	auto& csv = CSVReader::GetInstance();
	csv.Load("../Resource/csv/Board.csv");
	auto cells = csv.GetCells();

	const XMINT2 c_DataOffset = { 1,3 };
	for (int y = 0; y < c_ChipNum.y * 2; y++) {
		for (int x = 0; x < c_ChipNum.x * 2; x++) {

			auto data = atoi(cells[c_DataOffset.y + y][c_DataOffset.x + x].c_str());

			auto it = std::find_if(m_Square.begin(), m_Square.end(),
				[&](Square& d) {return(d.index.x == x && d.index.y == y);
			});
			if (it != m_Square.end()) {
				auto& ref = m_Square[(it - m_Square.begin())];
				ref.info = data;
			}
		}
	}

}

Square * Board::GetSquare(DirectX::XMINT2 index)
{
		auto it= std::find_if(m_Square.begin(), m_Square.end(),
			[&](Square& d) {return(d.index.x == index.x && d.index.y == index.y);
		});
		if (it != m_Square.end()) {
			return &m_Square[(it - m_Square.begin())];
		}
		return nullptr;
}

DirectX::XMFLOAT2 Board::GetLeftTop()
{
	XMFLOAT2 ret = Board::c_Pivot;
	ret.x -= GetSquareSize().x*(float)(Board::c_ChipNum.x) / 2;
	ret.y -= GetSquareSize().y*(float)(Board::c_ChipNum.y) / 2;
	return ret;
}

DirectX::XMFLOAT2 Board::ConvertSquareCenter(XMINT2 index)
{
	auto pos = GetLeftTop();
	pos.x += GetSquareSize().x / 2;
	pos.y += GetSquareSize().y / 2;

	pos.x += index.x * GetSquareSize().x / 2;
	pos.y += index.y * GetSquareSize().y / 2;

	return pos;
}

