/*
	@file	SceneRoot.cpp
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	�V�[���̑J�ڃN���X
*/
#include "SceneRoot.h"
#include "../SampleScene/SampleScene.h"
#include "../Title/Title.h"
#include "../Intro/Intro.h"
#include "../Result/Result.h"
#include "../../MemoryLeaks.h"

/*!
	@brief	�R���X�g���N�^
*/
SceneRoot::SceneRoot()
	:m_pScene(nullptr)
{
}

/*!
	@brief	�f�X�g���N�^
*/
SceneRoot::~SceneRoot()
{
	Finalize();
}

/*!
	@brief	������
*/
void SceneRoot::Initialize()
{
	/*! ��ԍŏ��̃V�[�� */
	//m_pScene = new Title();
	//m_pScene = new Intro();
	//m_pScene = new ResultF();
	m_pScene = new SampleScene;
	m_pScene->Initialize();
}

/*!
	@brief	�X�V
	@return	�V�[���̃|�C���^
*/
ISceneBase * SceneRoot::Update(ISceneBase * scene)
{
	/*! �V�[���̎��s */
	ISceneBase*pNext = m_pScene->Update(this);

	/*! �߂�l�����݂̃V�[���ƈقȂ��Ă���΃V�[���J�� */
	if (pNext != m_pScene) 
	{
		/*! �V�[���̔j�� */
		m_pScene->Finalize();
		delete m_pScene;

		/*!  */
		Scene* casted = dynamic_cast<Scene*>(pNext);
		m_pScene = casted;
		m_pScene->Initialize();
	}
	return this;
}

/*!
	@brief	�`��
*/
void SceneRoot::Render()
{
	m_pScene->Render();
}

/*!
	@brief	�j��
*/
void SceneRoot::Finalize()
{
	delete m_pScene;
	m_pScene = nullptr;
}
