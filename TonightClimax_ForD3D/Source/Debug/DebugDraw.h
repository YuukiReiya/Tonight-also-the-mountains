/*
	@file	Debug.h
	@brief	デバッグ
	@author	番場 宥輝
*/
#pragma once
#include "../Common/Common.h"
#include "../Singleton.h"
/*
	@brief	デバッグクラス
*/
class DebugDraw
	:public Singleton<DebugDraw>
{
public:
	/*! デストラクタ */
	~DebugDraw();

	/*
		@enum	COLOR
		@brief	色
	*/
	enum COLOR {
		WHITE,
		RED,
		GREEN,
		BLUE,
		BLACK
	};

	bool Init();
	void SetLineWidth(float Width);
	void SetAntialias(bool isAntiAlias = true);
	void DrawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, COLOR color = WHITE);
	void DrawSquare(D3DXVECTOR2 Center,float Width,float Height,COLOR color = WHITE);
	void DebugText(std::string str);
private:
	/*! コンストラクタ */
	DebugDraw();
	friend class Singleton<DebugDraw>;

	ID3DXLine*	m_pLine;
	LPD3DXFONT  m_Font;
	D3DCOLOR ConvertColor(COLOR color);
};

