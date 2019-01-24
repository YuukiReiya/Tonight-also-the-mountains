/*
	@file	Scene.cpp
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	�e�V�[���̊��N���X
*/
#include "Scene.h"
#include "Root/SceneRoot.h"

/*!
	@brief	�f�X�g���N�^
*/
Scene::~Scene()
{
}

/*!
	@brief	�X�V
*/
ISceneBase * Scene::Update(ISceneBase * scene)
{
	SceneRoot* root = dynamic_cast<SceneRoot*>(scene);
	return Update(root);
}