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
	std::wstring currentText;	//���݂̕�����
	float timeUntilDisplay;     //�\���ɂ����鎞��
	float timeElapsed;          //������̕\�����J�n��������                 
	int lastUpdateTextLength;   //�Ō�ɕ\�������̕�����
	bool isSkipText;
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Interval;
};