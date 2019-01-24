#include "Input.h"
#include "../MyGame.h"
#include "../MemoryLeaks.h"
#include <array>
using namespace Keyboard;

Input::Input()
{
	m_pGamePad = new GamePad(GamePad::Index::One);
}


Input::~Input()
{
	SAFE_DELETE(m_pGamePad);
}


void Input::Update()
{
	Keyboard::Update();
	m_pGamePad->Update();
}

bool Input::GetKey(const KeyCode code)
{
	return GetKeyState(code) == KeyState::Stay;
}

bool Input::GetKeyDown(const KeyCode code)
{
	return GetKeyState(code) == KeyState::Down;
}

//template<typename T>
//void PushQueue(std::queue<T>&q,byte source[]) {
//
//	for (size_t i = 0; i < sizeof(source); ++i) {
//		q.push(source[i]);
//	}
//
//}

Input::KeyState Input::GetKeyState(const KeyCode code)
{

	//auto keys = { c_kLeftCode,c_kRightCode,c_kUpCode,c_kDownCode };
	size_t index = 0;

	std::array<byte, 2>ba;
	switch (code)
	{
	case Input::LEFT:
		for (auto it : c_kLeftCode) { ba[index++] = it; }
		break;
	case Input::RIGHT:
		for (auto it : c_kRightCode) { ba[index++] = it; }
		break;
	case Input::UP:
		for (auto it : c_kUpCode) { ba[index++] = it; }
		break;
	case Input::DOWN:
		for (auto it : c_kDownCode) { ba[index++] = it; }
		break;
	case Input::A:
		for (auto it : c_kACode) { ba[index++] = it;}
		break;
	case Input::B:
		for (auto it : c_kBCode) { ba[index++] = it;}
		break;
	case Input::START:
		for (auto it : c_kStartCode) { ba[index++] = it; }
		break;
	default:
		break;
	}

	bool down	= GetButtonDown(ba[0]) || GetButtonDown(ba[1]);
	bool stay	= GetButton(ba[0]) || GetButton(ba[1]);

	if (down) { return KeyState::Down; }
	if (stay) { return KeyState::Stay; }

	return KeyState::Up;
}

