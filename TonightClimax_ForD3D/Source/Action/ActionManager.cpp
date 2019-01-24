#include "ActionManager.h"

using namespace std;
using namespace DirectX;



ActionManager::ActionManager()
{
}


ActionManager::~ActionManager()
{
}

void ActionManager::Init()
{
	m_pSprite			= make_shared<Sprite>();
	m_pOwnerTexture		= make_shared<Texture>();
	m_pPlayerTexture	= make_shared<Texture>();
	m_pBalloonTexture	= make_shared<Texture>();


	m_pOwnerTexture->Load("../Resource/Image/owner.png");
	m_pPlayerTexture->Load("../Resource/Image/chara_player.png");
	m_pBalloonTexture->Load("../Resource/Image/Balloon.png");

	m_Chara.split	= { 3,4 };
	m_Chara.size	= { 32,32 };
	m_Chara.scale	= 3;

	m_pSprite->SetSplit(m_Chara.split.x, m_Chara.split.y);
	m_pSprite->SetSpriteSize(m_Chara.size.x, m_Chara.size.y);
	m_pSprite->SetSizeScaling(m_Chara.scale);

	m_Balloon.scale	= 3;
	m_Balloon.split = { 8,10 };
	m_Balloon.size	= { 32,32 };

}
