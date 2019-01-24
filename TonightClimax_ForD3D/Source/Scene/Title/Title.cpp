#include "Title.h"
#include "../../MemoryLeaks.h"
#include "../../Input/Input.h"
#include "../Intro/Intro.h"

using namespace std;
using namespace DirectX;

const D3DXVECTOR2 Title::c_LogoPos = { 576,180 };
const D3DXVECTOR2 Title::c_PressPos = { 720,900 };
const int Title::c_FlashCnt = 16;

Title::Title():m_flshCnt(0),m_isRender(true),m_pAtlasIndex(0),m_bAtlasIndex(2)
{
}


Title::~Title()
{
}

void Title::Initialize()
{
	SpriteReader sr;
	m_pImages = sr.Load("../Resource/csv/TitleImage.csv");

	m_pPSprite	= make_unique<Sprite>();
	m_pPTexture = make_unique<Texture>();
	m_pBSprite	= make_unique<Sprite>();
	m_pBTexture = make_unique<Texture>();

	D3DXVECTOR2 pos = { 960,600 };
	m_pPTexture->Load("../Resource/Image/chara_player.png");
	m_pPSprite->SetSplit(3, 4);
	m_pPSprite->SetSpriteSize(32,32);
	m_pPSprite->SetSizeScaling(4);
	m_pPSprite->SetPos(pos);

	D3DXVECTOR2 offset = {80,-100};
	m_pBTexture->Load("../Resource/Image/Balloon.png");
	m_pBSprite->SetSplit(8, 10);
	m_pBSprite->SetSpriteSize(32, 32);
	m_pBSprite->SetSizeScaling(4);
	m_pBSprite->SetPos(pos + offset);
	//Font::GetInstance().Init();
	Font::GetInstance().SetFontScale(1.5f);
}

void Title::Finalize()
{
}

Scene * Title::Update(SceneRoot * root)
{
	m_flshCnt++;
	if (m_flshCnt%c_FlashCnt == 0) { m_isRender = !m_isRender; }
	if (m_flshCnt % 12 == 0) { m_pAtlasIndex = m_pAtlasIndex == 0 ? 2 : 0; }
	if (m_flshCnt % 6 == 0) { m_bAtlasIndex = m_bAtlasIndex < 7 ? ++m_bAtlasIndex : 2; }

	auto&input = Input::GetInstance();
	if (input.GetKeyDown(input.A)|| input.GetKeyDown(input.START)) {
		return new Intro;
	}


	return this;
}

void Title::Render()
{
	for (auto it : m_pImages) {
		it.second.Render();
	}

	auto&font = Font::GetInstance();


	font.SetFontScale(1.5f);
	font.Render(L"¡–é‚àŽRê", c_LogoPos);

	m_pPSprite->RenderAtlas(m_pPTexture->GetTexture(), m_pAtlasIndex, 0);
	m_pBSprite->RenderAtlas(m_pBTexture->GetTexture(), m_bAtlasIndex, 6);

	if (!m_isRender) {
		return;
	}
	float scale = 0.5f;
	font.SetFontScale(scale);
	font.Render(L"Press", c_PressPos, { 64 * scale,0 });
	auto pos = c_PressPos;
	pos.x += 64 * 3;
	font.Render(L"To", pos, { 64 * scale,0 });
	pos.x += 64 * 1.5f;
	font.Render(L"Button", pos, { 64 * scale,0 });

}
