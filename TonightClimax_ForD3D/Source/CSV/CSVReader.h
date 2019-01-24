/*
	@file	CSVReader.h
	@date	2019/01/09
	@author	�ԏ� �G�P
	@brief	CSV�ǂݎ��N���X
	@detail	�ǂݍ��񂾏��̓Z�����Ƃ�string�^�Ŋi�[����
*/
#pragma once
#include "../Singleton.h"
#include <string>
#include <vector>

class CSVReader
	:public Singleton<CSVReader>
{
public:
	/*!
		@brief	�f�X�g���N�^
	*/
	~CSVReader();

	/*!
		@fn			Load
		@brief		.csv�̓ǂݍ���
		@param[in]	�t�@�C���̃p�X
		@return		����:S_OK ���s:E_FAIL
	*/
	long Load(std::string filePath);

	/*!
		@fn			GetCells
		@brief		�ǂݍ���.csv�̃f�[�^��Ԃ�
		@detail		[y][x]�ɕ�����^�Ŋi�[����Ă���
		@return		�ǂݍ��񂾃Z��(������)���������񎟌��̉ϒ��z��
	*/
	std::vector<std::vector<std::string>>GetCells()const { return m_Cells; }

private:
	/*!
		@brief	�R���X�g���N�^
	*/
	CSVReader();

	/*!
		@brief	�V���O���g��
	*/
	friend class Singleton<CSVReader>;

	/*!
		@fn			GetDelimiterCount
		@brief		������̒��Ɋ܂܂��Z���̋�؂蕶���̌���Ԃ�
		@param[in]	���蕶����
		@return		�����񒆂Ɋ܂܂���؂蕶���̌�
	*/
	size_t GetDelimiterCount(std::string str)const;

	/*!
		@var		m_Cells
		@brief		�ǂݍ���.csv�̃Z���Ɋi�[���ꂽ��������i�[
		@detail		[y][x]�Ɋi�[�����
	*/
	std::vector<std::vector<std::string>> m_Cells;

	/*!
		@var		c_Delimiter
		@brief		�Z���̋�؂蕶��
	*/
	static const std::string c_Delimiter;

};

