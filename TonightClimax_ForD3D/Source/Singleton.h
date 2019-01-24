/*
	@file	Singleton.h
	@date	2018/11/10
	@author	�ԏ� �G�P
	@brief	�V���O���g���N���X�̊��N���X
	@detail	�e���v���[�g���g�������^�v���O���~���O
			�Q�l:https://qiita.com/narumi_/items/b205e59e7fc81695f380
*/
#pragma once

template<class T>
class Singleton {

public:

	/*! �C���X�^���X�̃Q�b�^�[ */
	static inline T& GetInstance() {
		static T instance;
		return instance;
	}

protected:

	/*! ��R���X�g���N�^ */
	Singleton() {}			/*< �O����Singleton�N���X�̃C���X�^���X�쐬���֎~���� */

	/*! ���z�f�X�g���N�^ */
	virtual ~Singleton() {}	/*< ���̃N���X���̂Ƀ����o�͎����Ă��Ȃ��̂œ��ɂ�邱�Ƃ��Ȃ�����Œ�`���Ă��� */

private:

	/*! ����I�y���[�^�[�폜 */
	void operator=(const Singleton&) = delete;

	/*! �R�s�[�R���X�g���N�^�폜 */
	Singleton(const Singleton&) = delete;
};