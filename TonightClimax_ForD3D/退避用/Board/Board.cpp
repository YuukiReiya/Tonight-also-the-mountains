#include "Board.h"
#include "../MyGame.h"
using namespace std;
using namespace DirectX;

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
}

void Board::Render()
{
	m_pTile->Render();
	m_pRWall->Render();
	m_pLWall->Render();
	m_pUWall->Render();
	m_pDWall->Render();
	m_pTable->Render();


}

