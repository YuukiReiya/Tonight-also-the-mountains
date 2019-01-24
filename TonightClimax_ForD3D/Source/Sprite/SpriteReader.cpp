#include "SpriteReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "../MyGame.h"
#include "../MemoryLeaks.h"

using namespace std;

SpriteReader::SpriteReader()
{
}


SpriteReader::~SpriteReader()
{
}

SpriteReader::ReadData SpriteReader::Load(string filePath)
{
	ifstream ifs(filePath);
	if (!ifs) { ErrorLog("ƒtƒ@ƒCƒ‹“Ç‚İ‚İ‚É¸”s"); }


	vector<string> data;
	data.clear();
	data.shrink_to_fit();
	string sstream = "";

	//	ƒZƒ‹‚Ìî•ñ‚ğ“Ç‚İ‚Ş
	while (getline(ifs,sstream))
	{
		string tmp = sstream;

		int cellNum = GetCellCount(tmp);
		for (int i = 0; i < cellNum; ++i) {

			auto cell = FindStrings(tmp, ",");
			data.push_back(cell);
		}
	}

	vector<Data>vd;
	ReadData ret;// = new ReadData();
	int index = 0;
	//	
	for (size_t i = c_ReadInfoOffset; i < data.size();) {

		HRESULT hr;
		string error;
		string hash, path;
		int cnt = c_ReadInfoOffset;
		float width, height;
		D3DXVECTOR2 pos;
		float scale;

		hash	= data[i++];
		path	= data[i++];
		width	= static_cast<float>(atof(data[i++].c_str()));
		height	= static_cast<float>(atof(data[i++].c_str()));
		pos.x	= static_cast<float>(atof(data[i++].c_str()));
		pos.y	= static_cast<float>(atof(data[i++].c_str()));
		scale	= static_cast<float>(atof(data[i++].c_str()));

		Data empty;
		vd.push_back(empty);
		vd[index].CSprite = make_shared<Sprite>();
		vd[index].pTexture = make_shared<Texture>();

		hr = vd[index].pTexture->Load(path);
		error = "sprite[" + std::to_string(index) + "] is Load failed!";
		FailedAssert(error, &hr);
		vd[index].CSprite->SetPos(pos);
		vd[index].CSprite->SetSpriteSize(width, height);
		vd[index].CSprite->SetSizeScaling(scale);

		//	“o˜^
		ret[hash] = vd[index];

		//ret[hash].CSprite = make_unique<API::Sprite>();
		//ret[hash].CSprite = move(vd[index].CSprite);
		//ret[hash].pTexture = make_unique<API::Texture>();
		//ret[hash].pTexture = move(vd[index].pTexture);
	}

	return ret;
}

size_t SpriteReader::GetCellCount(std::string str) const
{
	size_t ret = 0;
	size_t tmp = 0;
	while (tmp != string::npos)
	{
		tmp = str.find(",");
		str = str.substr(tmp + 1);
		ret++;
	}

	return ret;
}

std::string SpriteReader::FindStrings(std::string & source, std::string && findString)
{
	size_t index = 0;
	index = source.find(findString);
	auto ret = source.substr(0, index);
	source = source.substr(index + 1);
	return ret;
}

HRESULT Data::Render()
{
	CSprite->Render(pTexture->GetTexture());
	return S_OK;
}
