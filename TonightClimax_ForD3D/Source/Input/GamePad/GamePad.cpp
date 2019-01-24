/*
	@file	Keyboard.h
	@brief	Windows�L�[�{�[�h����
	@date	2018/04/24
	@detail	�L�[�R�[�h�m�F�p�����N:http://www.azaelia.net/factory/vk.html
	@author	�ԏ� �G�P
*/
#include "GamePad.h"
#include <math.h>

/*!
	@def	�萔�錾
*/
const int GamePad::c_JoyStickInputMin		= -32768;
const int GamePad::c_JoyStickInputMax		=  32767;
const int GamePad::c_VibrationRange			= 65535;	/*!< �o�C�u���[�V�����̒l��͈̔� 0�`65535 */

/*!
	@brief	���O���
*/
using namespace KeyCode;

/*!
	@brief	�R���X�g���N�^
*/
GamePad::GamePad()
{
	SecureZeroMemory(this, sizeof(this));
	index = Index::One;
}

/*!
	@brief		�����t���R���X�g���N�^
	@param[in]	�ݒ肷��R���g���[���[�ԍ�
*/
GamePad::GamePad(Index && index)
{
	SecureZeroMemory(this, sizeof(this));
	this->index = index;
}

/*!
	@brief	�f�X�g���N�^
*/
GamePad::~GamePad()
{
	SetVibration(0);
	//XInputEnable(false);/*!< XInput�𖳌��ɂ���(�S�ẴR���g���[���[�Ɉˑ�) */
}

/*!
	@brief	���̓o�b�t�@�̍X�V
*/
void GamePad::Update()
{
	old = now;

	if (XInputGetState(index, &now) == ERROR_SUCCESS) {}
}

/*!
	@brief	�{�^���������Ă��
*/
bool GamePad::GetButton(Button button)
{
	return now.Gamepad.wButtons&ConvertKeyButtonCode(Button(button));
}

/*!
	@brief	�\���L�[�������Ă��
*/
int GamePad::GetArrow(KeyCode::Arrow arrow)
{
	auto input = ConvertKeyArrowCode(Arrow(arrow));

	/*! ���̒l */
	if ((now.Gamepad.wButtons&input.x)==1) {
		return 1;
	}
	/*! ���̒l */
	if ((now.Gamepad.wButtons&input.y)==1) {
		return -1;
	}

	return 0;
}

/*!
	@brief	�{�^�����������u��
*/
bool GamePad::GetButtonDown(KeyCode::Button button)
{
	return ((now.Gamepad.wButtons&ConvertKeyButtonCode(Button(button))) 
		^
		(old.Gamepad.wButtons&ConvertKeyButtonCode(Button(button))))
		&
		(now.Gamepad.wButtons&ConvertKeyButtonCode(Button(button)));
}

/*!
	@brief	�\���L�[���������u��
*/
int GamePad::GetArrowDown(KeyCode::Arrow arrow)
{
	auto input = ConvertKeyArrowCode(Arrow(arrow));

	/*! ���̒l */
	if ((now.Gamepad.wButtons&input.x)
		^
		(old.Gamepad.wButtons&input.x)
		&
		(now.Gamepad.wButtons&input.x)
		) {
		return 1;
	}

	/*! ���̒l */
	if ((now.Gamepad.wButtons&input.y)
		^
		(old.Gamepad.wButtons&input.y)
		&
		(now.Gamepad.wButtons&input.y)
		) {
		return -1;
	}

	return 0;
}

/*!
	@brief	�{�^���������ꂽ�u��
*/
bool GamePad::GetButtonUp(KeyCode::Button button)
{
	return ((now.Gamepad.wButtons&ConvertKeyButtonCode(Button(button)))
		^
		(old.Gamepad.wButtons&ConvertKeyButtonCode(Button(button))))
		&
		(old.Gamepad.wButtons&ConvertKeyButtonCode(Button(button)));
}

/*!
	@brief	�\���L�[�������ꂽ�u��
*/
int GamePad::GetArrowUp(KeyCode::Arrow arrow)
{
	auto input = ConvertKeyArrowCode(Arrow(arrow));

	/*! ���̒l */
	if ((now.Gamepad.wButtons&input.x)
		^
		(old.Gamepad.wButtons&input.x)
		&
		(old.Gamepad.wButtons&input.x)
		) {
		return 1;
	}

	/*! ���̒l */
	if ((now.Gamepad.wButtons&input.y)
		^
		(old.Gamepad.wButtons&input.y)
		&
		(old.Gamepad.wButtons&input.y)
		) {
		return -1;
	}

	return 0;
}

/*!
	@brief	�W���C�X�e�B�b�N�̓��͎擾
	@detail	x:�����Ay:�c���Az:��������(0��1)
*/
DirectX::XMFLOAT3 GamePad::GetJoyStick(KeyCode::JoyStick joyStick)
{
	DirectX::XMFLOAT3 input = { 0,0,0 };

	switch (joyStick)
	{
	case KeyCode::JoyStick::LEFT:
		input.x = now.Gamepad.sThumbLX;
		input.y = now.Gamepad.sThumbLY;
		/*! ���X�e�B�b�N�̉������� */
		input.z = now.Gamepad.wButtons & 0x0040 ? 1.0f : 0.0f;
		break;
	case KeyCode::JoyStick::RIGHT:
		input.x = now.Gamepad.sThumbRX;
		input.y = now.Gamepad.sThumbRY;
		/*! �E�X�e�B�b�N�̉������� */
		input.z = now.Gamepad.wButtons & 0x0080 ? 1.0f : 0.0f;
		break;
	default:
		input = DirectX::XMFLOAT3(0, 0, 0);
		break;
	}

	/*! �l�̐��K��(-1�`1) */
	input.x = InputNormalize(input.x);
	input.y = InputNormalize(input.y);

	/*! �l���ۂ߂� */
	input.x = InputRound(input.x);
	input.y = InputRound(input.y);

	return input;
}

/*!
	@brief	�g���K�[�̓��͎擾
*/
BYTE GamePad::GetTrigger(KeyCode::Trigger trigger)
{
	BYTE input = 0;
	
	switch (trigger)
	{
	case KeyCode::LT:
		input = now.Gamepad.bLeftTrigger;
		break;
	case KeyCode::RT:
		input = now.Gamepad.bRightTrigger;
		break;
	default:
		break;
	}

	return input;
}

/*!
	@brief	�g���K�[�̓��͂�bool�Ŕ���
*/
bool GamePad::GetBTrigger(KeyCode::Trigger trigger)
{
	return GetTrigger(trigger) > 0;
}

/*!
	@brief	�o�C�u���[�V�����̐ݒ�
*/
void GamePad::SetVibration(int leftPower, int rightPower)
{
	/*! ���E�ŏo�͂������Ȃ� */
	if (rightPower == -1) {
		rightPower = leftPower;
	}
	XINPUT_VIBRATION vibration;
	SecureZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = VibrationConvertPower(leftPower);
	vibration.wRightMotorSpeed = VibrationConvertPower(rightPower);
	XInputSetState(index, &vibration);
}

/*!
	@brief	���͒l�̐��K��
	@detail	-1�`1�͈̔͂ɒl�𐳋K�������l��Ԃ�
*/
float GamePad::InputNormalize(float input)
{
	input = (input - c_JoyStickInputMin) / (c_JoyStickInputMax - c_JoyStickInputMin)*(1 - (-1)) + (-1);
	return input;
}

/*!
	@brief	���͒l���ۂ߂�
	@detail	�ݒ肵�����x�Ő��l���ۂ߂�
*/
float GamePad::InputRound(float input)
{
	int tmp = static_cast<int>(input) * c_JoyStickInputPrecision;
	input = static_cast<float>(tmp) / static_cast<float>(c_JoyStickInputPrecision);

	/*! �ݒ肵�����͒l�ȉ��Ȃ� ���͒l��0�ɂ��� */
	if (fabs(input) < c_JoyStickInputDead) {
		input = 0.0f;
	}

	return input;
}

/*!
	@brief	���K�������l���o�C�u���[�V�����l�ɕϊ�
	@detail	0�`100�͈̔͂��󂯎��
*/
int GamePad::VibrationConvertPower(int vibration)
{
	/*! �͈͊O�␳ */
	{
		if (vibration < 0) { vibration = 0; }
		else if (100 < vibration) { vibration = 100; }
	}
	vibration *= c_VibrationRange / 100;
	return vibration;
}

/*!
	@brief	�{�^���̃L�[�R�[�h�ϊ�
	@detail	�{�^���̗񋓑̂���XInput�̔���p16�i���֕ϊ�
*/
int GamePad::ConvertKeyButtonCode(Button button)
{
	switch (button)
	{
	case Button::A:			return 0x1000;	/*!< A�{�^�� �}�N���y XINPUT_GAMEPAD_A�z */
	case Button::B:			return 0x2000;	/*!< B�{�^�� �}�N���y XINPUT_GAMEPAD_B�z */
	case Button::X:			return 0x4000;	/*!< X�{�^�� �}�N���y XINPUT_GAMEPAD_X�z */
	case Button::Y:			return 0x8000;	/*!< Y�{�^�� �}�N���y XINPUT_GAMEPAD_Y�z */
	case Button::START:		return 0x0010;	/*!< START�{�^�� �}�N���y XINPUT_GAMEPAD_START�z */
	case Button::BACK:		return 0x0020;	/*!< BACK�{�^�� �}�N���y XINPUT_GAMEPAD_BACK�z */
	case Button::LB:		return 0x0100;	/*!< LB�{�^�� �}�N���y XINPUT_GAMEPAD_LEFT_SHOULDER�z */
	case Button::RB:		return 0x0200;	/*!< RB�{�^�� �}�N���y XINPUT_GAMEPAD_RIGHT_SHOULDER�z */
	case Button::L_STICK:	return 0x0040;	/*!< ���X�e�B�b�N�̉������� �}�N���y XINPUT_GAMEPAD_LEFT_THUMB�z */
	case Button::R_STICK:	return 0x0080;	/*!< �E�X�e�B�b�N�̉������� �}�N���y XINPUT_GAMEPAD_RIGHT_THUMB�z */
	default:
		break;
	}
	return 0;
}

/*!
	@brief	�\���L�[�̃L�[�R�[�h�ϊ�
	@detail	�\���L�[�̗񋓑̂���XInput�̔���p16�i���֕ϊ�
*/
DirectX::XMINT2 GamePad::ConvertKeyArrowCode(KeyCode::Arrow arrow)
{
	DirectX::XMINT2 code = { 0,0 };

	switch (arrow)
	{
	case KeyCode::VERTICAL:
		code.x = 0x0001;	/*!< �\���L�[�̏� */
		code.y = 0x0002;	/*!< �\���L�[�̉� */
		break;
	case KeyCode::HORIZONTAL:
		code.x = 0x0008;	/*!< �\���L�[�̉E */
		code.y = 0x0004;	/*!< �\���L�[�̍� */
		break;
	default:
		break;
	}
	return code;
}
