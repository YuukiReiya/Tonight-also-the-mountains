#include "Intro.h"
#include "../../Input/Input.h"
#include "../../IntroStage/IntroStage.h"
#include "../../Font/Font.h"
#include "../../TextController/TextController.h"
#include "../../CSV/CSVReader.h"
#include <codecvt>

using namespace std;
using namespace DirectX;

Intro::Intro()
{
}


Intro::~Intro()
{
}

void Intro::Initialize()
{
	SpriteReader sr;
	m_pImages = sr.Load("../Resource/csv/IntroImage.csv");

	ActionManager::GetInstance().Init();
	IntroStage::GetInstance().Init();

	auto& csv = CSVReader::GetInstance();
	csv.Load("../Resource/csv/IntroText.csv");
	auto data = csv.GetCells();
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t>cv;
	for (int y = 0; y < 8; ++y) {
		const char* tmp = data[y][0].c_str();

		mbstate_t state = mbstate_t();
		size_t len = 1 + mbsrtowcs(NULL, &tmp, 0, &state);
		vector<wchar_t> wstr(len);
		mbsrtowcs(&wstr[0], &tmp, wstr.size(), &state);
		wstring str = &wstr[0];
		m_TextQueue.push(str);
	}

	//Font::GetInstance().Init();
	TextController::GetInstance().Init();
	auto&text = TextController::GetInstance();
	text.SetFontScale(0.5f);
	text.SetIntervalForCharacterDisplay(150);
	text.SetInterval({ 64,64 });
	text.SetText(m_TextQueue.front());
	text.SetPos({300,900});
	m_TextQueue.pop();
}

void Intro::Finalize()
{
}

Scene * Intro::Update(SceneRoot * root)
{
	auto&input = Input::GetInstance();
	auto& text = TextController::GetInstance();

	if (input.GetKeyDown(input.A)) {
		//SpriteReader sr;
		//m_pImages = sr.Load("../Resource/csv/IntroImage.csv");

		//	テキストリストが空 ＆ 文字列をすべて表示済み
		if (m_TextQueue.empty() && text.GetIsEndOfShowText()) {

		}

		//	すべて表示し終わっている
		else if (!m_TextQueue.empty() &&text.GetIsEndOfShowText()) {
			text.SetText(m_TextQueue.front());
			m_TextQueue.pop();

			IntroStage::GetInstance().SetNextAction();

		}
		//	一気に表示
		else {
			text.ShowAllText();
		}
	}

	IntroStage::GetInstance().Update();	


	text.Update();
	return this;
}

void Intro::Render()
{
	IntroStage::GetInstance().Render();

	//	player
	//m_pPsp->RenderAtlas(m_pPtex->GetTexture(), m_PlayerAtlas.x, m_PlayerAtlas.y);

	//	owner
	//m_pOsp->RenderAtlas(m_pOtex->GetTexture(), m_OwnerAtlas.x, m_OwnerAtlas.y);

	for (auto it : m_pImages) {
		it.second.Render();
	}

	//auto&font = Font::GetInstance();
	//float scale = 0.5f;
	//auto pos = D3DXVECTOR2{ 720,900 };
	//font.SetFontScale(scale);
	//font.Render(L"Press\nTo", pos, { 64 * scale, 64 * scale });

	auto&text = TextController::GetInstance();
	text.Render();
	if (text.GetIsEndOfShowText()) {
	}
}

