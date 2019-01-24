/*
	@file	SampleScene.cpp
	@date	2018/11/06
	@author	番場 宥輝
	@brief	サンプルシーン
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
	@brief	名前空間
	@detail	usingディレクティブ
*/
using namespace std;
using namespace Keyboard;

Player* gp = new Player;

/*!
	@brief	コンストラクタ
*/
SampleScene::SampleScene()
{
}

/*!
	@brief	デストラクタ
*/
SampleScene::~SampleScene()
{
	Finalize();
}

/*!
	@brief	初期化
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
	@brief	破棄
*/
void SampleScene::Finalize()
{
	delete gp;
}

/*!
	@brief	更新
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
	@brief	描画
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
