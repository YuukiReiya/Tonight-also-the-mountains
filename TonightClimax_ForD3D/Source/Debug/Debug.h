/*!
	@file	Debug.h
	@date	2018/11/20
	@author	�ԏ� �G�P
	@brief	�f�o�b�O�֘A�̃N���X
	@detail	�e�N���X�Ŏg���Ă���V���{���̐錾���܂߂�
			�Q�Ƃ͕s�v�Ȃ̂Ń����o�͑S��static�Ő錾�y�ђ�`
*/
#pragma once
#include <Windows.h>

/*! 
	@brief	�f�o�b�O�p�V���{���̐錾 
	@detail	Release�r���h���ɗL���ɂȂ�Ȃ��悤�}�N���ň͂�
*/
#if defined DEBUG || defined _DEBUG

/*!
	@def	DEBUG_FPS	
	@brief	FPS��\������
	@detail	Main�֐�����SetWindowText���Ăяo���E�B���h�E���̕�����FPS�̕\��������
*/
#define DEBUG_FPS

/*!
	@def	DEBUG_CONSOLE
	@brief	�f�o�b�O�R���\�[���̐���
	@detail	Win32API�̊֐����g�p���Ă���
*/
//#define DEBUG_CONSOLE

/*!
	@def	DEBUG_SPRITE
	@brief	�X�v���C�g�N���X�̃f�o�b�O�V���{��
	@detail	�X�v���C�g�N���X�̃f�o�b�O�����̗L����
*/
//#define DEBUG_SPRITE

/*!
	@def	DEBUG_TEXTURE
	@brief	�e�N�X�`���N���X�̃f�o�b�O�V���{��
	@detail	�e�N�X�`���N���X�̃f�o�b�O�����̗L����
*/
#define DEBUG_TEXTURE

#endif // _DEBUG

/*!
	@brief	�f�o�b�O�N���X
*/
class Debug
{
public:

	/*!
		@fn		�R���\�[���E�B���h�E�̐���
		@brief	�R���\�[���E�B���h�E�̍쐬�ƃn���h���̏�����
		@detail	�����o�n���h���Ƀn���h�������i�[
		@return	true:���� false:���s
	*/
	static bool CreateConsoleWindow();

	/*!
		@fn		�R���\�[���E�B���h�E�̔j��
		@brief	���������R���\�[���E�B���h�E�̔j�����s��
		@detail	�n���h�����n���h�������擾���Ă�����E�B���h�E������Ă���̂�FreeConsole���Ăяo��
	*/
	static void DestroyConsoleWindow();

	/*!
		@fn		����{�^���̖�����
		@brief	RemoveMenu�ŕ���{�^���𖳌������Ă���
		@detail	CreateConsoleWindow�ŃE�B���h�E�̍쐬��ɌĂяo��
	*/
	static void DisableCloseButton();
private:
	Debug()		= delete;
	~Debug()	= delete;
	static HWND  m_hWndConsole;	/*!< �R���\�[���E�B���h�E�n���h�� */
	static HMENU m_hMenu;		/*!< ���j���[�n���h�� */
};

