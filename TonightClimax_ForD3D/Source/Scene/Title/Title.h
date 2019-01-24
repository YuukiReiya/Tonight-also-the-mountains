#pragma once
#include "../Scene.h"
#include "../../Sprite/SpriteReader.h"
#include "../../Font/Font.h"
#include <memory>

class Title final
	: public Scene
{
public:
	Title();
	~Title();

	void Initialize()override;
	void Finalize()override;
	Scene* Update(SceneRoot* root)override;
	void Render()override;

private:
	SpriteReader::ReadData m_pImages;

	static const D3DXVECTOR2 c_LogoPos;
	static const D3DXVECTOR2 c_PressPos;
	static const int c_FlashCnt;

	//Player
	std::unique_ptr<Sprite>	m_pPSprite;	
	std::unique_ptr<Texture>m_pPTexture;
	//Ballon
	std::unique_ptr<Sprite>	m_pBSprite;
	std::unique_ptr<Texture>m_pBTexture;

	int m_flshCnt;
	int m_pAtlasIndex;
	int m_bAtlasIndex;
	bool m_isRender;
	//	3ビット目に決定用のバッファ(フラグを持たせる)
	enum Menu : byte {

		START	= 0b10,
		END		= 0b01,
	};

	Menu m_eMenu;
};

