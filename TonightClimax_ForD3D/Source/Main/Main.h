/*!
	@file	Main.h
	@date	2018/11/10
	@author	�ԏ� �G�P
	@brief	�A�v���P�[�V�������C���G���g���[�|�C���g
*/

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <memory>
#include "../Window/Window.h"
#include "../Scene/Root/SceneRoot.h"
#include "../Singleton.h"

class Main
	:public Singleton<Main>
{
public:
	~Main();

	bool Initialize(HINSTANCE hInstance);
	void Finalize();
	void Release();
	void Loop();
	bool HighQualityTimmer();
	void SetUpFPS();
private:
	Main();
	friend class Singleton<Main>;
	void App();
	void Update();
	void Render();
	void SleepApp();

	static const std::string c_AppName;
	static const int	c_FPS;
	static const float	c_MinFrameTime;
	static const int c_WindowWidth = 1920, c_WindowHeight = 1080;

	HWND	m_hWnd;
	float	m_FrameTime;
	float	m_Fps;
	LARGE_INTEGER m_TimeStart;
	LARGE_INTEGER m_TimeEnd;
	LARGE_INTEGER m_TimeFreq;

	std::unique_ptr<Window>		m_pWindow;	/*< �E�B���h�E */
	std::unique_ptr<SceneRoot>	m_pRoot;	/*< �V�[���ϐ� */
};

