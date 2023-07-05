#include "Player.h"
#include "PowerGauge.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

/*
* 
* �p���[�P�[�W���쐬���āA�X�y�[�X�{�^������������A�J�[�r�B�̂�����胁�K�g���p���`�̃P�[�W�̂悤�ȑ���ɂ���
*/

namespace {
	static const float ROT_SPEED = 90.0f;	//1�b�Ԃňړ�����p�x(�x)
	const float GAUGE_TIME = 0.5f;	//0���疞�^���ɂȂ邽�߂̎���
}

Player::Player(GameObject* parent)
//	:maxPw_(180),nowPw_(2)
{
	direction = 0.0f;
	power = 0.1f;
	hModel = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(2.0,0.1,0.1);
	transform_.rotate_.y = 90.0f;
}

Player::~Player()
{

}

void Player::Update()
{
	PowerGauge* pGauge = (PowerGauge*)FindObject("LifeGauge");


	//PowerGauge�̗͂̑���
	if (PowerGaugeFlag == 1) {
		pGauge->AddValue(PowerGauge::MAX/GAUGE_TIME/60.0f);
		if (pGauge->GetValue() >= PowerGauge::MIN) {
			PowerGaugeFlag = 2;
		}
	}
	/*if (nowPw_ == maxPw_) {
		PowerGaugeFlag = 2;

	}*/
	if (PowerGaugeFlag == 2) {
		pGauge->AddValue(PowerGauge::MAX/GAUGE_TIME / 60.0f);
		if (pGauge->GetValue() <= PowerGauge::MAX) {
			PowerGaugeFlag = 1;
		}
	}
	/*if (nowPw_ <= maxPw_ - maxPw_ + 1) {
		PowerGaugeFlag = 1;
	}*/

	//�ړ�������nowPw_�̕␳��������
	/*if (nowPw_ <= maxPw_ - 20) {
		PowerComPenSate = nowPw_ * 0.01;
	}
	if (nowPw_ >= maxPw_ - 20) {
		PowerComPenSate = nowPw_ * 0.05;
	}*/

	if (Input::IsKey(DIK_A))
		direction -= XMConvertToRadians(ROT_SPEED) / 60.0f;
	if (Input::IsKey(DIK_D))
		direction += XMConvertToRadians(ROT_SPEED) / 60.0f;
	if (PowerGaugeFlag == 0){
		if (Input::IsKeyDown(DIK_SPACE)){

			PowerGaugeFlag = 1;
		}
	}
	else if (PowerGaugeFlag == 1 || PowerGaugeFlag == 2) {
		if (Input::IsKeyDown(DIK_SPACE)){
			//�����ŋʂ�ł�
			XMVECTOR base = XMVectorSet(0, 0, power * PowerComPenSate, 0);	//��]���ĂȂ����Ɉړ�����x�N�g��
			XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//��]�s��������
			XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
			myBall->AddForce(v);	//���ꂪ��]��̈ړ��x�N�g��
		}
	}
	
	//PowerGaugeFlag�������ɕς��A�Ĕ������Ȃ����߂̏���
	/*if (nowPw_ == 0.0f) {
		PowerGaugeFlag = 0;
	}
	if (PowerGaugeFlag == 0) {
		nowPw_ = 2;
	}*/

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

//	PowerGauge* pPowerGauge = (PowerGauge*)FindObject("PowerGauge");
//	pPowerGauge->SetPw(nowPw_, maxPw_);

	std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
	bool flag = true;

	//	for (auto itr = all.begin(); itr != all.end(); itr++) {
	for (Ball* b : all)
		//		if (!(*itr)->IsStopped()) {
		flag = false;
	return;	//break;
}

void Player::Draw()
{
	//transform_.position_��ݒ�
	//�����ʂ����_�ɂ���Ƃ��āA�����ʂ̂ǂ��ɕ\�����邩
	//�����ɁA�����ʂ̍��W�𑫂��΁A
	//�\�����W�����܂�̂ŁAtransform_.position_�ɑ������

	XMVECTOR base = XMVectorSet(0, 0, 1.2, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//Y����]�s��������
	XMVECTOR v = XMVector3Transform(base, yrot);	//���̉�]�Ńx�N�g���̌�����ς���
	transform_.position_ = myBall->GetPosition() + v;
	transform_.rotate_.y = (direction * 230) + 90;

//	hModel = Model::Load("no0.fbx");
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}
