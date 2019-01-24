/*
	@file	SampleScene.h
	@date	2018/11/06
	@author	�ԏ� �G�P
	@brief	�T���v���V�[��
*/
#pragma once
#include <memory>
#include "../Scene.h"
#include "../../Sprite/SpriteReader.h"

class SampleScene final
	: public Scene
{
public:
	SampleScene();
	~SampleScene();

	void Initialize()override;
	void Finalize()override;
	Scene* Update(SceneRoot* root)override;
	void Render()override;

private:
	SpriteReader::ReadData m_pRD;
};

