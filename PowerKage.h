#pragma once
#include "Engine/GameObject.h"

//�p���[�P�[�W�V�[�����Ǘ�����N���X
class PowerKage : public GameObject
{
	int hPictPowerKage_;
	int hPictPowerFlame_;

	int nowPw_, maxPw_, animPw_;
public:
	//�R���X�g���N�^
	PowerKage(GameObject* parent);

	//�f�X�g���N�^
	~PowerKage();

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
		nowPw_ = nowPw;
		maxPw_ = maxPw;
		animPw_ = (animPw_ * 9 + nowPw_) / 10;
	}
};

