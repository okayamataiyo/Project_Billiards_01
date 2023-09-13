#pragma once
#include "Engine/GameObject.h"

class Button;

//�^�C�g���V�[�����Ǘ�����N���X
class Title : public GameObject
{
	Button* start;
	Button* back;
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};
	SELECT selected;
	//int hPict_[PictNum_];	//�摜�ԍ�
	int PushFlag_;			//�摜�����������ɐ؂�ւ��t���O
	Transform giveTrans;
	Transform backTrans;
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

	void SetPosition(int x, int y);
};

