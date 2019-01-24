#pragma once
#include "../Singleton.h"
#include <DirectXMath.h>
#include <memory>
#include "../Tile/Tile.h"
#include "../Wall/Wall.h"
#include "../Table/Tables.h"
#include <vector>

struct Square
{
	DirectX::XMINT2 index;
	int info;
};

class Board
	:public Singleton<Board>
{
public:
	Board();
	~Board();

	void Init();
	void Render();
	void Load();
	Square*GetSquare(DirectX::XMINT2 index);

	//	�}�b�v�`�b�v�̃T�C�Y
	static const DirectX::XMFLOAT2 c_ChipSize;

	//	�g��k���̔{��
	static const float c_Scale;

	//	��ʂ̊�_(��ʂ̒��S)
	static const DirectX::XMFLOAT2 c_Pivot;

	//	�c���ɕ~���l�߂�}�b�v�`�b�v�̐�(�����`�̂���x��y�œ����l���g�p)
	static const DirectX::XMINT2 c_ChipNum;


	//	1�}�X�̑傫��
	DirectX::XMFLOAT2 GetSquareSize() { return { c_ChipSize.x * c_Scale, c_ChipSize.y * c_Scale }; }

	//	����
	DirectX::XMFLOAT2 GetLeftTop();

	//	�C���f�b�N�X�����̍��W�̒��S�ɕϊ�
	DirectX::XMFLOAT2 ConvertSquareCenter(DirectX::XMINT2 index);

	enum Info :int{
		EMPTY		= 0,	// �ʘH
		OBJECT		= 1,	// �I�u�W�F�N�g
		CUSTOMER	= 2,	// �q
	};

private:
	friend class Singleton<Board>;

	std::unique_ptr<Tile>m_pTile;
	std::unique_ptr<UpWall>m_pUWall;
	std::unique_ptr<LeftWall>m_pLWall;
	std::unique_ptr<DownWall>m_pDWall;
	std::unique_ptr<RightWall>m_pRWall;
	std::unique_ptr<Tables>m_pTable;

	std::vector<Square>m_Square;
};

