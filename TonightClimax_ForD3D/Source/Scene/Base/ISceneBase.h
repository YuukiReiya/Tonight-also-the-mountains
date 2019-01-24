/*
	@file	ISceneBase.h
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	�V�[���̃C���^�[�t�F�[�X
*/
#pragma once

__interface ISceneBase
{
	void Initialize();
	void Finalize();
	ISceneBase* Update(ISceneBase* scene);
	void Render();
};