/*!
	@file	Window.cpp
	@date	2018/02/22
	@author	�ԏ� �G�P
	@brief	WindowsAPI�̃E�B���h�E����
*/
#include "Window.h"
#include "../MemoryLeaks.h"

/*!
	@brief	�v���g�^�C�v�錾
	@detail	�R�[���o�b�N�֐�WndProc�̃v���g�^�C�v�錾
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*!
	@var	g_pWindow
	@brief	�E�B���h�E�̃C���X�^���X�錾
*/
Window*	g_pWindow = NULL;

/*!
	@brief	�E�B���h�E�v���V�[�W��
	@detail	�R�[���o�b�N�֐�WndProc�̃I�[�o�[���C�h
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
}

/*!
	@brief	�f�X�g���N�^
*/
Window::~Window()
{
}

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
LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
			/*! Esc�L�[�������ꂽ�� */
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
		/*! �E�B���h�E���j�����ꂽ�Ƃ� */
	case WM_DESTROY:
		PostQuitMessage(0);	/*!< WM_QUIT���b�Z�[�W�����b�Z�[�W�L���[�ɑ��� */
		break;
	}
	/*! �f�t�H���g�̃��b�Z�[�W�������s�� */
	return DefWindowProc(hWnd, msg, wParam, lParam);
}



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
bool Window::Initialize(HWND* hWnd, HINSTANCE hInstance, INT iX, INT iY, INT iWidth, INT iHeight, LPCTSTR WindowName)
{
	g_pWindow = this;
	/*! �E�B���h�E�̒�` */
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	/*! �E�B���h�E�̍쐬 */
	*hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);
	if (!hWnd)
	{
		return false;
	}
	/*! �E�B���h�E�̕\�� */
	ShowWindow(*hWnd, SW_SHOW);
	UpdateWindow(*hWnd);

	return true;
}