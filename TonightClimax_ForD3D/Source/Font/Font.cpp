#include "Font.h"


using namespace std;
using namespace DirectX;

const XMINT2 Font::c_Split = { 20,22 };
const XMFLOAT2 Font::c_SpriteSize = { 128,128 };
const string Font::c_FilePath = "../Resource/Font/PixcelMPlus.png";

Font::Font()
{
}


Font::~Font()
{
}

void Font::Init()
{
	m_pSprite = make_unique<Sprite>();
	m_pTexture = make_unique<Texture>();

	m_pTexture->Load(c_FilePath);
	m_pSprite->SetSpriteSize(c_SpriteSize.x, c_SpriteSize.y);
	m_pSprite->SetSplit(c_Split.x, c_Split.y);

	m_AtlasMap[L'今'] = { 15,14 };
	m_AtlasMap[L'夜'] = { 8,21 };
	m_AtlasMap[L'も'] = { 4,3 };
	m_AtlasMap[L'山'] = { 9,21 };
	m_AtlasMap[L'場'] = { 16,16 };
	m_AtlasMap[L'P'] = { 15,6 };
	m_AtlasMap[L'l'] = { 11,3 };
	m_AtlasMap[L'e'] = { 14,2 };
	m_AtlasMap[L'a'] = { 10,2 };
	m_AtlasMap[L's'] = { 18,3 };
	m_AtlasMap[L'r'] = { 17,3 };
	m_AtlasMap[L'T'] = { 19,6 };
	m_AtlasMap[L'o'] = { 14,3 };
	m_AtlasMap[L'B'] = { 11,5 };
	m_AtlasMap[L'u'] = { 10,4 };
	m_AtlasMap[L't'] = { 19,3 };
	m_AtlasMap[L'n'] = { 13,3 };
	m_AtlasMap[L' '] = { 19,21 };
	m_AtlasMap[L'店'] = { 16,20 };
	m_AtlasMap[L'長'] = { 6,20 };
	m_AtlasMap[L'、'] = { 5,8 };
	m_AtlasMap[L'そ'] = { 4,1 };
	m_AtlasMap[L'ろ'] = { 4,4 };
	m_AtlasMap[L'上'] = { 17,20 };
	m_AtlasMap[L'が'] = { 0,6 };
	m_AtlasMap[L'り'] = { 1,4 };
	m_AtlasMap[L'ま'] = { 0,3 };
	m_AtlasMap[L'ー'] = { 6,13 };
	m_AtlasMap[L'す'] = { 2,1 };
	m_AtlasMap[L'。'] = { 6,8 };
	m_AtlasMap[L'待'] = { 15,17 };
	m_AtlasMap[L'て'] = { 8,1 };
	m_AtlasMap[L'こ'] = { 9,0 };
	m_AtlasMap[L'ら'] = { 0,4 };
	m_AtlasMap[L'ぁ'] = { 0,5 };
	m_AtlasMap[L'！'] = { 8,13 };
	m_AtlasMap[L'だ'] = { 0,7 };
	m_AtlasMap[L'お'] = { 4,0 };
	m_AtlasMap[L'客'] = { 18,20 };
	m_AtlasMap[L'様'] = { 19,20 };
	m_AtlasMap[L'残'] = { 0,21 };
	m_AtlasMap[L'っ'] = { 5,5 };
	m_AtlasMap[L'る'] = { 2,4 };
	m_AtlasMap[L'う'] = { 2,0 };
	m_AtlasMap[L'最'] = { 1,21 };
	m_AtlasMap[L'後'] = { 2,21 };
	m_AtlasMap[L'で'] = { 3,7 };
	m_AtlasMap[L'接'] = { 3,21 };
	m_AtlasMap[L'し'] = { 1,1 };
	m_AtlasMap[L'い'] = { 1,0 };
	m_AtlasMap[L'は'] = { 5,2 };
	m_AtlasMap[L'（'] = { 16,4 };
	m_AtlasMap[L'棒'] = { 4,21 };
	m_AtlasMap[L'読'] = { 5,21 };
	m_AtlasMap[L'み'] = { 1,3 };
	m_AtlasMap[L'）'] = { 17,4 };
	m_AtlasMap[L'ヤ'] = { 5,12 };
	m_AtlasMap[L'バ'] = { 5,16 };
	m_AtlasMap[L'早'] = { 7,18 };
	m_AtlasMap[L'く'] = { 7,0 };
	m_AtlasMap[L'さ'] = { 0,1 };
	m_AtlasMap[L'ん'] = { 7,4 };
	m_AtlasMap[L'帰'] = { 6,21 };
	m_AtlasMap[L'せ'] = { 3,1 };
	m_AtlasMap[L'私'] = { 10,19 };
	m_AtlasMap[L'な'] = { 0,2 };
	m_AtlasMap[L'と'] = { 9,1 };
	m_AtlasMap[L'・'] = { 9,8 };
	m_AtlasMap[L'終'] = { 14,19 };
	m_AtlasMap[L'電'] = { 7,21 };
	m_AtlasMap[L'0'] = { 10,0 };
	m_AtlasMap[L'1'] = { 11,0 };
	m_AtlasMap[L'2'] = { 12,0 };
	m_AtlasMap[L'3'] = { 13,0 };
	m_AtlasMap[L'4'] = { 14,0 };
	m_AtlasMap[L'5'] = { 15,0 };
	m_AtlasMap[L'6'] = { 16,0 };
	m_AtlasMap[L'7'] = { 17,0 };
	m_AtlasMap[L'8'] = { 18,0 };
	m_AtlasMap[L'9'] = { 19,0 };
	m_AtlasMap[L':'] = { 17,7 };
	m_AtlasMap[L'A'] = { 10,5 };
	m_AtlasMap[L'ボ'] = { 9,16 };
	m_AtlasMap[L'タ'] = { 5,10 };
	m_AtlasMap[L'ン'] = { 7,13 };
	m_AtlasMap[L'イ'] = { 1,9 };
	m_AtlasMap[L'ト'] = { 9,10 };
	m_AtlasMap[L'ル'] = { 2,13 };
	m_AtlasMap[L'に'] = { 1,2 };
	m_AtlasMap[L'ど'] = { 4,7 };
}

void Font::Render(std::wstring str, D3DXVECTOR2 leftTopPos, D3DXVECTOR2 interval)
{
	int row = 0;
	int offset = 0;
	
	for (size_t i = 0; i < str.length(); ++i) {

		auto pos = leftTopPos;
		if (str[i] == L'\n') { 
			row++; 
			offset = i + 1;
			continue; 
		}
		pos.x -= interval.x* static_cast<float>(offset);
		pos.x += interval.x * static_cast<float>(i);
		pos.y += interval.y * static_cast<float>(row);
		RenderChar(str[i], pos);
	}
}

void Font::SetFontScale(float scale)
{
	m_pSprite->SetSpriteSize(c_SpriteSize.x, c_SpriteSize.y);
	m_pSprite->SetSizeScaling(scale);

}

size_t Font::GetIndentionNum(std::wstring str)
{
	size_t ret, offset;
	ret = offset = 0;
	while (!str.empty() && offset != string::npos) {
		offset = str.find(L"\n");
		str = str.substr(offset + 1);
		if(offset!=string::npos){ ret++; }
	}

	return ret;
}

void Font::RenderChar(wchar_t str, D3DXVECTOR2 pos)
{
	m_pSprite->SetPos(pos);
	m_pSprite->RenderAtlas(
		m_pTexture->GetTexture(),
		m_AtlasMap[str].x,
		m_AtlasMap[str].y
	);
}
