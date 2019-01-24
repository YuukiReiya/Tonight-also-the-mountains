#pragma once
#include "../../Singleton.h"
#include "../ICharacter.h"
#include "../../Texture/Texture.h"
#include "../../Sprite/Sprite.h"
#include <memory>
#include <vector>
class CharacterController:
	public Singleton<CharacterController>
{
public:
	~CharacterController();


	void Init();
	void Update();
	void Render();

	std::shared_ptr<ICharacter> GetCharacter(DirectX::XMINT2 ltIndex);
	std::shared_ptr<ICharacter> GetCharacter(DirectX::XMFLOAT2 pos);
private:
	friend class Singleton<CharacterController>;
	CharacterController();

	static const float c_Diff;
	size_t m_CustomerNumber;
	std::vector<std::shared_ptr<ICharacter>> m_Characters;
	std::shared_ptr<Texture> m_CustomerTex[3];
	std::shared_ptr<Sprite>m_pSprite;
};

