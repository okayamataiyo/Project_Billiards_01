#include "Player.h"
#include "PowerGauge.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

/*
* 
* パワーケージを作成して、スペースボタンを押したら、カービィのかちわりメガトンパンチのケージのような操作にする
*/

namespace {
	static const float ROT_SPEED = 90.0f;	//1秒間で移動する角度(度)
	const float GAUGE_TIME = 0.5f;	//0から満タンになるための時間
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


	//PowerGaugeの力の増減
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

	//移動距離にnowPw_の補正をかける
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
			//ここで玉を打つ
			XMVECTOR base = XMVectorSet(0, 0, power * PowerComPenSate, 0);	//回転してない時に移動するベクトル
			XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
			XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
			myBall->AddForce(v);	//これが回転後の移動ベクトル
		}
	}
	
	//PowerGaugeFlagがすぐに変わり、再発動しないための処理
	/*if (nowPw_ == 0.0f) {
		PowerGaugeFlag = 0;
	}
	if (PowerGaugeFlag == 0) {
		nowPw_ = 2;
	}*/

	if (Input::IsKeyDown(DIK_S))
	{
		//ここで玉を打つ
		XMVECTOR base = XMVectorSet(0, 0, power, 0);	//回転してない時に移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
		XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
		myBall->AddForce(-v);
	}
	if (Input::IsKeyDown(DIK_LEFT))
	{
		//ここで玉を打つ
		XMVECTOR base = XMVectorSet(-power, 0, 0, 0);	//回転してない時に移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
		XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
		myBall->AddForce(v);
	}
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		//ここで玉を打つ
		XMVECTOR base = XMVectorSet(power, 0, 0, 0);	//回転してない時に移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
		XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
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
	//transform_.position_を設定
	//白い玉が原点にあるとして、白い玉のどこに表示するか
	//そこに、白い玉の座標を足せば、
	//表示座標が求まるので、transform_.position_に代入する

	XMVECTOR base = XMVectorSet(0, 0, 1.2, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//Y軸回転行列を作って
	XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
	transform_.position_ = myBall->GetPosition() + v;
	transform_.rotate_.y = (direction * 230) + 90;

//	hModel = Model::Load("no0.fbx");
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}
