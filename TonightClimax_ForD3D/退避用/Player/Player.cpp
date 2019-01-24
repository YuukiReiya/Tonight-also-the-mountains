#include "Player.h"
#include "../Input/Input.h"
using namespace std;

const string Player::c_FilePath = { "../Resource/Image/chara_player.png" };

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_pSprite	= make_unique<Sprite>();
	m_pTex		= make_unique<Texture>();

	m_pTex->Load(c_FilePath);
	m_pSprite->SetSpriteSize(c_ImageSize, c_ImageSize);
	m_pSprite->SetSizeScaling(c_Scale);
	m_pSprite->SetSplit(c_SplitNum.x, c_SplitNum.y);
}

D3DXVECTOR2 pos = { 960,540 };
void Player::Update()
{
	auto&input = Input::GetInstance();
	const float speed = 48*c_Scale/2;
	if (input.GetKeyDown(input.LEFT)) {
		pos.x -= speed;
	}

	if (input.GetKeyDown(input.RIGHT)) {
		pos.x += speed;
	}

	if (input.GetKeyDown(input.UP)) {
		pos.y -= speed;
	}

	if (input.GetKeyDown(input.DOWN)) {
		pos.y += speed;
	}


}

void Player::Render()
{
	m_pSprite->SetPos(pos);
	m_pSprite->RenderAtlas(m_pTex->GetTexture(), 0, 0);
}
