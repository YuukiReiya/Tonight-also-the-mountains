/*
	@file	GamePad.h
	@brief	�Q�[���p�b�h����
	@date	2018/04/24
	@detail	XInput��p��������
			XInput�Q�l:		http://www.geocities.jp/gameprogrammingunit/xinput/index.html
			�񋓑̂̒���:	http://d.hatena.ne.jp/mclh46/20100627/1277603928
	@author	�ԏ� �G�P
*/#pragma once
#include <windows.h>
#include <Xinput.h>
#include <DirectXMath.h>

#pragma comment(lib, "XInput.lib")

/*!
	@brief	���O���
*/
namespace KeyCode {
	/*! �񋓑̃L�[�R�[�h */

	/*!
		@enum	Button
		@brief	�{�^���̃L�[�R�[�h�񋓑�
	*/
	enum Button		{ A, B, X, Y, START, BACK, LB, RB, L_STICK, R_STICK, };	/*!< �{�^�� */

	/*!
		@enum	Trigger
		@brief	�g���K�[�̃L�[�R�[�h�񋓑�
	*/
	enum Trigger	{ LT, RT };												/*!< �g���K�[ */

	/*!
		@enum	JoyStick
		@brief	�W���C�X�e�B�b�N�̎�ޗ񋓑�
	*/
	enum JoyStick	{ LEFT, RIGHT };										/*!< �W���C�X�e�B�b�N */

	/*!
		@enum	Arrow
		@brief	�����L�[�̃L�[�R�[�h�񋓑�
	*/
	enum Arrow		{ VERTICAL, HORIZONTAL };								/*!< V:�c H:�� */
}

/*!
	@brief	�Q�[���p�b�h�N���X
	@detail	XBOX�R���g���[���[�̓��͐���N���X
*/
class GamePad {
public:
	/*! �R���g���[���[�ԍ� */
	enum Index { One, Two, Three, Four, };

	/*!
		@brief	�R���X�g���N�^
	*/
	explicit GamePad();

	/*!
		@brief	�����t���R���X�g���N�^
	*/
	explicit GamePad(Index&& index);

	/*!
		@brief	�f�X�g���N�^
	*/
	~GamePad();


	/*!
		@fn		Update
		@brief	�X�V����
		@detail	���̓o�b�t�@�̍X�V
	*/
	void Update();

	/*!
		@fn			GetButton
		@brief		�{�^���������Ă�Ԃ̎擾
		@param[in]	���肷��{�^���̃L�[�R�[�h
		@return		�{�^���̉������
	*/
	bool GetButton(KeyCode::Button button);

	/*!
		@fn			GetButtonDown
		@brief		�{�^�����������u�Ԃ̎擾
		@param[in]	���肷��{�^���̃L�[�R�[�h
		@return		�{�^���̉������
	*/
	bool GetButtonDown(KeyCode::Button button);

	/*!
		@fn			GetButtonUp
		@brief		�{�^���������ꂽ�u�Ԃ̎擾
		@param[in]	���肷��{�^���̃L�[�R�[�h
		@return		�{�^���̉������
	*/
	bool GetButtonUp(KeyCode::Button button);

	/*!
		@fn			GetArrow
		@brief		�\���L�[�������Ă���Ԃ̎擾
		@param[in]	�������
		@return		1: -1: 0:������Ă��Ȃ�
	*/
	int GetArrow(KeyCode::Arrow arrow);

	/*!
		@fn			GetArrow
		@brief		�\���L�[���������u�Ԃ̎擾
		@param[in]	�������
		@return		1: -1: 0:������Ă��Ȃ�
	*/
	int GetArrowDown(KeyCode::Arrow arrow);

	/*!
		@fn			GetArrowUp
		@brief		�\���L�[�𗣂����u�Ԃ̎擾
		@param[in]	�������
		@return		1: -1: 0:������Ă��Ȃ�
	*/
	int GetArrowUp(KeyCode::Arrow arrow);

	/*!
		@fn			GetJoyStick
		@brief		�W���C�X�e�B�b�N�̓��͎擾
		@param[in]	�W���C�X�e�B�b�N�̎��
		@return		x:�����Ay:�c���Az:��������(0��1)
	*/
	DirectX::XMFLOAT3 GetJoyStick(KeyCode::JoyStick joyStick);

	/*!
		@fn			GetTrigger
		@brief		�g���K�[�̓��͎擾
		@param[in]	���肷��g���K�[
		@return		0�`255�͈̔͂̋�����Ԃ�
	*/
	BYTE GetTrigger(KeyCode::Trigger trigger);

	/*!
		@fn			GetBTrigger
		@brief		�g���K�[�̓��͎擾
		@param[in]	���肷��g���K�[
		@return		������Ă���/���Ȃ��̂ǂ��炩��Ԃ�
	*/
	bool GetBTrigger(KeyCode::Trigger trigger);

	/*!
		@fn			SetVibration
		@brief		�o�C�u���[�V�����̐ݒ�
		@detail		�f�t�H���g������rightPower = -1���w�肷�邱�Ƃō��E�̏o�͂𓯂��ɂ���
		@param[in]	�����̃��[�^�[�̋���
		@param[in]	�E���̃��[�^�[�̋���
	*/
	void SetVibration(int leftPower, int rightPower = -1);
private:

	/*!
		@fn			InputNormalize
		@brief		���͒l�̐��K��
		@param[in]	���K������l
		@return		-1�`1�͈̔͂ɒl�𐳋K�������l��Ԃ�
	*/
	float InputNormalize(float input);

	/*!
		@fn			InputRound
		@brief		���͒l���ۂ߂�
		@detail		�ݒ肵�����x�Ő��l���ۂ߂�
		@param[in]	���͒l
		@return		�ۂ߂��l
	*/
	float InputRound(float input);

	/*!
		@fn			VibrationConvertPower
		@brief		���K�������l���o�C�u���[�V�����l�ɕϊ�
		@detail		0�`100�͈̔͂ɐ��K�������l���o�C�u���[�V�����Ŏg���l�ɕϊ�
		@param[in]	���K�������l(0�`100)
		@return		�o�C�u���[�V�����̒l�ɕϊ������l
	*/
	int VibrationConvertPower(int vibration);

	/*!
		@fn			ConvertKeyButtonCode
		@brief		�{�^���̃L�[�R�[�h�ϊ�
		@detail		�{�^���̗񋓑̂���XInput�̔���p16�i���֕ϊ�
		@param[in]	�ϊ�����{�^��
		@return		�ϊ���̃L�[�R�[�h
	*/
	int ConvertKeyButtonCode(KeyCode::Button button);

	/*!
		@fn			ConvertKeyArrowCode
		@brief		�\���L�[�̃L�[�R�[�h�ϊ�
		@detail		�\���L�[�̗񋓑̂���XInput�̔���p16�i���֕ϊ�
		@param[in]	�ϊ�����\���L�[
		@return		�ϊ���̏�񂪓�����XMINT2�^
	*/
	DirectX::XMINT2 ConvertKeyArrowCode(KeyCode::Arrow arrow);

	/*!
		@var	c_JoyStickInputMin
		@brief	�W���C�X�e�B�b�N���͂̍ŏ��l
	*/
	static const int c_JoyStickInputMin;

	/*!
		@var	c_JoyStickInputMax
		@brief	�W���C�X�e�B�b�N���͂̍ő�l
	*/
	static const int c_JoyStickInputMax;

	/*!
		@var	c_VibrationRange
		@brief	�o�C�u���[�V�����̒l��͈̔�
	*/
	static const int c_VibrationRange;

	/*!
		@var	c_JoyStickInputPrecision
		@brief	�W���C�X�e�B�b�N�̓��͐��x
		@detail	���x ex)10:�������ʁA100:��������
	*/
	static constexpr int c_JoyStickInputPrecision = 10;

	/*!
		@var	c_JoyStickInputDead
		@brief	�W���C�X�e�B�b�N�̓��͐���
		@detail	���̒l�ȉ��̒l�� 0.0f �Ƃ��Ĉ����� ���W���C�X�e�B�b�N�̂ݑΉ�
	*/
	static constexpr float c_JoyStickInputDead = 0.0f;

	/*! �p�����[�^�[ */
	Index index;			/*!< �R���g���[���[�ԍ� */
	XINPUT_STATE now,old;	/*!< ���̓o�b�t�@ */

};