#include "Result.h"
#include "../../CSV/CSVReader.h"
#include "../../Input/Input.h"
#include "../../Font/Font.h"
#include "../Title/Title.h"

void Result::Initialize()
{
	auto&csv = CSVReader::GetInstance();
	SpriteReader sr;
	m_Sprites = sr.Load("../Resource/csv/ResultImage.csv");

	//Font::GetInstance().Init();
	m_rc.Init();
	m_lastTrain.Init();
}

void Result::Finalize()
{
}

void Result::Render()
{
	m_Sprites["bg"].Render();
	m_Sprites["gr"].Render();

	
	m_lastTrain.Render();
	m_rc.Render();
}

void ResultS::Initialize()
{
	Result::Initialize();

	//	電車の移動処理
	m_lastTrain.SetPos({ -852,500 });
	m_lastTrain.SetTargetPos(1920);

	isRenderChara = true;
}

Scene * ResultS::Update(SceneRoot * root)
{
	cnt++;
	m_lastTrain.Update();
	m_rc.Update();

	//-------------------
	//	フレーム直打ち
	//-------------------

	//	電車停車
	if (cnt == 100) {
		//	キャラの移動命令
		m_rc.SetTargetPos({ 1450, 720 });
	}

	//	キャラ停止
	else if (cnt == 215) {
		m_rc.SetBalloonState(ResultCharacter::HAPPY);
	}

	//	キャラ再移動
	else if (cnt == 245) {
		m_rc.SetBalloonState(ResultCharacter::NONE);
		m_rc.SetTargetPos({ 1450, 570 });
	}

	//	キャラのレンダリング停止
	else if (cnt == 255) {
		isRenderChara = false;
	}

	//	電車再出発
	else if (cnt == 265) {
		m_lastTrain.SetTargetPos(4476);
	}

	else if (cnt >= 380) {

		auto&input = Input::GetInstance();
		if (input.GetKeyDown(input.A)) {
			return new Title;
		}
	}


	return this;
}

void ResultS::Render()
{
	m_Sprites["bg"].Render();
	m_Sprites["gr"].Render();


	m_lastTrain.Render();

	if (isRenderChara) {
		m_rc.Render();
	}

	if (cnt >= 350) {
		auto&font = Font::GetInstance();
		font.SetFontScale(1);
		font.Render(L"23:59", { 840,400 }, {52,0});
	}

	if (cnt >= 380) {
		if (cnt % 32 <= 16) {
			auto&font = Font::GetInstance();
			font.SetFontScale(0.5f);
			font.Render(L"Aボタンでタイトルにもどる", { 540,550 });
		}
	}
}

void ResultF::Initialize()
{
	Result::Initialize();

	//	電車の移動処理
	m_lastTrain.SetPos({ -852,500 });
	m_lastTrain.SetTargetPos(1920);


}

Scene * ResultF::Update(SceneRoot * root)
{
	cnt++;
	m_lastTrain.Update();
	m_rc.Update();

	//-------------------
	//	フレーム直打ち
	//-------------------

	//	電車停車
	if (cnt == 100) {
		//	キャラの移動命令
		m_rc.SetTargetPos({ 960, 720 });
	}

	//	電車移動
	else if (cnt == 160) {
		m_lastTrain.SetTargetPos(4476);
	}

	//	キャラ呆然
	else if (cnt == 205) {
		m_rc.SetBalloonState(ResultCharacter::WORD);
	}

	//	キャラ悲しみ
	else if (cnt == 244) {
		m_rc.SetBalloonState(ResultCharacter::CRY);
	}


	else if (cnt >= 380) {

		auto&input = Input::GetInstance();
		if (input.GetKeyDown(input.A)) {
			return new Title;
		}
	}
	return this;
}

void ResultF::Render()
{
	Result::Render();
	if (cnt >= 270) {
		auto&font = Font::GetInstance();
		font.SetFontScale(1);
		font.Render(L"00:01", { 840,400 }, { 52,0 });
	}

	if (cnt >= 300) {
		if (cnt % 32 <= 16) {
			auto&font = Font::GetInstance();
			font.SetFontScale(0.5f);
			font.Render(L"Aボタンでタイトルにもどる", { 540,550 });
		}
	}

}
