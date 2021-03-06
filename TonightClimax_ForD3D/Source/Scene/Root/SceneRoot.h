/*
	@file	SceneRoot.h
	@date	2018/02/22
	@author	番場 宥輝
	@brief	シーンの遷移クラス
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

