/*
	@file	Texture.h
	@brief	テクスチャ
	@author	番場 宥輝
*/
#pragma once
#include "../Common/Common.h"
#include  <d3dx9tex.h>
#include <string>

/*
	@brief	テクスチャの読み込みクラス
*/
class Texture {
public:
	/*! コンストラクタ */
	Texture();
	/*! デストラクタ */
	~Texture();
	/*! 画像データ読み込み */
	bool Load(std::string FilePath);
	/*! ゲッター */
	IDirect3DTexture9* GetTexture() { return m_pTexture; }
private:
	IDirect3DTexture9* m_pTexture;
};