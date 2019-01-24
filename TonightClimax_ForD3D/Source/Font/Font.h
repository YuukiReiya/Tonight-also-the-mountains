#pragma once
#include "../Singleton.h"
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include <map>
#include <DirectXMath.h>


class Font final
	:public Singleton<Font>
{
public:
	Font();
	~Font();

	void Init();
	void Render(std::wstring str, D3DXVECTOR2 leftTopPos, D3DXVECTOR2 interval = GetInstance().m_pSprite->GetSize());
	void SetFontScale(float scale);
	struct FontData
	{
		DirectX::XMINT2 atlas;
	};
private:
	size_t GetIndentionNum(std::wstring str);
	void RenderChar(wchar_t str, D3DXVECTOR2 pos);
	std::map<wchar_t, DirectX::XMINT2>m_AtlasMap;

	std::unique_ptr<Sprite>m_pSprite;
	std::unique_ptr<Texture>m_pTexture;

	static const std::string c_FilePath;
	static const DirectX::XMINT2 c_Split;
	static const DirectX::XMFLOAT2 c_SpriteSize;
};

