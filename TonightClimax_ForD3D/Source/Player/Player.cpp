#include "Player.h"
#include "../Input/Input.h"
#include "../Character/Controller/CharacterController.h"
using namespace std;
using namespace DirectX;

//	�摜������
const XMINT2 Player::c_SplitNum = { 3,4 };

//	�摜�p�X
const string Player::c_FilePath = { "../Resource/Image/chara_player.png" };

//	1�t���[��������̈ړ���
const float Player::c_MovingSpeed = Board::GetInstance().GetSquareSize().x / 20;

//	�ړ�����
const float Player::c_MovingDistance = Board::GetInstance().GetSquareSize().y / 2;

//	�e�N�X�`���؂�ւ��t���[��
const int Player::c_SwitchingFrame = 6;

//	����
const XMINT2 Player::c_dLeft	= { -1, 0 };
const XMINT2 Player::c_dRight	= {  1, 0 };
const XMINT2 Player::c_dUp		= {  0,-1 };
const XMINT2 Player::c_dDown	= {  0, 1 };

//	�������W
const XMINT2 Player::c_ltInitIndex = { 12,6 };

Player::Player() 
	:	m_isMoving(false),
		m_eWay(Way::DOWN),
		m_SwitchTexCnt(0),
		m_FigureIndex(1)
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_pSprite	= make_unique<Sprite>();
	m_pTex		= make_unique<Texture>();

	m_pTex->Load(c_FilePath);
	m_pSprite->SetSpriteSize(Board::c_ChipSize.x, Board::c_ChipSize.y);
	m_pSprite->SetSizeScaling(Board::c_Scale);
	m_pSprite->SetSplit(c_SplitNum.x, c_SplitNum.y);

	m_ltIndex = c_ltInitIndex;
	m_CharaPos = Board::GetInstance().ConvertSquareCenter(m_ltIndex);
	m_NextPos = m_CharaPos;
	m_pSprite->SetPos({ m_CharaPos.x,m_CharaPos.y });

	auto& cc = CharacterController::GetInstance();
}

void Player::Update()
{
	Stay();
	Move();
}
#include "../Debug/DebugDraw.h"
void Player::Render()
{
	D3DXVECTOR2 pos = {
		m_CharaPos.x,
		m_CharaPos.y
	};
	XMINT2 uv = {
		m_FigureIndex,
		m_eWay
	};
	m_pSprite->SetPos(pos);
	m_pSprite->RenderAtlas(m_pTex->GetTexture(), uv.x, uv.y);

#define debug
#ifdef debug
	auto&draw = DebugDraw::GetInstance();

	auto size = Board::GetInstance().GetSquareSize();
	auto way = ConvertDirection(m_eWay);
	pos.x -= size.x / 4;
	pos.y -= size.y / 4;

	pos.x += way.x*0.5f*size.x;
	pos.y += way.y*0.5f*size.y;

	for (int y = 0; y < 2; ++y) {
		for (int x = 0; x < 2; ++x) {
			draw.DrawSquare({ pos.x + x * size.x/2,pos.y + y * size.y/2 }, size.x/2, size.y/2, draw.RED);
		}
	}

#endif // debug


}

void Player::Input()
{
	auto&input = Input::GetInstance();

	if (input.GetKey(input.LEFT)) {
		m_eWay = LEFT;
		if (GetIsMoveDir()) {
			MovePreparation();
			return;
		}
	}

	if (input.GetKey(input.RIGHT)) {
		m_eWay = RIGHT;
		if (GetIsMoveDir()) {
			MovePreparation();
			return;
		}
	}

	if (input.GetKey(input.UP)) {
		m_eWay = UP;
		if (GetIsMoveDir()) {
			MovePreparation(); 
			return;
		}
	}

	if (input.GetKey(input.DOWN)) {
		m_eWay = DOWN;
		if (GetIsMoveDir()) {
			MovePreparation();
			return;
		}
	}

}

void Player::Stay()
{
	if (m_isMoving) { return; }

	//	�C���f�b�N�X�X�V


	Input();
}

void Player::Move()
{
	if (!m_isMoving) { return; }

	//	�J�E���^
	m_SwitchTexCnt++;
	if (m_SwitchTexCnt > c_SwitchingFrame) {
		m_FigureIndex = ++m_FigureIndex < c_SplitNum.x ? m_FigureIndex : 0;
		m_SwitchTexCnt = 0;
	}

	float speed = c_MovingSpeed;
	auto way = ConvertDirection(m_eWay);
	XMFLOAT2 velocity = {
		way.x * speed,
		way.y * speed
	};

	m_CharaPos.x += velocity.x;
	m_CharaPos.y += velocity.y;

	//	�ړ���ɃL������������
	if (!m_weakChara.expired()) {
		auto pChara = m_weakChara.lock();
		pChara->Move(velocity);
	}

	bool sign = (way.x+way.y) > 0;

	//	��
	if (sign) {

		if (m_CharaPos.x >= m_NextPos.x&&m_CharaPos.y >= m_NextPos.y) {
			MoveFinish();
		}
	}
	//	��
	else {

		if (m_CharaPos.x <= m_NextPos.x&&m_CharaPos.y <= m_NextPos.y) {
			MoveFinish();
		}
	}
}

void Player::MovePreparation()
{
	auto way = ConvertDirection(m_eWay);
	m_NextPos = m_CharaPos;
	m_NextPos.x += way.x*c_MovingDistance;
	m_NextPos.y += way.y*c_MovingDistance;
	m_isMoving = true;
}

void Player::MoveFinish()
{
	auto way = ConvertDirection(m_eWay);
	m_CharaPos = m_NextPos;
	m_isMoving = false;
	m_ltIndex.x += way.x;
	m_ltIndex.y += way.y;

	//	�����Ă�L�����̈ړ�
	if (!m_weakChara.expired()) {
		auto c = m_weakChara.lock();
		c->MoveFinish(way);
		m_weakChara.reset();
	}
}

//	�ړ���̍��W���ړ��\������
bool Player::GetIsMoveDir()
{
	auto dir = ConvertDirection(m_eWay);
	auto index = m_ltIndex;

	//	����␳(���オ���S�̂��߈ړ��悪�E�܂��͉��̎��A+�P�}�X��̔���ɂ���)
	const int comp = (dir.x + dir.y) > 0 ? 2 : 1;

	//	�ړ���̔���ӏ�
	index.x += dir.x*comp;
	index.y += dir.y*comp;

	m_weakChara.reset();
	
	auto& bd = Board::GetInstance();
	auto& cc = CharacterController::GetInstance();

	auto sq = bd.GetSquare(index);
	if (sq == nullptr || sq->info == Board::OBJECT) { return false; }

	//	�אڃ}�X
	index.x += dir.y != 0 ? 1 : 0;
	index.y += dir.x != 0 ? 1 : 0;

	auto adjsq = bd.GetSquare(index);
	if (adjsq == nullptr || adjsq->info == Board::OBJECT) { return false; }

	if (sq->info == Board::EMPTY&&adjsq->info == Board::EMPTY) { return true; }
	else if(sq->info == Board::CUSTOMER&&adjsq->info == Board::CUSTOMER){}
	else { return false; }
	
	auto pos = m_CharaPos;
	pos.x += dir.x * bd.GetSquareSize().x;
	pos.y += dir.y * bd.GetSquareSize().y;

	m_weakChara = cc.GetCharacter(pos);
	if (m_weakChara.expired()) {

		index.x = sq->index.x + dir.x;
		index.y = sq->index.y + dir.y;
		auto ret1 = bd.GetSquare(index);
		index.x = adjsq->index.x + dir.x;
		index.y = adjsq->index.y + dir.y;
		auto ret2 = bd.GetSquare(index);
		if (ret1->info == Board::EMPTY&&ret2->info == Board::EMPTY) {
			return true;
		}
		return false;
	}
	else {
		index.x = sq->index.x - dir.x;
		index.y = sq->index.y - dir.y;
		auto ret1 = bd.GetSquare(index);
		index.x = adjsq->index.x - dir.x;
		index.y = adjsq->index.y - dir.y;
		auto ret2 = bd.GetSquare(index);
		if (ret1->info == Board::EMPTY&&ret2->info == Board::EMPTY) {
			return true;
		}
		return false;
	}

	return false;
	//auto pos = m_CharaPos;
	//pos.x += dir.x*bd.GetSquareSize().x;
	//pos.y += dir.y*bd.GetSquareSize().y;

	//m_weakChara = cc.GetCharacter(pos);
	//pos.x += dir.x*bd.GetSquareSize().x * 2;
	//pos.y += dir.y*bd.GetSquareSize().y * 2;
	//weak_ptr<ICharacter>tmp = cc.GetCharacter(pos);
	//return tmp.expired();

	//--------

	//auto lt = bd.GetSquare(m_ltIndex);
	//index.x = lt->index.x + dir.x * (2);
	//index.y = lt->index.y + dir.y * (2);

	//auto tmp = bd.GetSquare(index);

	//if (tmp == nullptr || tmp->info != Board::EMPTY) { return false; }

	//index.x = adjsq->index.x + dir.x * 2;
	//index.y = adjsq->index.y + dir.y * 2;
	//tmp = bd.GetSquare(index);

	//if (tmp == nullptr || tmp->info != Board::EMPTY) { return false; }

	//m_weakChara = cc.GetCharacter({ m_ltIndex.x + dir.x,m_ltIndex.y + dir.y });
	//return true;
}

//	4�}�X�̏��𔻒�
int Player::GetIsMove(DirectX::XMINT2 ltIndex)
{
	auto grid = GetGrid(ltIndex);
	Square* ptr[] = { grid.lt,grid.rt, grid.lb, grid.rb, };

	//	�͈͊O �܂��� �ړ��s��
	for (auto it : ptr) {
		if (it == nullptr || it->info == Board::OBJECT) { return Board::OBJECT; }
	}

	//	���q
	for (auto it : ptr) {
		if (it->info == Board::CUSTOMER) { 
			return Board::CUSTOMER; 
		}
	}

	//	�ʘH
	return Board::EMPTY;
}

Grid Player::GetGrid(DirectX::XMINT2 ltIndex)
{
	Grid ret;
	XMINT2 offset{ 1,1 };
	auto&bd = Board::GetInstance();
	ret.lt = bd.GetSquare(ltIndex);
	ret.rt = bd.GetSquare({ ltIndex.x + offset.x,ltIndex.y });
	ret.lb = bd.GetSquare({ ltIndex.x,ltIndex.y + offset.y });
	ret.rb = bd.GetSquare({ ltIndex.x + offset.x,ltIndex.y + offset.y });

	return ret;
}

//	�Տ�̈ړ��悪�ړ��\������
//SquareData Player::GetIsMoveForBoard(DirectX::XMFLOAT2 index)
//{
//	SquareData ret;
//	XMINT2 roundUp, roundOff;
//
//	//	�؂�̂�
//	roundUp.x = static_cast<int>(ceil(index.x));
//	roundUp.y = static_cast<int>(ceil(index.y));
//
//	//	�؂�グ
//	roundOff.x = static_cast<int>(index.x);
//	roundOff.y = static_cast<int>(index.y);
//
//	auto&bd = Board::GetInstance();
//	auto leftTop = bd.GetSquare(roundUp);
//	auto rightButtom = bd.GetSquare(roundOff);
//	auto leftButtom = bd.GetSquare({roundUp.x,roundOff.y});
//	auto rightTop = bd.GetSquare({ roundOff.x,roundUp.y });
//
//	const int canMove = 1;
//	const int notMove = 2;
//	ret.info[SquareData::LEFT] = leftTop->info[SquareData::DOWN] == canMove && leftButtom->info[SquareData::UP] == canMove ? canMove : notMove;
//	ret.info[SquareData::UP] = leftTop->info[SquareData::DOWN] == canMove && leftButtom->info[SquareData::UP] == canMove ? canMove : notMove;
//
//	return ret;
//}

DirectX::XMINT2 Player::ConvertDirection(Way way)
{
	switch (way)
	{
		case Player::LEFT	:return c_dLeft;
		case Player::RIGHT	:return c_dRight;
		case Player::UP		:return c_dUp;
		case Player::DOWN	:return c_dDown;
		default:
			break;
	}
	return DirectX::XMINT2(0, 0);
}
