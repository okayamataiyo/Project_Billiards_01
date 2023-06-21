#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

/*
* �p���[�P�[�W���쐬���āA�ړ��{�^������������A�J�[�r�B�̂�����胁�K�g���p���`�̂悤�Ȏg�p�ɂ���
*/

Player::Player(GameObject* parent)
{
	direction = 0.0f;
	power = 0.3f;
	hModel = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(0.2, 0.2, 0.2);
}

Player::~Player()
{

}

void Player::Update()
{
	if (Input::IsKey(DIK_A))
		direction -= 0.02;
	if (Input::IsKey(DIK_D))
		direction += 0.02;
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//�����ŋʂ�ł�
		XMVECTOR base = XMVectorSet(0, 0, power, 0);	//��]���ĂȂ����Ɉړ�����x�N�g��
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
		XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
		myBall->AddForce(v);	//���ꂪ��]��̈ړ��x�N�g��
	}
	if (Input::IsKeyDown(DIK_S))
	{
		//�����ŋʂ�ł�
		XMVECTOR base = XMVectorSet(0, 0, power, 0);	//��]���ĂȂ����Ɉړ�����x�N�g��
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
		XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
		myBall->AddForce(-v);
	}
	if (Input::IsKeyDown(DIK_LEFT))
	{
		//�����ŋʂ�ł�
		XMVECTOR base = XMVectorSet(-power, 0, 0, 0);	//��]���ĂȂ����Ɉړ�����x�N�g��
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
		XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
		myBall->AddForce(v);
	}
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		//�����ŋʂ�ł�
		XMVECTOR base = XMVectorSet(power, 0, 0, 0);	//��]���ĂȂ����Ɉړ�����x�N�g��
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
		XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
		myBall->AddForce(v);
	}
}

void Player::Draw()
{
	//transform_.position_��ݒ�
	//�����ʂ����_�ɂ���Ƃ��āA�����ʂ̂ǂ��ɕ\�����邩
	//�����ɁA�����ʂ̍��W�𑫂��΁A
	//�\�����W�����܂�̂ŁAtransform_.position_�ɑ������
	
	XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
	XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
	transform_.position_ = myBall->GetPosition() + v;

//	hModel = Model::Load("no0.fbx");
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}
