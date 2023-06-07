#include "Engine/GameObject.h"
#pragma once
class Ball : public GameObject
{

public:
	//�R���X�g���N�^
//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Ball(GameObject* parent);

	~Ball();

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�{�[���ԍ�(1~9)���w��,���ʂ�0
	void SetNumber(int no);

	//�{�[���ɗ͂�������
	void AddForce(XMVECTOR f);
private:
	int hModel;

	//�{�[���̔ԍ�
	int number;

	//�ړ����x
	XMVECTOR velocity;


};

