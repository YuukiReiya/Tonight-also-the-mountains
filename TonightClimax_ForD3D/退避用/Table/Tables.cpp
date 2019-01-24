#include "Tables.h"
#include "../Board/Board.h"

using namespace std;
using namespace DirectX;

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
	m_pTableSprite->SetSpriteSize(c_ImageSize.x,c_ImageSize.y);
	m_pTableSprite->SetSizeScaling(c_Scale);
}

void Tables::Render()
{
	XMINT2 num{ 3,3 };

	const XMFLOAT2 offset{ 
		48 * Tile::c_Scale,48*Tile::c_Scale/2
	};
	const XMFLOAT2 interval{
		288,
		216
	};


	for (size_t i = 0; i < num.y; ++i) {

		for (size_t j = 0; j < num.x; ++j) {

			auto pos = Tile::GetBasicPos();

			pos.x += offset.x + j * interval.x;
			pos.y += offset.y + i * interval.y;
			D3DXVECTOR2 vPos = { pos.x,pos.y };
			m_pTableSprite->SetPos(vPos);
			m_pTableSprite->Render(m_pTableTexture->GetTexture());
		}

	}


}

