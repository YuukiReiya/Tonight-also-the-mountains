/*
	@file	Camera2D.h
	@brief	カメラ
	@author	番場 宥輝
*/
#pragma once
#include "../Common/Common.h"

/*
	@def	カメラ座標への変換マクロ
*/
#define ConvertView(Pos) Pos-Camera2D::GetInstance().GetPos()

/*
	@brief	カメラの管理クラス
*/
class Camera2D
{
public:
	/*! デストラクタ */
	~Camera2D();

	/*! シングルトン */
	static Camera2D& GetInstance() {
		static Camera2D instance;
		return instance;
	}

	/*! セッター */
	void SetPos(D3DXVECTOR2 pos) { m_CharaPos = pos; }
	void SetPos(int x, int y) { m_CharaPos.x = (float)x, m_CharaPos.y = (float)y; }
	void SetZoom(float zoom) { m_Zoom = zoom; }
	/*! ゲッター */
	const D3DXVECTOR2 GetPos()const { return m_CharaPos; }
	const float GetZoom()const { return m_Zoom; }
private:
	/*! コンストラクタ */
	Camera2D();

	D3DXVECTOR2 m_CharaPos;			/*!< 位置 */
	float m_Zoom;				/*!< ズーム*/
};

