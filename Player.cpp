#include "Player.h"
#include "PowerKage.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

/*
* パワーケージを作成して、移動ボタンを押したら、カービィのかちわりメガトンパンチのような使用にする
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
	//PowerKageの力の増減
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

	//移動距離にnowPw_の補正をかける
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
			//ここで玉を打つ
			XMVECTOR base = XMVectorSet(0, 0, power * PowerComPenSate, 0);	//回転してない時に移動するベクトル
			XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
			XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
			myBall->AddForce(v);	//これが回転後の移動ベクトル

			nowPw_ = 0;
		}
	}
	
	//PowerKageFlugがすぐに変わり、再発動しないための処理
	if (nowPw_ == 0.0f) {
		PowerKageFlug = 0;
	}
	if (PowerKageFlug == 0) {
		nowPw_ = 2;
	}

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

	PowerKage* pPowerKage = (PowerKage*)FindObject("PowerKage");
	pPowerKage->SetPw(nowPw_, maxPw_);
}

void Player::Draw()
{
	//transform_.position_を設定
	//白い玉が原点にあるとして、白い玉のどこに表示するか
	//そこに、白い玉の座標を足せば、
	//表示座標が求まるので、transform_.position_に代入する
	
	XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
	XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
	transform_.position_ = myBall->GetPosition() + v;

//	hModel = Model::Load("no0.fbx");
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}
