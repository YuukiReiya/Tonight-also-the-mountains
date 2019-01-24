#include "Tile.h"
#include "../Board/Board.h"
#include "../Debug/DebugDraw.h"

using namespace std;
using namespace DirectX;

const string Tile::c_FilePath = "../Resource/Image/inhouse_tile.png";

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
	m_pSprite->SetSpriteSize(c_ImageSize.x, c_ImageSize.y);
	m_pSprite->SetSizeScaling(c_Scale);
}

void Tile::Render()
{
	for (int y = 0; y < c_Num.y; ++y) {
		for (int x = 0; x < c_Num.x; ++x) {

			auto pos = ConevrtPos(x, y);
			D3DXVECTOR2 vPos = { pos.x,pos.y };
			m_pSprite->SetPos(vPos);
			m_pSprite->Render(m_pTex->GetTexture());
			float w, h;
			w = c_ImageSize.x*c_Scale;
			h = c_ImageSize.y*c_Scale;
			DebugDraw::GetInstance().DrawSquare(vPos, w, h, DebugDraw::RED);

			w /= 2;
			h /= 3;
			for (int iy = 0; iy < 3; ++iy) {
				for (int ix = 0; ix < 2; ++ix)
				{
					vPos = { pos.x,pos.y };
					//	��_
					vPos.x -= c_ImageSize.x*c_Scale / 2;
					vPos.y -= c_ImageSize.y*c_Scale / 2;

					//	���W
					vPos.x += w / 2;
					vPos.y += h / 2;

					//	�I�t�Z�b�g
					vPos.x += w * ix;
					vPos.y += h * iy;

					DebugDraw::GetInstance().DrawSquare(vPos, w, h, DebugDraw::BLUE);
				}
			}
		}


	}

	//XMFLOAT2 pos = { 768,540 };
	//		D3DXVECTOR2 vPos = { pos.x,pos.y };
	//		m_pSprite->SetPos(vPos);
	//		m_pSprite->Render(m_pTex->GetTexture());

	//		pos = { 960,540 };
	//		vPos = { pos.x,pos.y };
	//		m_pSprite->SetPos(vPos);
	//		m_pSprite->Render(m_pTex->GetTexture());
}

DirectX::XMFLOAT2 Tile::GetBasicPos()
{
	XMFLOAT2 ret = Board::c_Pivot;
	XMFLOAT2 length, offset;
	//------------------------------------------------------------
	//	���̍���Z�o
	length.x = (c_ImageSize.x*c_Scale*c_Num.x);
	length.y = (c_ImageSize.y*c_Scale*c_Num.y);
	offset.x = c_ImageSize.x*c_Scale / 2;
	offset.y = c_ImageSize.y*c_Scale / 2;
	ret.x -= (length.x / 2) - offset.x;
	ret.y -= (length.y / 2) - offset.y;
	//------------------------------------------------------------

	return ret;
}

DirectX::XMFLOAT2 Tile::ConevrtPos(int x, int y)
{
	XMFLOAT2 ret = Board::c_Pivot;

	XMFLOAT2 length,offset;

	//	����
	length.x = (c_ImageSize.x*c_Scale*c_Num.x);
	length.y = (c_ImageSize.y*c_Scale*c_Num.y);

	//	�I�t�Z�b�g
	offset.x = c_ImageSize.x*c_Scale / 2;
	offset.y = c_ImageSize.y*c_Scale / 2;

	//	�߂�l
	ret.x -= (length.x / 2) - offset.x;
	ret.y -= (length.y / 2) - offset.y;

	//	�Y����
	ret.x += x * offset.x * 2;
	ret.y += y * offset.y * 2;

	return ret;
}
