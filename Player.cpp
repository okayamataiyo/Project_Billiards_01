#include "Player.h"
#include "PowerKage.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

/*
* �p���[�P�[�W���쐬���āA�ړ��{�^������������A�J�[�r�B�̂�����胁�K�g���p���`�̂悤�Ȏg�p�ɂ���
*/

Player::Player(GameObject* parent)
	:maxPw_(180),nowPw_(2)
{
	direction = 0.0f;
	power = 0.1f;
	hModel = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(0.2, 0.2, 0.2);
}

Player::~Player()
{

}

void Player::Update()
{
	//PowerKage�̗͂̑���
	if (PowerKageFlug == 1) {
		nowPw_++;

	}
	if (nowPw_ == maxPw_) {
		PowerKageFlug = 2;

	}
	if (PowerKageFlug == 2) {
		nowPw_--;
	}
	if (nowPw_ <= maxPw_ - maxPw_ + 1) {
		PowerKageFlug = 1;
	}

	//�ړ�������nowPw_�̕␳��������
	if (nowPw_ <= maxPw_ - 20) {
		PowerComPenSate = nowPw_ * 0.01;
	}
	if (nowPw_ >= maxPw_ - 20) {
		PowerComPenSate = nowPw_ * 0.05;
	}

	if (Input::IsKey(DIK_A))
		direction -= 0.02;
	if (Input::IsKey(DIK_D))
		direction += 0.02;
	if (PowerKageFlug == 0){
		if (Input::IsKeyDown(DIK_SPACE)){

			PowerKageFlug = 1;
		}
	}
	else if (PowerKageFlug == 1 || PowerKageFlug == 2) {
		if (Input::IsKeyDown(DIK_SPACE)){
			//�����ŋʂ�ł�
			XMVECTOR base = XMVectorSet(0, 0, power * PowerComPenSate, 0);	//��]���ĂȂ����Ɉړ�����x�N�g��
			XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
			XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
			myBall->AddForce(v);	//���ꂪ��]��̈ړ��x�N�g��

			nowPw_ = 0;
		}
	}
	
	//PowerKageFlug�������ɕς��A�Ĕ������Ȃ����߂̏���
	if (nowPw_ == 0.0f) {
		PowerKageFlug = 0;
	}
	if (PowerKageFlug == 0) {
		nowPw_ = 2;
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

	PowerKage* pPowerKage = (PowerKage*)FindObject("PowerKage");
	pPowerKage->SetPw(nowPw_, maxPw_);
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
