#include "LastTrain.h"

using namespace std;

void LastTrain::Init()
{
	m_pSprite	= make_unique<Sprite>();
	m_pTexture	= make_unique<Texture>();

	m_pTexture->Load("../Resource/Image/train.png");
	
	m_Pos = {960,500};
	m_Scale = 2;
	m_Size = { 852,196 };
	m_TrainLength = m_Size.x * m_Scale;
	m_Speed = 30;
	m_Horizontal = m_Pos.x;
	m_pSprite->SetPos(m_Pos);
	m_pSprite->SetSpriteSize(m_Size.x, m_Size.y);
	m_pSprite->SetSizeScaling(m_Scale);

}

void LastTrain::Update()
{
	//	�ڕW���W
	if (GetIsMoveEnd()) { return; }
	
	//	�ړ�����
	int sign = (m_Horizontal - m_Pos.x) >= 0 ? 1 : -1;

	//	�ړ�
	m_Pos.x += m_Speed * sign;

	////////////
	//	�␳�@//
	////////////

	//	�E
	if (sign > 0) {

		if (m_Pos.x > m_Horizontal) {
			m_Pos.x = m_Horizontal;
		}

	}
	//	��
	else{

		if (m_Pos.x < m_Horizontal) {
			m_Pos.x = m_Horizontal;
		}
	}
}

void LastTrain::Render()
{
	int num = 2;
	for (int i = 0; i < num; i++) {

		auto pos = m_Pos - D3DXVECTOR2{ m_TrainLength*i, 0 };
		m_pSprite->SetPos(pos);
		m_pSprite->Render(
			m_pTexture->GetTexture()
		);
	}
}
