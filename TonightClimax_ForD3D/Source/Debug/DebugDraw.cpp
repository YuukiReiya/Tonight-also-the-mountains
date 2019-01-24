/*
	@file	Debug.cpp
	@brief	デバッグ	
	@author	番場 宥輝
*/
#include "DebugDraw.h"
#include "../MyGame.h"

/*
	@brief	コンストラクタ
*/
DebugDraw::DebugDraw()
{
	m_pLine = NULL;
	m_Font = NULL;
}

/*
	@brief	デストラクタ
*/
DebugDraw::~DebugDraw()
{
}

/*
	@brief	初期化
*/
bool DebugDraw::Init()
{
	HRESULT hr = D3DXCreateLine(DirectDevice::GetInstance().GetDevice(), &m_pLine);
	if (FAILED(hr)) {
		ErrorLog("CreateLineに失敗");
		return false;
	}
	SetLineWidth(3.0);
	SetAntialias();
	hr = D3DXCreateFont(DirectDevice::GetInstance().GetDevice(), 24, 12,
		FW_HEAVY, 1, false, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"ＭＳ ゴシック", &m_Font);
	if(FAILED(hr)){
		ErrorLog("CreateFontに失敗");
		return false;
	}
		return true;
}

/*
	@brief	線の太さを設定
*/
void DebugDraw::SetLineWidth(float Width)
{
	m_pLine->SetWidth(Width);
}

/*
	@brief	線のアンチエイリアスを設定
*/
void DebugDraw::SetAntialias(bool isAntiAlias)
{
	m_pLine->SetAntialias(isAntiAlias);
}

/*
	@brief	線の描画
*/
void DebugDraw::DrawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, COLOR color)
{
	D3DXVECTOR2 vector[] = {
		D3DXVECTOR2(start),	/*!< 始点 */
		D3DXVECTOR2(end)	/*!< 終点 */
	};
	m_pLine->Begin();
	m_pLine->Draw(vector, 2, ConvertColor(color));
	m_pLine->End();
}

/*
	@brief	四角形描画
*/
void DebugDraw::DrawSquare(D3DXVECTOR2 Center, float Width, float Height, COLOR color)
{
	DrawLine(D3DXVECTOR2(Center.x - Width / 2, Center.y - Height / 2), D3DXVECTOR2(Center.x + Width / 2, Center.y - Height / 2), color);	//上
	DrawLine(D3DXVECTOR2(Center.x + Width / 2, Center.y - Height / 2), D3DXVECTOR2(Center.x + Width / 2, Center.y + Height / 2), color);	//右
	DrawLine(D3DXVECTOR2(Center.x + Width / 2, Center.y + Height / 2), D3DXVECTOR2(Center.x - Width / 2, Center.y + Height / 2), color);	//下
	DrawLine(D3DXVECTOR2(Center.x - Width / 2, Center.y + Height / 2), D3DXVECTOR2(Center.x - Width / 2, Center.y - Height / 2), color);	//左
}

void DebugDraw::DebugText(std::string str)
{
	//SIFT_JIS→Unicode変換
	
}

/* 
	@brief	色の変換
	@detail	引数をD3DCOLOR型に変換し出力
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
