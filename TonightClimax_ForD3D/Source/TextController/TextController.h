#pragma once
#include "../Font/Font.h"
class TextController
	:public Singleton<TextController>
{
public:
	~TextController();

	void Init();
	void Update();
	void Render();
	void SetText(std::wstring str);
	void SetPos(D3DXVECTOR2 leftTopPos) { m_Pos = leftTopPos; }
	void SetInterval(D3DXVECTOR2 interval) { m_Interval = interval; }
	void SetFontScale(float scale) { Font::GetInstance().SetFontScale(scale); }
	bool GetIsEndOfShowText() { return currentText.length() == lastUpdateTextLength; }
	void ShowAllText() { isSkipText = true; }
	void SetIntervalForCharacterDisplay(float interval) { intervalForCharacterDislay = interval; }
private:
	TextController();
	friend class Singleton<TextController>;
	bool isCompleteDisplayText();
	float Clamp01(float val);
	float intervalForCharacterDislay;
	std::wstring currentText;	//現在の文字列
	float timeUntilDisplay;     //表示にかかる時間
	float timeElapsed;          //文字列の表示を開始した時間                 
	int lastUpdateTextLength;   //最後に表示したの文字数
	bool isSkipText;
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Interval;
};