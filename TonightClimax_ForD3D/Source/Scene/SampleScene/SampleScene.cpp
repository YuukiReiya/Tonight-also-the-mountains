/*
	@file	SampleScene.cpp
	@date	2018/11/06
	@author	�ԏ� �G�P
	@brief	�T���v���V�[��
*/
#include "SampleScene.h"
#include "../../MyGame.h"
#include "../../Input/Input.h"
#include "../../Board/Board.h"
#include "../../Debug/DebugDraw.h"
#include "../../Player/Player.h"
#include "../../Character/Controller/CharacterController.h"
#include "../../CSV/CSVReader.h"
/*!
	@brief	���O���
	@detail	using�f�B���N�e�B�u
*/
using namespace std;
using namespace Keyboard;

Player* gp = new Player;

/*!
	@brief	�R���X�g���N�^
*/
SampleScene::SampleScene()
{
}

/*!
	@brief	�f�X�g���N�^
*/
SampleScene::~SampleScene()
{
	Finalize();
}

/*!
	@brief	������
*/
void SampleScene::Initialize()
{
	SpriteReader sr;
	//m_pRD = sr.Load("../Resource/csv/ImageReader.csv");
	DebugDraw::GetInstance().Init();

	Board::GetInstance().Init();
	CharacterController::GetInstance().Init();
	gp->Init();

}

/*!
	@brief	�j��
*/
void SampleScene::Finalize()
{
	delete gp;
}

/*!
	@brief	�X�V
*/
Scene * SampleScene::Update(SceneRoot * root)
{
	if (GetButtonDown(Keyboard::TAB)) {
		SpriteReader sr;
		m_pRD = sr.Load("../Resource/csv/ImageReader.csv");

	}

	////if (GetButton('S')) {
	////	pos.z -= 0.01f;
	////}

	////if (GetButton('W')) {
	////	pos.z += 0.01f;
	////}
	//Player::GetInstance().Update();
	//Camera::GetInstance().Initialize(pos,look);

	//gp->Update();
	//CharacterController::GetInstance().Update();
	return this;
}

/*!
	@brief	�`��
*/
void SampleScene::Render()
{
	//Player::GetInstance().Rnder();
	Board::GetInstance().Render();
	//CharacterController::GetInstance().Render();

	//for (auto it : m_pRD) {
	//	it.second.Render();
	//}
	//go->Render();
	//gp->Render();
}
