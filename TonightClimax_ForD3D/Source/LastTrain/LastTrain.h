#pragma once
#include "../Sprite/Sprite.h"
#include "../Texture/Texture.h"
#include "../ResultState/ResultState.h"
#include <memory>
#include <DirectXMath.h>

class LastTrain
	:public IResultState
{
public:

	void Init();
	void Update();
	void Render();
	void SetPos(D3DXVECTOR2 pos) { m_Pos = pos; }
	void SetTargetPos(float horizontal) { m_Horizontal = horizontal; }
	bool GetIsMoveEnd() { return m_Pos.x == m_Horizontal; }
private:
	std::unique_ptr<Sprite> m_pSprite;
	std::unique_ptr<Texture> m_pTexture;

	D3DXVECTOR2 m_Pos;			//	�擪�ԗ��̕`��̒��S
	float m_TrainLength;		//	�d�Ԃ̒���
	float m_Scale;				//	�X�P�[��
	DirectX::XMFLOAT2 m_Size;	//	�T�C�Y
	float m_Horizontal;			//�@�ړ���x���W
	float m_Speed;				//	�ړ����x

};