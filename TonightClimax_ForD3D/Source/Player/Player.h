#pragma once
#include "../Texture/Texture.h"
#include "../Sprite/Sprite.h"
#include <memory>
#include <DirectXMath.h>
#include "../Board/Board.h"
#include "../Character/ICharacter.h"

struct Grid
{
	Square *lt, *rt, *lb, *rb;
};

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
private:
	//	キャラクターチップに対応
	enum Way :int
	{
		DOWN	= 0,
		LEFT	= 1,
		RIGHT	= 2,
		UP		= 3,
	};

	void Input();
	void Stay();
	void Move();
	void MovePreparation();
	void MoveFinish();
	bool GetIsMoveDir();
	int GetIsMove(DirectX::XMINT2 ltIndex);
	Grid GetGrid(DirectX::XMINT2 ltIndex);
	//void SetChara()
	DirectX::XMINT2 ConvertDirection(Way way);

	static const DirectX::XMINT2 c_SplitNum;
	static const DirectX::XMINT2 c_ltInitIndex;
	static const std::string c_FilePath;
	static const float	c_MovingSpeed;
	static const float	c_MovingDistance;
	static const int	c_SwitchingFrame;

	std::unique_ptr<Sprite>m_pSprite;
	std::unique_ptr<Texture>m_pTex;


	static const DirectX::XMINT2 c_dLeft;
	static const DirectX::XMINT2 c_dRight;
	static const DirectX::XMINT2 c_dUp;
	static const DirectX::XMINT2 c_dDown;

	DirectX::XMFLOAT2	m_NextPos;
	DirectX::XMFLOAT2	m_CharaPos;
	DirectX::XMINT2		m_ltIndex;
	Way					m_eWay;
	bool				m_isMoving;
	int					m_SwitchTexCnt;
	int					m_FigureIndex;

	std::weak_ptr<ICharacter>m_weakChara;
};

