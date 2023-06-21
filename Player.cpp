#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

/*
* パワーケージを作成して、移動ボタンを押したら、カービィのかちわりメガトンパンチのような使用にする
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
		//ここで玉を打つ
		XMVECTOR base = XMVectorSet(0, 0, power, 0);	//回転してない時に移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction * 4);	//回転行列を作って
		XMVECTOR v = XMVector3Transform(base, yrot);	//その回転でベクトルの向きを変える
		myBall->AddForce(v);	//これが回転後の移動ベクトル
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
