#include "Owner.h"
#include "../../Board/Board.h"
using namespace std;
using namespace DirectX;

const string Owner::c_FilePath = "../Resource/Image/owner.png";
const XMINT2 Owner::c_SplitNum = { 3,4 };
const XMINT2 Owner::c_ltInitIndex = { 12,0 };

Owner::Owner()
{
}


Owner::~Owner()
{
}

void Owner::Move(DirectX::XMFLOAT2 vec)
{
	m_CharaPos.x += vec.x;
	m_CharaPos.y += vec.y;
}

void Owner::Init() {
	
	m_pSprite	= make_unique<Sprite>();
	m_pTexture	= make_unique<Texture>();

	m_pTexture->Load(c_FilePath);

	auto&bd = Board::GetInstance();
	auto size = bd.c_ChipSize;
	m_pSprite->SetSpriteSize(size.x, size.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);
	m_pSprite->SetSplit(c_SplitNum.x, c_SplitNum.y);

	m_ltIndex = c_ltInitIndex;
	m_CharaPos = bd.ConvertSquareCenter(m_ltIndex);
	m_NextPos = m_CharaPos;
	m_pSprite->SetPos({ m_CharaPos.x,m_CharaPos.y });
}

void Owner::Update() {

	//
	float speed = 1.0f;
	XMFLOAT2 vec = {
		m_Dir.x*speed,
		m_Dir.y*speed
	};
	Move(vec);
}

void Owner::Render() {
	D3DXVECTOR2 pos = { m_CharaPos.x,m_CharaPos.y };
	m_pSprite->SetPos(pos);
	m_pSprite->Render(m_pTexture->GetTexture());
}

