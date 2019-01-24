#include "TextController.h"

using namespace std;

TextController::TextController()
{
}

bool TextController::isCompleteDisplayText()
{
	return timeGetTime() > timeElapsed + timeUntilDisplay;
}

float TextController::Clamp01(float val)
{
	float ret = min(max(val, 0), 1);
	return ret;
}


TextController::~TextController()
{
}

void TextController::Init()
{
	timeUntilDisplay = 0;
	timeElapsed = 1;
	lastUpdateTextLength = -1;
	intervalForCharacterDislay = 250;
	isSkipText = false;
	m_Interval = { 128,128 };
}

void TextController::Update()
{           
	//  テキストの更新処理


	//  テキストが表示しきっている
	if (isCompleteDisplayText())
	{
		//  最後の文字を表示していたら処理しない
		//if (currentLine > textEvents.Length) { return; }

		//  Aボタンを押すことで次のテキストの表示を開始する
		//if (isSentText())
		if(isSkipText)
		{
			//ReflectionRun();
			//SetNextLine();
		}
	}
	//  テキストの表示が終わっていない
	else
	{
		//  Aボタンを押すことですべて表示する
		//if (isSentText()) { timeUntilDisplay = 0; }
		if(isSkipText) { timeUntilDisplay = 0; }
	}

}

void TextController::Render()
{
	//  現在の時間に表示するべき文字数
	int displayCharacterCount = static_cast<int>(Clamp01((timeGetTime() - timeElapsed) / timeUntilDisplay) * currentText.length());

	//  表示すべき時間と最後に更新された文字数が異なればテキストの文字を更新
	//if (displayCharacterCount != lastUpdateTextLength)
	{
		wstring str = currentText.substr(0, displayCharacterCount);
		Font::GetInstance().Render(str, m_Pos, m_Interval);
		lastUpdateTextLength = displayCharacterCount;
	}
}

void TextController::SetText(std::wstring str)
{
	currentText = str;
	timeUntilDisplay = currentText.length()*intervalForCharacterDislay;
	timeElapsed = timeGetTime();
	lastUpdateTextLength = -1;
	isSkipText = false;
}
