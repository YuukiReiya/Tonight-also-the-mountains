#pragma once
#include "Sprite.h"
#include "../Texture/Texture.h"
#include <string>
#include <unordered_map>
#include <memory>

/*!
	@brief	�ǂݍ���.csv����X�v���C�g��\��

*/
struct Data
{
	std::shared_ptr<Sprite> CSprite;
	std::shared_ptr<Texture> pTexture;
	HRESULT Render();
};

class SpriteReader
{
public:
	SpriteReader();
	~SpriteReader();

	typedef std::unordered_map<std::string, Data> ReadData;
	ReadData Load(std::string filePath);

	size_t GetCellCount(std::string str)const;
	std::string FindStrings(std::string& source, std::string&&findString);

	size_t c_ReadInfoOffset = 7;//FilePath�`scale.z�܂ł̌� - 1(�C���f�b�N�X��)
};

