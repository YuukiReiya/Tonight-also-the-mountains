/*
	@file	CSVReader.h
	@date	2019/01/09
	@author	番場 宥輝
	@brief	CSV読み取りクラス
	@detail	読み込んだ情報はセルごとにstring型で格納する
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
		@brief	デストラクタ
	*/
	~CSVReader();

	/*!
		@fn			Load
		@brief		.csvの読み込み
		@param[in]	ファイルのパス
		@return		成功:S_OK 失敗:E_FAIL
	*/
	long Load(std::string filePath);

	/*!
		@fn			GetCells
		@brief		読み込んだ.csvのデータを返す
		@detail		[y][x]に文字列型で格納されている
		@return		読み込んだセル(文字列)が入った二次元の可変長配列
	*/
	std::vector<std::vector<std::string>>GetCells()const { return m_Cells; }

private:
	/*!
		@brief	コンストラクタ
	*/
	CSVReader();

	/*!
		@brief	シングルトン
	*/
	friend class Singleton<CSVReader>;

	/*!
		@fn			GetDelimiterCount
		@brief		文字列の中に含まれるセルの区切り文字の個数を返す
		@param[in]	判定文字列
		@return		文字列中に含まれる区切り文字の個数
	*/
	size_t GetDelimiterCount(std::string str)const;

	/*!
		@var		m_Cells
		@brief		読み込んだ.csvのセルに格納された文字列を格納
		@detail		[y][x]に格納される
	*/
	std::vector<std::vector<std::string>> m_Cells;

	/*!
		@var		c_Delimiter
		@brief		セルの区切り文字
	*/
	static const std::string c_Delimiter;

};

