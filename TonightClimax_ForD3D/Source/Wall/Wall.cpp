#include "Wall.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../Board/Board.h"
#include <iostream>

using namespace std;
using namespace DirectX;

const XMINT2 UpWall::c_Comp = { 1,4 };

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

	XMFLOAT2 size = { Board::c_ChipSize };
	size.x *= c_Comp.x;
	size.y *= c_Comp.y;
	m_pSprite->SetSpriteSize(size.x, size.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);
}

void UpWall::Render()
{
	auto& board = Board::GetInstance();
	XMFLOAT2 size = {
	board.GetSquareSize().x*c_Comp.x,
	board.GetSquareSize().y*c_Comp.y
	};
	XMFLOAT2 basicPos = board.GetLeftTop();

	//	��
	{
		basicPos.x += size.x / 2;
		basicPos.y -= board.GetSquareSize().y;

		D3DXVECTOR2 vPos = { basicPos.x,basicPos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pLWallTex->GetTexture());
	}

	//	�E
	{
		basicPos = board.GetLeftTop();
		basicPos.x += board.GetSquareSize().x*Board::c_ChipNum.x;
		basicPos.x -= board.GetSquareSize().x / 2;
		basicPos.y -= board.GetSquareSize().y;

		D3DXVECTOR2 vPos = { basicPos.x,basicPos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pRWallTex->GetTexture());
	}

	//	��
	for (int i = 1; i < Board::c_ChipNum.x - 1; ++i) {

		 basicPos = board.GetLeftTop();

		//	�摜�̒��S���W
		basicPos.x += size.x / 2;
		basicPos.y -= board.GetSquareSize().y*2;//	��_�ɑ΂�2�}�X��

		//	�ȍ~
		basicPos.x += size.x*i;

		D3DXVECTOR2 vPos = { basicPos.x,basicPos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}

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


	XMFLOAT2 size = { Board::c_ChipSize };
	m_pSprite->SetSpriteSize(size.x, size.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);
}
#include"../Debug/DebugDraw.h"
auto&dd = DebugDraw::GetInstance();
void LeftWall::Render()
{
	auto& board = Board::GetInstance();

	D3DXVECTOR2 vPos = { board.GetLeftTop().x,board.GetLeftTop().y };

	//	��
	{
		const float pxGap = 12 * Board::c_Scale;
		vPos.y -= board.GetSquareSize().y / 2 + pxGap;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pUWallTex->GetTexture());

		//	�␳(���Ԃ��ǂ�)
		vPos.y += board.GetSquareSize().y / 2;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}

	//	��
	for (int i = 0; i < Board::c_ChipNum.y - 1; ++i) {
		vPos = { board.GetLeftTop().x,board.GetLeftTop().y };
		vPos.y += board.GetSquareSize().y / 2;
		vPos.y += i * board.GetSquareSize().y;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}

	//	��
	{
		vPos.y+= board.GetSquareSize().y;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pDWallTex->GetTexture());
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


	XMFLOAT2 size = { Board::c_ChipSize };
	m_pSprite->SetSpriteSize(size.x, size.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);

}

void DownWall::Render()
{
	auto& board = Board::GetInstance();

	XMFLOAT2 basicPos = board.GetLeftTop();

	//	��
	{
		//basicPos.x += size.x / 2;
		//basicPos.y -= board.GetSquareSize().y;

		//D3DXVECTOR2 vPos = { basicPos.x,basicPos.y };
		//m_pSprite->SetPos(vPos);
		//m_pSprite->Render(m_pLWallTex->GetTexture());
	}


	for (int i = 0; i < Board::c_ChipNum.x; ++i) {


		D3DXVECTOR2 vPos = { basicPos.x,basicPos.y };
		vPos.x += i * board.GetSquareSize().x + board.GetSquareSize().x / 2;
		vPos.y += Board::c_ChipNum.y*board.GetSquareSize().y - board.GetSquareSize().y / 2;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}
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

	//	����
	m_pEntranceTex = make_unique<Texture>();
	m_pEntranceTex->Load("../Resource/Image/MRWall_E.png");

	XMFLOAT2 size = { Board::c_ChipSize };
	m_pSprite->SetSpriteSize(size.x, size.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);
}

void RightWall::Render()
{

	auto& board = Board::GetInstance();

	auto pos = board.GetLeftTop();
	D3DXVECTOR2 vPos = { pos.x,pos.y };
	m_pSprite->SetSpriteSize(Board::c_ChipSize.x, Board::c_ChipSize.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);

	//	��
	{
		const float pxGap = 12 * Board::c_Scale;
		vPos.y -= board.GetSquareSize().y / 2 + pxGap;
		vPos.x += Board::c_ChipNum.x*board.GetSquareSize().x;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pUWallTex->GetTexture());

		//	�␳(���Ԃ��ǂ�)
		vPos.y += board.GetSquareSize().y / 2;
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}

	//	y:[0]�`[n] ����
	const int n = 1;
	for (size_t i = 0; i < n; i++)
	{
		pos = board.GetLeftTop();
		pos.x += board.GetSquareSize().x*Board::c_ChipNum.x;
		pos.y += board.GetSquareSize().y / 2 + i * board.GetSquareSize().y;
		vPos = { pos.x,pos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}

	//	����(comp.y���̃}�X)
	const XMINT2 comp = { 1,4 };
	{
		const float pxGap = 24 * Board::c_Scale;
		pos.x += board.GetSquareSize().x*comp.x / 2;
		pos.y += board.GetSquareSize().y*comp.y / 2+pxGap;
		vPos = { pos.x,pos.y };
		m_pSprite->SetSpriteSize(Board::c_ChipSize.x*comp.x, Board::c_ChipSize.y*comp.y);
		m_pSprite->SetSizeScaling(Board::c_Scale);
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pEntranceTex->GetTexture());
	}

	m_pSprite->SetSpriteSize(Board::c_ChipSize.x, Board::c_ChipSize.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);

	//	��
	for (int i = 0; i < Board::c_ChipNum.y - (n + comp.y + 1); i++)
	{
		pos = board.GetLeftTop();
		pos.x += board.GetSquareSize().x*Board::c_ChipNum.x;
		pos.y += board.GetSquareSize().y * 5 + board.GetSquareSize().y / 2;
		pos.y += i * board.GetSquareSize().y;
		vPos = { pos.x,pos.y };
		m_pSprite->SetPos(vPos);
		m_pSprite->Render(m_pMWallTex->GetTexture());
	}
	vPos.y += board.GetSquareSize().y;
	m_pSprite->SetPos(vPos);
	m_pSprite->Render(m_pDWallTex->GetTexture());
}
