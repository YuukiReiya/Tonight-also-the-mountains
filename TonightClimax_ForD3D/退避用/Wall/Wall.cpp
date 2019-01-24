#include "Wall.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../Board/Board.h"
#include <iostream>

using namespace std;
using namespace DirectX;

void UpWall::Init()
{
	m_pSprite = make_unique<Sprite>();

	//	��
	m_pLWallTex = make_unique<Texture>();
	m_pLWallTex->Load("../Resource/Image/LUWall.png");

	//	��
	m_pMWallTex = make_unique<Texture>();
	m_pMWallTex->Load("../Resource/Image/MUWall.png");

	//	�E
	m_pRWallTex = make_unique<Texture>();
	m_pRWallTex->Load("../Resource/Image/RUWall.png");


	m_pSprite->SetSpriteSize(c_ImageSize.x, c_ImageSize.y);
	m_pSprite->SetSizeScaling(c_Scale);
}

void UpWall::Render()
{
	//	��
	{
		auto pos = Tile::GetBasicPos();

		pos.x -= Tile::c_ImageSize.x*Tile::c_Scale / 2;
		pos.y -= Tile::c_ImageSize.y*Tile::c_Scale / 2;

		pos.x += c_ImageSize.x*c_Scale / 2;
		pos.y -= c_ImageSize.y*c_Scale / 6;

		D3DXVECTOR2 vPos = { pos.x,pos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pLWallTex->GetTexture());
	}

	//	�E
	{
		auto pos = Tile::GetBasicPos();
		pos.x -= c_ImageSize.x*c_Scale / 2;
		pos.x += (c_Num - 1)*c_ImageSize.x*c_Scale;
		pos.y -= Tile::c_ImageSize.y*Tile::c_Scale / 2;
		pos.y -= c_ImageSize.y*c_Scale / 6;

		D3DXVECTOR2 vPos = { pos.x,pos.y };
		m_pSprite->SetPos(vPos);
	//	m_pSprite->Render(m_pRWallTex->GetTexture());
	}

	//	��
	for (int i = 1; i < c_Num - 1; ++i) {

		auto pos = ConvertPos(i);
		D3DXVECTOR2 vPos = { pos.x,pos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}

}

DirectX::XMFLOAT2 UpWall::ConvertPos(int x)
{
	auto ret = Tile::GetBasicPos();
	XMFLOAT2 offset;

	//	���W����
	offset.x = c_ImageSize.x*c_Scale;
	offset.y = c_ImageSize.y*c_Scale;

	//	�Y����
	ret.x += x * offset.x;
	ret.x -= offset.x / 2;
	ret.y -= offset.y / 2;

	//	�摜�̃Y��(35px)
	const float pxGap = 60 * c_Scale;
	ret.y -= pxGap;
	return ret;
}

void LeftWall::Init()
{
	m_pSprite = make_unique<Sprite>();

	//	��
	m_pUWallTex = make_unique<Texture>();
	m_pUWallTex->Load("../Resource/Image/ULWall.png");

	//	��
	m_pMWallTex = make_unique<Texture>();
	m_pMWallTex->Load("../Resource/Image/MLWall.png");

	//	��
	m_pDWallTex = make_unique<Texture>();
	m_pDWallTex->Load("../Resource/Image/DLWall.png");


	m_pSprite->SetSpriteSize(c_ImageSize.x, c_ImageSize.y);
	m_pSprite->SetSizeScaling(c_Scale);

}

void LeftWall::Render()
{
	const XMFLOAT2 pxGap = { 12 * c_Scale,68 * c_Scale };
	auto pos = Tile::GetBasicPos();
	pos.x -= c_ImageSize.x*c_Scale / 2 + pxGap.x;
	pos.y -= pxGap.y;
	D3DXVECTOR2 vPos = { pos.x,pos.y };

	float upPivot, downPivot, distance;
	//	��
	{
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pUWallTex->GetTexture());

		upPivot = vPos.y + c_ImageSize.y*c_Scale / 2;
	}

	//	��
	{
		pos.y = Tile::GetBasicPos().y;
		float length = Tile::c_ImageSize.y*Tile::c_Scale*Tile::c_Num.y;
		length -= Tile::c_ImageSize.y*Tile::c_Scale;
		vPos.y = pos.y + length;

		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pDWallTex->GetTexture());

		downPivot = vPos.y - c_ImageSize.y*c_Scale / 2;
	}

	distance = downPivot - upPivot;
	if (distance <= 0) { return; }
	
	//	��
	size_t size = static_cast<size_t>(ceil(distance / (c_ImageSize.y*c_Scale)));
	distance /= (size + 1);
	for (size_t i = 0; i < size; ++i) {

		vPos.y = upPivot + (i+1) * distance;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}
}

void DownWall::Init()
{
	m_pSprite = make_unique<Sprite>();

	//	��
	m_pLWallTex = make_unique<Texture>();
	m_pLWallTex->Load("../Resource/Image/LUWall.png");

	//	��
	m_pMWallTex = make_unique<Texture>();
	m_pMWallTex->Load("../Resource/Image/_5.png");

	//	�E
	m_pRWallTex = make_unique<Texture>();
	m_pRWallTex->Load("../Resource/Image/RUWall.png");


	m_pSprite->SetSpriteSize(c_ImageSize.x, c_ImageSize.y);
	m_pSprite->SetSizeScaling(c_Scale);

}

void DownWall::Render()
{
	for (int i = 0; i < c_Num; ++i) {

		auto pos = ConvertPos(i);
		D3DXVECTOR2 vPos = { pos.x,pos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}
}

DirectX::XMFLOAT2 DownWall::ConvertPos(int x)
{
	auto ret = Tile::GetBasicPos();
	XMFLOAT2 offset;
	float length = Tile::c_ImageSize.y*Tile::c_Scale*Tile::c_Num.y;
	length -= Tile::c_ImageSize.y*Tile::c_Scale;

	ret.y += length + Board::c_SquareSize.x*c_Scale;

	//	���W����
	offset.x = c_ImageSize.x*c_Scale;
	offset.y = c_ImageSize.y*c_Scale;

	//	�Y����
	ret.x += x * offset.x;
	ret.x -= offset.x / 2;
	//ret.y -= offset.y / 2;

	//	�摜�̃Y��(35px)
	//const float pxGap = 35 * c_Scale;
	//ret.y -= pxGap;
	return ret;
}

void RightWall::Init()
{
	m_pSprite = make_unique<Sprite>();

	//	��
	m_pUWallTex = make_unique<Texture>();
	m_pUWallTex->Load("../Resource/Image/URWall.png");

	//	��
	m_pMWallTex = make_unique<Texture>();
	m_pMWallTex->Load("../Resource/Image/MRWall.png");

	//	��
	m_pDWallTex = make_unique<Texture>();
	m_pDWallTex->Load("../Resource/Image/DRWall.png");


	m_pSprite->SetSpriteSize(c_ImageSize.x, c_ImageSize.y);
	m_pSprite->SetSizeScaling(c_Scale);

}

void RightWall::Render()
{
	const XMFLOAT2 pxGap = { 12 * c_Scale,16 * c_Scale };
	auto pos = Tile::GetBasicPos();
	pos.x += Tile::c_ImageSize.x*Tile::c_Scale*Tile::c_Num.x;

	pos.x -= c_ImageSize.x*c_Scale / 2+10;
	pos.y -= pxGap.y;
	D3DXVECTOR2 vPos = { pos.x,pos.y };

	//	��
	{
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pUWallTex->GetTexture());
	}

	//	��
	{


	}

	//	��
	{
		pos.y = Tile::GetBasicPos().y;
		float length = Tile::c_ImageSize.y*Tile::c_Scale*Tile::c_Num.y;
		length -= Tile::c_ImageSize.y*Tile::c_Scale;
		vPos.y = pos.y + length;

		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pDWallTex->GetTexture());
	}



}
