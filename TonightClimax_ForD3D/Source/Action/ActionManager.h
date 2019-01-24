#pragma once
#include "../Singleton.h"
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include <memory>
#include <DirectXMath.h>

class ActionManager final
	:public Singleton<ActionManager>
{
public:
	~ActionManager();
	struct SpriteData {
		DirectX::XMINT2		split;
		DirectX::XMFLOAT2	size;
		float				scale;
	};

	std::shared_ptr<Texture>GetPlayerTex() { return m_pPlayerTexture; };
	std::shared_ptr<Texture>GetOwnerTex() { return m_pOwnerTexture; }
	std::shared_ptr<Texture>GetBalloonTex() { return m_pBalloonTexture; }
	std::shared_ptr<Sprite>GetSprite() { return m_pSprite; };
	SpriteData GetCharaData() { return m_Chara; }
	SpriteData GetBalloonData() { return m_Balloon; }
	void Init();
private:
	ActionManager();
	friend class Singleton<ActionManager>;
	std::shared_ptr<Texture>	m_pPlayerTexture;
	std::shared_ptr<Texture>	m_pOwnerTexture;
	std::shared_ptr<Texture>	m_pBalloonTexture;
	std::shared_ptr<Sprite>		m_pSprite;


	SpriteData m_Chara;
	SpriteData m_Balloon;
};

