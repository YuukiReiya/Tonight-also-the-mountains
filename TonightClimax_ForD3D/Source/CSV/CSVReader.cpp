#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include "../MyGame.h"

using namespace std;

const string CSVReader::c_Delimiter = ",";

CSVReader::CSVReader()
{
}

CSVReader::~CSVReader()
{
}



long CSVReader::Load(std::string filePath)
{
	m_Cells.clear();
	ifstream ifs(filePath);
	if (!ifs) { 
		ErrorLog("ファイル読み込みに失敗"); 
		return E_FAIL;
	}

	string stream;
	size_t row = 0;	//	行数

	//	セルの情報を変数に格納
	while (getline(ifs, stream))
	{
		vector<string> line;
		line.shrink_to_fit();
		auto length = GetDelimiterCount(stream);

		//	文字列の先頭から区切り文字が出てくるまでの文字列をセルに順次格納する
		for (size_t i = 0; i < length; i++)
		{
			auto offset = stream.find(c_Delimiter);
			auto cell = stream.substr(0, offset);
			stream = stream.substr(offset + 1);
			line.push_back(cell);
		}
		m_Cells.push_back(line);
	}

	return S_OK;
}

size_t CSVReader::GetDelimiterCount(std::string str) const
{
	size_t ret, offset;
	ret = offset = 0;
	while (!str.empty() && offset != string::npos) {
		offset = str.find(c_Delimiter);
		str = str.substr(offset + 1);
		ret++;
	}
	return ret;
}

