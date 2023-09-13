#pragma once
#include "Engine/GameObject.h"

//�{�^�����Ǘ�����N���X
class Button : public GameObject
{
	
public:
	//�R���X�g���N�^
	Button(GameObject* parent);
	~Button();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;

	void SetImage(std::string normal, std::string pushed);

	void SetPosition(int x, int y);		//�{�^���\���ʒu

	void Push(bool pushed);				//�{�^�������������A�����ĂȂ���
	
	bool MouseInArea(XMFLOAT3 mousePos);//�}�E�X���{�^�����ɓ����Ă��邩

	/// <summary>
	/// �{�^�����ړ�������
	/// </summary>
	/// <param name="toX">�ړ���̍��WX</param>
	/// <param name="toY">�ړ���̍��WY</param>
	/// <param name="seconds">�ړ�����(�b)</param>
	void SetMovePosition(int toX, int toY, float seconds);

	/// <summary>
	/// �����Ă���Ȃ�true
	/// </summary>
	/// <returns></returns>
	bool IsMoving();

	/// <summary>
	/// �����I�Ɉړ����I��������
	/// </summary>
	void ForceMoveEnd();

private:
	int hImage;		//�ʏ�摜�ԍ�
	int pushed;		//�����ꂽ�摜
	int hPush;		//������Ă��邩
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};

	//���������
	XMFLOAT3 startPos;
	XMFLOAT3 endPos;
	XMFLOAT3 center;	//�{�^���̒��S���W(��ʍ��W)
	XMFLOAT3 size;		//�{�^���̉摜�T�C�Y
	float totalTime;
	float currentTime;
};

