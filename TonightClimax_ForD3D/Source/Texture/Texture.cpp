/*
	@file	Texture.cpp
	@brief	�e�N�X�`��
	@author	�ԏ� �G�P
*/
#include "Texture.h"
#include "../MyGame.h"

/*
	@brief	�R���X�g���N�^
*/
Texture::Texture() {
	m_pTexture = NULL;
}

/*
	@brief	�f�X�g���N�^	
*/
Texture::~Texture()
{
	/*! �ǂݍ��܂�Ă�����j�� */
	if (m_pTexture != NULL)
		m_pTexture->Release();
}

/*
	@brief	�摜�t�@�C���̓ǂݍ���
*/
bool Texture::Load(std::string FileName)
{
	auto cast = To_WString(FileName);
	auto path = const_cast<LPCWSTR>(cast.c_str());


	/*! �摜�ǂݍ��� */
	if (FAILED(D3DXCreateTextureFromFile(DirectDevice::GetInstance().GetDevice(), path, &m_pTexture)))
		/*! �摜�ǂݍ��ݎ��s�i�t�@�C�����Ȃ��\������j */
		return false;

	/*! �摜�ǂݍ��ݐ��� */
	return true;
}
