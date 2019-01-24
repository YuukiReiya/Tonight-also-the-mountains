/*!
	@file	Main.cpp
	@date	2018/11/10
	@author	番場 宥輝
	@brief	アプリケーションメインエントリーポイント
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
	@brief	名前空間
*/
using namespace std;

/*!
	@def	定数
*/
const std::string Main::c_AppName = "App";						/*!< アプリケーションの名前 */
const int	Main::c_FPS = 60;									/*! ゲームのターゲットFPS */
const float Main::c_MinFrameTime = 1.0f / Main::c_FPS;			/*!< 1フレーム辺りの経過時間 */

/*!
	@brief	コンストラクタ
*/
Main::Main() :m_pWindow(nullptr)
{
}

/*!
	@brief	デストラクタ
*/
Main::~Main()
{
	Finalize();
}

/*!
	@brief	初期化
*/
bool Main::Initialize(HINSTANCE hInstance)
{
	/*! ウィンドウのインスタンスを生成 */
	m_pWindow = make_unique<Window>();

	auto  tmp = To_TString(c_AppName);
	const auto appName = const_cast<LPCTSTR>(tmp.c_str());

	/*! ウィンドウ作成 */
	if (!m_pWindow->Initialize(&m_hWnd, hInstance,
		0, 0, c_WindowWidth, c_WindowHeight, appName)) {
		return false;
	}

	/*! Direct3Dデバイスの初期化 */
	//if (FAILED(Direct3D11::GetInstance().Initialize(m_hWnd))) { return false; }

	/*! DirectDevice初期化(d3d9のパーサー) */
	if (!DirectDevice::GetInstance().Init(m_hWnd)) {
		return false;
	}

	/*! デバッグコンソール表示 */
#ifdef DEBUG_CONSOLE

	/*! コンソールウィンドウの表示 */
	if (!Debug::CreateConsoleWindow()) { return false; }

	/*! 生成したコンソールウィンドウの閉じるボタンを無効化 */
	Debug::DisableCloseButton();

#endif

	/*! 初期化完了 */
	return true;
}

/*!
	@brief	破棄
*/
void Main::Finalize()
{
	Release();/*!< 変数の開放 */
}

/*!
	@brief	解放
*/
void Main::Release()
{

	/*! ウィンドウの開放 */
	m_pWindow.reset();

	/*! Direct3Dデバイスの開放 */
	//Direct3D11::GetInstance().Release();

	/*! オーディオデバイスの開放 */
}

/*!	
	@brief	アプリケーション処理の入り口
*/
void Main::Loop()
{
	//HRESULT hr;

	///*! オーディオデバイスの初期化 */
	//hr = AudioMaster::GetInstance().Initialize();
	//if (FAILED(hr)) {
	//	return;
	//}

	///*! シェーダー管理クラスの初期化 */
	//hr = ShaderManager::GetInstance().Initialize("../Resource/Shader/");
	//if (FAILED(hr)) {
	//	return;
	//}

	//	フォント
	Font::GetInstance().Init();

	/*! シーンの初期化 */
	m_pRoot = make_unique<SceneRoot>();
	m_pRoot->Initialize();

	/*! FPSの初期化 */
	SetUpFPS();

	/*! メッセージループ */
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
			App();/*!< App処理 */
		}
	}
	/*! コンソールウィンドウの破棄 */
#ifdef DEBUG_CONSOLE
	Debug::DestroyConsoleWindow();
#endif // DEBUG


}

/*
	@brief	高解像度タイマーが対応しているか確認
*/
bool Main::HighQualityTimmer()
{
	/*! QueryPerformanceFrequencyの対応を見る */
	if (!QueryPerformanceFrequency(&m_TimeFreq)) {
		ErrorLog("This PC is not fit QueryPerformanceFrequency!\n"
			"Sorry this project is exit!");
		return false;
	}

	return true;
}

/*!
	@brief	アプリケーション処理
*/
void Main::App()
{
	/*! FPS確認 */
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
	/*! FPSの調整方法で分岐 */
#ifdef Vsync
	/*! 更新処理 */
	Update();
	/*! 描画処理 */
	Render();
#else
	/*! 更新処理 */
	Update();
	/*! 描画処理 */
	Render();
	/*! FPS調整 */
	SleepApp();
#endif // Vsync
}

/*!
	@brief	更新
*/
void Main::Update()
{
	//	キーボード更新
	Input::GetInstance().Update();

	/*! シーンの更新 */
	m_pRoot->Update(m_pRoot.get());
}

/*!
	@brief	描画
*/
void Main::Render()
{
	if (SUCCEEDED(DirectDevice::GetInstance().GetDevice()->BeginScene())) {
		/*! 背景クリア色 */
		DWORD ClearColor = 0xff000000;
		/*! クリアターゲットのフラグ */
		DWORD flag = D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER;
		/*! 背景クリア */
		DirectDevice::GetInstance().GetDevice()->Clear(0, NULL, flag, ClearColor, 1.0f, 0);
		/*! 透過処理 */
		DirectDevice::GetInstance().SetRenderState();

		/*! シーンの描画 */
		m_pRoot->Render();

		/*! 描画終了 */
		DirectDevice::GetInstance().GetDevice()->EndScene();
	}

	/*! 描画反映 */
	DirectDevice::GetInstance().GetDevice()->Present(NULL, NULL, NULL, NULL);
}

/*!
	@brief	FPS調整の準備
*/
void Main::SetUpFPS()
{
	m_FrameTime = 0;
	/*! 初回の計算 */
	QueryPerformanceCounter(&m_TimeStart);
}
/*!
	@brief	アプリケーション処理のお休み
*/
void Main::SleepApp()
{
	/*! 今の時間を取得 */
	QueryPerformanceCounter(&m_TimeEnd);
	/*! 経過時間 */
	m_FrameTime = static_cast<float>(m_TimeEnd.QuadPart - m_TimeStart.QuadPart) / static_cast<float>(m_TimeFreq.QuadPart);
	if (m_FrameTime < c_MinFrameTime)
	{
		DWORD SleepTime = static_cast<DWORD>((c_MinFrameTime - m_FrameTime) * 1000);/*!< ズレ分 */
		timeBeginPeriod(1);	/*!< 分解性能を上げる */
		Sleep(SleepTime);	/*!< お休み */
		timeEndPeriod(1);	/*!< 戻す */
	}
	QueryPerformanceCounter(&m_TimeStart);
}