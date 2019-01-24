/*
	@file	Debug.cpp
	@brief	�f�o�b�O	
	@author	�ԏ� �G�P
*/
#include "DebugDraw.h"
#include "../MyGame.h"

/*
	@brief	�R���X�g���N�^
*/
DebugDraw::DebugDraw()
{
	m_pLine = NULL;
	m_Font = NULL;
}

/*
	@brief	�f�X�g���N�^
*/
DebugDraw::~DebugDraw()
{
}

/*
	@brief	������
*/
bool DebugDraw::Init()
{
	HRESULT hr = D3DXCreateLine(DirectDevice::GetInstance().GetDevice(), &m_pLine);
	if (FAILED(hr)) {
		ErrorLog("CreateLine�Ɏ��s");
		return false;
	}
	SetLineWidth(3.0);
	SetAntialias();
	hr = D3DXCreateFont(DirectDevice::GetInstance().GetDevice(), 24, 12,
		FW_HEAVY, 1, false, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"�l�r �S�V�b�N", &m_Font);
	if(FAILED(hr)){
		ErrorLog("CreateFont�Ɏ��s");
		return false;
	}
		return true;
}

/*
	@brief	���̑�����ݒ�
*/
void DebugDraw::SetLineWidth(float Width)
{
	m_pLine->SetWidth(Width);
}

/*
	@brief	���̃A���`�G�C���A�X��ݒ�
*/
void DebugDraw::SetAntialias(bool isAntiAlias)
{
	m_pLine->SetAntialias(isAntiAlias);
}

/*
	@brief	���̕`��
*/
void DebugDraw::DrawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, COLOR color)
{
	D3DXVECTOR2 vector[] = {
		D3DXVECTOR2(start),	/*!< �n�_ */
		D3DXVECTOR2(end)	/*!< �I�_ */
	};
	m_pLine->Begin();
	m_pLine->Draw(vector, 2, ConvertColor(color));
	m_pLine->End();
}

/*
	@brief	�l�p�`�`��
*/
void DebugDraw::DrawSquare(D3DXVECTOR2 Center, float Width, float Height, COLOR color)
{
	DrawLine(D3DXVECTOR2(Center.x - Width / 2, Center.y - Height / 2), D3DXVECTOR2(Center.x + Width / 2, Center.y - Height / 2), color);	//��
	DrawLine(D3DXVECTOR2(Center.x + Width / 2, Center.y - Height / 2), D3DXVECTOR2(Center.x + Width / 2, Center.y + Height / 2), color);	//�E
	DrawLine(D3DXVECTOR2(Center.x + Width / 2, Center.y + Height / 2), D3DXVECTOR2(Center.x - Width / 2, Center.y + Height / 2), color);	//��
	DrawLine(D3DXVECTOR2(Center.x - Width / 2, Center.y + Height / 2), D3DXVECTOR2(Center.x - Width / 2, Center.y - Height / 2), color);	//��
}

void DebugDraw::DebugText(std::string str)
{
	//SIFT_JIS��Unicode�ϊ�
	
}

/* 
	@brief	�F�̕ϊ�
	@detail	������D3DCOLOR�^�ɕϊ����o��
*/
D3DCOLOR DebugDraw::ConvertColor(COLOR color)
{
	D3DCOLOR cr;
	switch (color)
	{
	case DebugDraw::WHITE:
		cr = D3DCOLOR_ARGB(255, 255, 255, 255);
		break;
	case DebugDraw::RED:
		cr = (D3DCOLOR_ARGB(255, 255, 0, 0));
		break;
	case DebugDraw::GREEN:
		cr = (D3DCOLOR_ARGB(255, 0, 255, 0));
		break;
	case DebugDraw::BLUE:
		cr = (D3DCOLOR_ARGB(255, 0, 0, 255));
		break;
	case DebugDraw::BLACK:
		cr = (D3DCOLOR_ARGB(255, 0, 0, 0));
		break;
	default:
		cr = (D3DCOLOR_ARGB(255, 255, 255, 0));
		break;
	}
	return cr;
}
