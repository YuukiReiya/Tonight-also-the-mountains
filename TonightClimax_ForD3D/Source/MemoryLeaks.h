/*
	@file	MemoryLeaks.h
	@date	2018/02/11
	@author	�ԏ� �G�P
	@brief	���������[�N����}�N����`�w�b�_�[
*/
#pragma once
#if defined DEBUG || defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif