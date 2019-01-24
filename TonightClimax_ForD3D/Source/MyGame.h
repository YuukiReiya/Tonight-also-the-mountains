/*
	@file	MyGame.h
	@date	2018/02/21
	@author	�ԏ� �G�P
	@brief	�g�������Ȋ֐��܂Ƃ�
*/
#pragma once
#include <iostream>
#include <tchar.h>
#include <Windows.h>

/*!
	@brief	�ÓI�z��̗v�f���擾
	@return	�ÓI�z��̗v�f��
*/
template<typename Array,std::size_t Size>
static inline std::size_t GetArraySize(const Array(&)[Size])
{
	return Size;
}

/*!
	@brief	�����R�[�h�ϊ�
	@return	�ϊ�������
*/
static inline std::basic_string<TCHAR> To_TString(std::string str) {
#ifdef _UNICODE
	std::wstring ret;
	size_t length = 0;
	ret.resize(MAX_PATH - 1);
	mbstowcs_s(&length, &ret.front(), ret.size(), str.c_str(), _TRUNCATE);
	return ret;
#else
	//TCHAR* ret = str;
	return str;
#endif // _UNICODE
}

static inline std::wstring To_WString(std::string str) 
{
	std::wstring ret;
	size_t length = 0;
	ret.resize(MAX_PATH - 1);
	mbstowcs_s(&length, &ret.front(), ret.size(), str.c_str(), _TRUNCATE);
	return ret;

}

/*!
	@brief	���b�Z�[�W�{�b�N�X�̃G���[�\��
*/
static inline void ErrorLog(std::string msg) {
#ifdef _UNICODE
	
	size_t length =0;
	WCHAR tmp[MAX_PATH] = { 0 };
	mbstowcs_s(&length, tmp, MAX_PATH, msg.c_str(), _TRUNCATE);
	MessageBoxW(NULL, tmp, _T("Error"), MB_OK);
#else
	MessageBoxA(NULL, msg.c_str(), _T("Error"), MB_OK);
#endif // _UNICODE

		
}

/*!
	@brief	WindowsAPI�̃G���[�o��
*/
static inline void WindowsErrorLog() {

	LPTSTR error;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // �f�t�H���g ���[�U�[���� 
		(LPTSTR)&error,
		0,
		NULL);
	MessageBox(NULL, error, _T("Error"), MB_OK);
}

/*!
	@brief	���S��delete
*/
template <typename T>
static inline void SAFE_DELETE(T* &p)
{
	/*! �s���S�Ȍ^�̃|�C���^��delete���悤�Ƃ����Ƃ��ɃR���p�C���G���[�ɂ��� */

	//	[�s���S�Ȍ^�̎��] �Q�l:https://msdn.microsoft.com/ja-jp/library/200xfxh6.aspx
	//	�E�����o�[���܂��w�肳��Ă��Ȃ��\���̌^�B
	//	�E�����o�[���܂��w�肳��Ă��Ȃ����p�̌^�B
	//	�E�������܂��w�肳��Ă��Ȃ��z��^�B

	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void)sizeof(type_must_be_complete);

	if (p != nullptr) {
		delete(p);
		p = nullptr;
	}
}

static HRESULT FailedAssert(std::string error, HRESULT* hr) {

	if (FAILED(&hr)) {
		ErrorLog(error);
	}
	return *hr;
}