#pragma once
#include "../Scene.h"
#include "../../Sprite/SpriteReader.h"
#include "../../IntroState/IntroState.h"
#include <memory>
#include <DirectXMath.h>
#include <queue>

class Intro final
	:public Scene
{
public:
	Intro();
	~Intro();

	void Initialize()override;
	void Finalize()override;
	Scene* Update(SceneRoot* root)override;
	void Render()override;
private:
	SpriteReader::ReadData	m_pImages;
	std::queue<std::wstring>m_TextQueue;
};

