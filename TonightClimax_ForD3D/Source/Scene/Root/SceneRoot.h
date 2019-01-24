/*
	@file	SceneRoot.h
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	�V�[���̑J�ڃN���X
*/
#pragma once
#include "../Scene.h"

class SceneRoot final:
	public ISceneBase
{
public:
	SceneRoot();
	~SceneRoot();

	void		Initialize()override;
	ISceneBase*	Update(ISceneBase* scene)override;
	void		Render()override;
	void		Finalize()override;
private:
	Scene*		m_pScene;
};

