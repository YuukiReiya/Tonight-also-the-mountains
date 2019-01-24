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
	//  �e�L�X�g�̍X�V����


	//  �e�L�X�g���\���������Ă���
	if (isCompleteDisplayText())
	{
		//  �Ō�̕�����\�����Ă����珈�����Ȃ�
		//if (currentLine > textEvents.Length) { return; }

		//  A�{�^�����������ƂŎ��̃e�L�X�g�̕\�����J�n����
		//if (isSentText())
		if(isSkipText)
		{
			//ReflectionRun();
			//SetNextLine();
		}
	}
	//  �e�L�X�g�̕\�����I����Ă��Ȃ�
	else
	{
		//  A�{�^�����������Ƃł��ׂĕ\������
		//if (isSentText()) { timeUntilDisplay = 0; }
		if(isSkipText) { timeUntilDisplay = 0; }
	}

}

void TextController::Render()
{
	//  ���݂̎��Ԃɕ\������ׂ�������
	int displayCharacterCount = static_cast<int>(Clamp01((timeGetTime() - timeElapsed) / timeUntilDisplay) * currentText.length());

	//  �\�����ׂ����ԂƍŌ�ɍX�V���ꂽ���������قȂ�΃e�L�X�g�̕������X�V
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
