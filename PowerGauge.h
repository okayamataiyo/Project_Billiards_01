#pragma once
#include "Engine/GameObject.h"

//�p���[�P�[�W�V�[�����Ǘ�����N���X
//�Q�[�W�N���X�́A�Q�[�W�̍ő��100%(�܂�1.0)�ƂȂ�悤�ɍ��B
//�\���̑傫���ɂ���āA�\���T�C�Y��ς����悤�ɍ��B
//�\������ʒu�́A�O����(�g����)����w��o����悤�ɂ���B
//���Z����֐��ƁA���Y����֐��ƁA���݂̒l���擾����֐���p�ӂ���B



class PowerGauge : public GameObject
{
	int hPictPowerGauge_;	//�摜�ԍ�(�Q�[�W�̒��g)
	int hPictPowerFrame_;	//�摜�ԍ�(�Q�[�W�̊O�g)
	float nowPw_;		//���̒l
	const float maxPw_ = 1.0f;	//�ő�l
	float animPw_;		//dispHp	�\���p�̒l
	int ImageWidth;		//�Q�[�W�摜�̕�
	int ImageHeight;	//�Q�[�W�摜�̍���


public:
	static constexpr float MIN = 0.0f;
	static constexpr float MAX = 1.0f;

	//�R���X�g���N�^
	PowerGauge(GameObject* parent);

	//�f�X�g���N�^
	~PowerGauge();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPw(int nowPw, int maxPw)
	{
//		nowPw_ = nowPw;
//		maxPw_ = maxPw;
//		animPw_ = (animPw_ * 9 + nowPw_) / 10;
	}

	void SetPosition(float x, float y);

	/// <summary>
	/// �l�������Z����
	/// </summary>
	/// <param name="v"></param>
	void AddValue(float v);

	void SetValue(float v);

	float GetValue();
};

