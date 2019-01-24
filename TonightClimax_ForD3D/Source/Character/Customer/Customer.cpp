#include "Customer.h"
#include "../../Board/Board.h"

using namespace std;
using namespace DirectX;

Customer::Customer()
{
}


Customer::~Customer()
{
}

void Customer::Move(DirectX::XMFLOAT2 vec)
{
	m_CharaPos.x += vec.x;
	m_CharaPos.y += vec.y;

	//	丸め補正の計算

}

void Customer::MoveFinish(DirectX::XMINT2 dir)
{
	XMINT2 index = m_ltIndex;
	auto&bd = Board::GetInstance();

	//	正方向と負方向で計算が違う
	bool isPositive = (dir.x+dir.y) > 0;

	//	正(右もしくは下)
	if (isPositive) {

		for (int y = 0; y < 2; ++y) {

			for (int x = 0; x < 2; ++x) {
			
				//	現在のインデックス
				index = m_ltIndex;
				index.x += 1 - x;
				index.y += 1 - y;
				auto now = bd.GetSquare(index);

				//	移動先
				index.x += dir.x;
				index.y += dir.y;
				auto next = bd.GetSquare(index);
				if (next == nullptr) { break; }
				auto tmp = next->info;

				//	入れ替え
				next->info = now->info;
				now->info = tmp;
			}
		}
	}
	//	負(左もしくは上)
	else {
		
		for (int y = 0; y < 2; ++y) {

			for (int x = 0; x < 2; ++x) {

				//	現在のインデックス
				index = m_ltIndex;
				index.x += x;
				index.y += y;
				auto now = bd.GetSquare(index);

				//	移動先
				index.x += dir.x;
				index.y += dir.y;
				auto next = bd.GetSquare(index);
				if (next != nullptr) {

					auto tmp = next->info;

					//	入れ替え
					//next->info = now->info;
					//now->info = tmp;

					next->info = Board::EMPTY;
					now->info= Board::EMPTY;
				}
				else {
					//now->info = Board::EMPTY;
					now->info = Board::EMPTY;
				}
			}
		}
	}

	//	インデックス更新
	m_ltIndex.x += dir.x;
	m_ltIndex.y += dir.y;

	SetSquare();
	m_CharaPos = bd.ConvertSquareCenter(m_ltIndex);
}


void Customer::SetSquare()
{
	auto&bd = Board::GetInstance();

	const XMINT2 index[] = {
		{m_ltIndex},
		{m_ltIndex.x + 1,m_ltIndex.y},
		{m_ltIndex.x,m_ltIndex.y + 1},
		{m_ltIndex.x + 1,m_ltIndex.y + 1},
	};

	for (auto it : index) {

		auto square = bd.GetSquare(it);
		if (square == nullptr) { continue; }
		square->info = Board::CUSTOMER;
	}
}

void Customer::Init() 
{
	auto&bd = Board::GetInstance();
	SetSquare();
	m_CharaPos = bd.ConvertSquareCenter(m_ltIndex);
	m_AtlasIndex = m_InitAtlasIndex;
}

void Customer::Update() 
{

}

void Customer::Render()
{
	//	weak_ptrの参照がされていない
	if (m_pSprite.expired() || m_pTex.expired()) {
		return;
	}

	D3DXVECTOR2 pos = { m_CharaPos.x,m_CharaPos.y };

	auto sprite_ptr = m_pSprite.lock();
	auto textire_ptr = m_pTex.lock();
	
	
	sprite_ptr->SetSpriteSize(Board::c_ChipSize.x*m_Comp.x, Board::c_ChipSize.y*m_Comp.y);
	sprite_ptr->SetSplit(m_SplitNum.x, m_SplitNum.y);
	sprite_ptr->SetSizeScaling(Board::c_Scale);
	sprite_ptr->SetPos(pos);

	sprite_ptr->RenderAtlas(
		textire_ptr->GetTexture(), 
		m_AtlasIndex.x, 
		m_AtlasIndex.y
	);
}