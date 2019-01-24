/*!
	@file	Entry.cpp
	@date	2018/02/08
	@author	�ԏ� �G�P
	@brief	Windows�̃G���g���[�|�C���g
*/
#pragma once
#include "Main/Main.h"
#include "MemoryLeaks.h"

#include <stdio.h>
#include <tchar.h>
#include <locale>
/*!
	@var	g_pMain
*/
//Main*	g_pMain;

/*!
	@brief	�G���g���[�|�C���g
*/
INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, INT) 
{
	/*! ���������[�N�ӏ����� */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//���������[�N�����
#endif
#ifdef _UNICODE
	/*! �����R�[�h�ݒ� */
	setlocale(LC_ALL, "JPN");
#endif // _UNICODE


	/*! �C���X�^���X�̐��� */
	/*g_pMain = new Main;
	if (!g_pMain) {
		return 0;
	}*/

	/*! ���𑜓x�^�C�}�[�֑Ή��𒲂ׁA���Ή��Ȃ�v���O�������I�������� */
	//if (!g_pMain->HighQualityTimmer()) {
	//	g_pMain->Release();
	//	delete(g_pMain);
	//	g_pMain = nullptr;
	//	return 0;
	//}
	if (!Main::GetInstance().HighQualityTimmer()) {
		Main::GetInstance().Release();
		/*delete(g_pMain);
		g_pMain = nullptr;*/
		return 0;
	}

	/*! �A�v���P�[�V�����̏����������A���C�����[�v�� */
	//if (g_pMain->Initialize(hInstance)) {
	//	g_pMain->Loop();
	//}
	if (Main::GetInstance().Initialize(hInstance)) {
		Main::GetInstance().Loop();
	}


	//delete(g_pMain);

	return 0;
}

