/*!
	@file	Main.cpp
	@date	2018/11/10
	@author	�ԏ� �G�P
	@brief	�A�v���P�[�V�������C���G���g���[�|�C���g
*/
#include "../Common/DirectDevice.h"
#include <tchar.h>
#include "Main.h"
#include "../Debug/Debug.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include "../Input/Input.h"
#include "../Font/Font.h"

/*!
	@brief	���O���
*/
using namespace std;

/*!
	@def	�萔
*/
const std::string Main::c_AppName = "App";						/*!< �A�v���P�[�V�����̖��O */
const int	Main::c_FPS = 60;									/*! �Q�[���̃^�[�Q�b�gFPS */
const float Main::c_MinFrameTime = 1.0f / Main::c_FPS;			/*!< 1�t���[���ӂ�̌o�ߎ��� */

/*!
	@brief	�R���X�g���N�^
*/
Main::Main() :m_pWindow(nullptr)
{
}

/*!
	@brief	�f�X�g���N�^
*/
Main::~Main()
{
	Finalize();
}

/*!
	@brief	������
*/
bool Main::Initialize(HINSTANCE hInstance)
{
	/*! �E�B���h�E�̃C���X�^���X�𐶐� */
	m_pWindow = make_unique<Window>();

	auto  tmp = To_TString(c_AppName);
	const auto appName = const_cast<LPCTSTR>(tmp.c_str());

	/*! �E�B���h�E�쐬 */
	if (!m_pWindow->Initialize(&m_hWnd, hInstance,
		0, 0, c_WindowWidth, c_WindowHeight, appName)) {
		return false;
	}

	/*! Direct3D�f�o�C�X�̏����� */
	//if (FAILED(Direct3D11::GetInstance().Initialize(m_hWnd))) { return false; }

	/*! DirectDevice������(d3d9�̃p�[�T�[) */
	if (!DirectDevice::GetInstance().Init(m_hWnd)) {
		return false;
	}

	/*! �f�o�b�O�R���\�[���\�� */
#ifdef DEBUG_CONSOLE

	/*! �R���\�[���E�B���h�E�̕\�� */
	if (!Debug::CreateConsoleWindow()) { return false; }

	/*! ���������R���\�[���E�B���h�E�̕���{�^���𖳌��� */
	Debug::DisableCloseButton();

#endif

	/*! ���������� */
	return true;
}

/*!
	@brief	�j��
*/
void Main::Finalize()
{
	Release();/*!< �ϐ��̊J�� */
}

/*!
	@brief	���
*/
void Main::Release()
{

	/*! �E�B���h�E�̊J�� */
	m_pWindow.reset();

	/*! Direct3D�f�o�C�X�̊J�� */
	//Direct3D11::GetInstance().Release();

	/*! �I�[�f�B�I�f�o�C�X�̊J�� */
}

/*!	
	@brief	�A�v���P�[�V���������̓����
*/
void Main::Loop()
{
	//HRESULT hr;

	///*! �I�[�f�B�I�f�o�C�X�̏����� */
	//hr = AudioMaster::GetInstance().Initialize();
	//if (FAILED(hr)) {
	//	return;
	//}

	///*! �V�F�[�_�[�Ǘ��N���X�̏����� */
	//hr = ShaderManager::GetInstance().Initialize("../Resource/Shader/");
	//if (FAILED(hr)) {
	//	return;
	//}

	//	�t�H���g
	Font::GetInstance().Init();

	/*! �V�[���̏����� */
	m_pRoot = make_unique<SceneRoot>();
	m_pRoot->Initialize();

	/*! FPS�̏����� */
	SetUpFPS();

	/*! ���b�Z�[�W���[�v */
	MSG msg{ 0 };
	SecureZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			App();/*!< App���� */
		}
	}
	/*! �R���\�[���E�B���h�E�̔j�� */
#ifdef DEBUG_CONSOLE
	Debug::DestroyConsoleWindow();
#endif // DEBUG


}

/*
	@brief	���𑜓x�^�C�}�[���Ή����Ă��邩�m�F
*/
bool Main::HighQualityTimmer()
{
	/*! QueryPerformanceFrequency�̑Ή������� */
	if (!QueryPerformanceFrequency(&m_TimeFreq)) {
		ErrorLog("This PC is not fit QueryPerformanceFrequency!\n"
			"Sorry this project is exit!");
		return false;
	}

	return true;
}

/*!
	@brief	�A�v���P�[�V��������
*/
void Main::App()
{
	/*! FPS�m�F */
#ifdef DEBUG_FPS
	static DWORD time = 0;
	static int frame = 0;
	frame++;
	char str[50];
	sprintf_s(str, "fps=%d", frame);
	if (timeGetTime() - time > 1000) {
		time = timeGetTime();
		frame = 0;

		auto tmp = To_TString(str);
		const auto fps = const_cast<LPTSTR>(tmp.c_str());
		if (!SetWindowText(m_hWnd, fps)) {
			WindowsErrorLog();
		}
	}
#endif
	/*! FPS�̒������@�ŕ��� */
#ifdef Vsync
	/*! �X�V���� */
	Update();
	/*! �`�揈�� */
	Render();
#else
	/*! �X�V���� */
	Update();
	/*! �`�揈�� */
	Render();
	/*! FPS���� */
	SleepApp();
#endif // Vsync
}

/*!
	@brief	�X�V
*/
void Main::Update()
{
	//	�L�[�{�[�h�X�V
	Input::GetInstance().Update();

	/*! �V�[���̍X�V */
	m_pRoot->Update(m_pRoot.get());
}

/*!
	@brief	�`��
*/
void Main::Render()
{
	if (SUCCEEDED(DirectDevice::GetInstance().GetDevice()->BeginScene())) {
		/*! �w�i�N���A�F */
		DWORD ClearColor = 0xff000000;
		/*! �N���A�^�[�Q�b�g�̃t���O */
		DWORD flag = D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER;
		/*! �w�i�N���A */
		DirectDevice::GetInstance().GetDevice()->Clear(0, NULL, flag, ClearColor, 1.0f, 0);
		/*! ���ߏ��� */
		DirectDevice::GetInstance().SetRenderState();

		/*! �V�[���̕`�� */
		m_pRoot->Render();

		/*! �`��I�� */
		DirectDevice::GetInstance().GetDevice()->EndScene();
	}

	/*! �`�攽�f */
	DirectDevice::GetInstance().GetDevice()->Present(NULL, NULL, NULL, NULL);
}

/*!
	@brief	FPS�����̏���
*/
void Main::SetUpFPS()
{
	m_FrameTime = 0;
	/*! ����̌v�Z */
	QueryPerformanceCounter(&m_TimeStart);
}
/*!
	@brief	�A�v���P�[�V���������̂��x��
*/
void Main::SleepApp()
{
	/*! ���̎��Ԃ��擾 */
	QueryPerformanceCounter(&m_TimeEnd);
	/*! �o�ߎ��� */
	m_FrameTime = static_cast<float>(m_TimeEnd.QuadPart - m_TimeStart.QuadPart) / static_cast<float>(m_TimeFreq.QuadPart);
	if (m_FrameTime < c_MinFrameTime)
	{
		DWORD SleepTime = static_cast<DWORD>((c_MinFrameTime - m_FrameTime) * 1000);/*!< �Y���� */
		timeBeginPeriod(1);	/*!< ���𐫔\���グ�� */
		Sleep(SleepTime);	/*!< ���x�� */
		timeEndPeriod(1);	/*!< �߂� */
	}
	QueryPerformanceCounter(&m_TimeStart);
}