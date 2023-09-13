#pragma once
#include "Engine/GameObject.h"

namespace {
	const int PictNum_ = { 2 };
}

//�^�C�g���V�[�����Ǘ�����N���X
class Title : public GameObject
{
	int hPict_[PictNum_];	//�摜�ԍ�
public:
	//�R���X�g���N�^
	Title(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;
};

