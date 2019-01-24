#pragma once
#include "GamePad/GamePad.h"
#include "../Singleton.h"
#include "Keyboard/Keyboard.h"


class Input
	:public Singleton<Input>
{
public:
	~Input();

	enum KeyCode {

		LEFT,
		RIGHT,
		UP,
		DOWN,
		A,
		B,
		START
	};

	void Update();
	bool GetKey(const KeyCode code);
	bool GetKeyDown(const KeyCode code);
private:
	friend class Singleton<Input>;
	Input();

	enum KeyState {
		Down,
		Stay,
		Up
	};
	KeyState GetKeyState(const KeyCode code);

	/*!
		@var	c_kLeftCode
		@brief	Keyboardの左キーコード
	*/
	const byte c_kLeftCode[2] = { 'A' ,Keyboard::LEFT };

	/*!
		@var	c_kRightCode
		@brief	Keyboardの右キーコード
	*/
	const byte c_kRightCode[2] = { 'D' ,Keyboard::RIGHT };

	/*!
		@var	c_kUpCode
		@brief	Keyboardの上キーコード
	*/
	const byte c_kUpCode[2] = { 'W' ,Keyboard::UP };

	/*!
		@var	c_kDowmCode
		@brief	Keyboardの下キーコード
	*/
	const byte c_kDownCode[2] = { 'S' ,Keyboard::DOWN };

	/*!
		@var	c_kACode
		@brief	GamePad上のAのKeyboardとしてのキーコード
	*/
	const byte c_kACode[2] = { 'X' ,Keyboard::SPACE };

	/*!
		@var	c_kBCode
		@brief	GamePad上のBのKeyboardとしてのキーコード
	*/
	const byte c_kBCode[2] = { 'Z' ,Keyboard::SPACE };

	/*!
		@var	c_kStartCode
		@brief	GamePad上のStartのKeyboardとしてのキーコード
	*/
	const byte c_kStartCode[2] = { 'Z' ,Keyboard::BACK };

	GamePad* m_pGamePad;
};

