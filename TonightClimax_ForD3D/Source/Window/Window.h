/*!
	@file	Window.h
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	WindowsAPI�̃E�B���h�E����
*/
#pragma once
#include <Windows.h>

class Window
{
public:
	/*!
		@brief	�R���X�g���N�^
	*/
	Window() = default;

	/*!
		@brief	�f�X�g���N�^
	*/
	~Window();

	/*!
		@fn			���b�Z�[�W�v���V�[�W��
		@brief		�E�B���h�E�v���V�[�W���̒��g
		@detail		win32��WndProc���I�[�o�[���C�h���Ă���
		@param[in]	�E�B���h�E�̃n���h��
		@param[in]	���b�Z�[�W�̎w��
		@param[in]	���b�Z�[�W�̒ǉ�
		@param[in]	���b�Z�[�W�̒ǉ�
		@return		���b�Z�[�W
	*/
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/*!
		@fn			�C�j�V�����C�Y
		@brief		������
		@detail		win32�̃E�B���h�E�쐬
		@param[in]	�E�B���h�E�n���h���̎Q��
		@param[in]	�C���X�^���X�n���h��
		@param[in]	�����ʒux
		@param[in]	�����ʒuy
		@param[in]	����
		@param[in]	�c��
		@param[in]	�E�B���h�E�̖��O
		@return		true:���� false:���s
	*/
	bool Initialize(HWND* hWnd,HINSTANCE hInstance,INT iX,INT iY,INT iWidth,INT iHeight, LPCTSTR WindowName);
};

