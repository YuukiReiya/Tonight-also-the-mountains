/*!
	@file	Debug.cpp
	@date	2018/11/20
	@author	�ԏ� �G�P
	@brief	�f�o�b�O�֘A�̃N���X
	@detail	�e�N���X�Ŏg���Ă���V���{���̐錾���܂߂�
			�Q�Ƃ͕s�v�Ȃ̂Ń����o�͑S��static�Ő錾�y�ђ�`
*/
#include "Debug.h"
#include "../MyGame.h"

/*!
	�ÓI�����o�ϐ��̏������Ɛ錾
*/
HWND	Debug::m_hWndConsole	= nullptr;
HMENU	Debug::m_hMenu			= nullptr;


/*!
	@brief	��R���X�g���N�^
*/
//Debug::Debug()
//{
//}

/*!	
	@brief	��f�X�g���N�^
*/
//Debug::~Debug()
//{
//}
//
/*!
	@fn		�R���\�[���E�B���h�E�̐���
	@brief	�R���\�[���E�B���h�E�̍쐬�ƃn���h���̏�����
	@detail	�����o�n���h���Ƀn���h�������i�[
*/
bool Debug::CreateConsoleWindow()
{
	/*! �R���\�[���쐬 */
	if (!AllocConsole()) {
		ErrorLog("Debug Console Window is not create!");
		return false;
	}

	/*! �W�����o�͂Ɋ��蓖�Ă� */
	FILE*fp;

	/*! �V���ȃt�@�C�����J���X�g���[���ƌ��т��� */
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	/*! �E�B���h�E�n���h���擾 */
	m_hWndConsole = GetConsoleWindow();
	if (m_hWndConsole == nullptr) {
		ErrorLog("console window handle is \"nullptr\"!");
		return false;
	}

	/*! ���j���[�n���h���擾 */
	m_hMenu = GetSystemMenu(m_hWndConsole, false);
	if (m_hMenu == nullptr) {
		ErrorLog("console menu handle is \"nullptr\"!");
		return false;
	}
	return true;
}

/*!
	@fn		�R���\�[���E�B���h�E�̔j��
	@brief	���������R���\�[���E�B���h�E�̔j�����s��
	@detail	�n���h�����n���h�������擾���Ă�����E�B���h�E������Ă���̂�FreeConsole���Ăяo��
*/
void Debug::DestroyConsoleWindow()
{
	if (m_hWndConsole == nullptr) { return; }
	FreeConsole();
}

/*!
	@fn		����{�^���̖�����
	@brief	����{�^���������Ȃ�����
	@detail	RemoveMenu�ŕ���{�^���𖳌������Ă���
*/
void Debug::DisableCloseButton()
{
	/*! ���j���[�̕���{�^���𖳌��� */
	RemoveMenu(m_hMenu, SC_CLOSE, MF_BYCOMMAND);
}
