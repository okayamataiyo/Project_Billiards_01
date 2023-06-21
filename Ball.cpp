#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <assert.h>
#include <list>

Ball::Ball(GameObject* parent) : GameObject(parent, "Ball"), hModel(-1)
{
	velocity = XMVectorSet(0.1f, 0, 0.1f, 0);
}

Ball::~Ball()
{
	if(hModel>0)
	Model::Release(hModel);
}

void Ball::Update()
{
	//0.001ずつ減る
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	//velocityの長さlenを求める
	//lenから0.001減らす(0以下になったら0にする)
	//velocityの長さをlenにする
//	XMVECTOR lenVec = XMVector3Length(velocity);
//	float len = XMVectorGetX(lenVec);
	float len = Length(velocity);
	len -= 0.001f;
	if (len < 0.0f) len = 0.0f;
	velocity = XMVector3Normalize(velocity) * len;
	//ボールどうしで反射する
	std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
	for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++) {
		if (*itr == this)continue;
		XMFLOAT3 next = transform_.position_ + velocity;		//自分の移動後の位置
		XMFLOAT3 other = (*itr)->GetNextPosition();				//相手の移動語の位置
		if (Length(next - other) <1.0f * 2.0f ) { //玉の半径2個分

			XMVECTOR n = other - next;
			n = XMVector3Normalize(n);			//nの長さを1にする
			XMVECTOR powDot = XMVector3Dot(velocity, n);
			float pow = XMVectorGetX(powDot);	//押す力の大きさ
			//nは押す力の向き、powは押す力の大きさ
			XMVECTOR push = n * pow;			//押すベクトル→相手に渡した力
			velocity -= push;
			(*itr)->AddForce(push);

			n = next - other;
			n = XMVector3Normalize(n);			//nの長さを1にする
			powDot = XMVector3Dot((*itr)->GetVelocity(), n);
			pow = XMVectorGetX(powDot);			//押す力の大きさ
			//nは押す力の向き、powは押す力の大きさ
			push = n * pow;						//押すベクトル→相手に渡した力
			(*itr)->AddForce(-push);			//相手から引く
			AddForce(push);						//自分に加える
		}
	
	}
	
	//壁に反射する
	XMFLOAT3 next = transform_.position_ + velocity;
	if (next.x >= 35.0f)
	{
		XMVECTOR n = XMVectorSet(-1, 0, 0, 0);		//右の壁の法線(長さが1)
		n = n * -1;									//逆向きにする=壁に向かうベクトル
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//壁を押す力の量
		float ip = XMVectorGetX(ipvec);				//壁を押す力の大きさ
		XMVECTOR push = n * ip;						//壁を押すベクトル
		XMVECTOR th = velocity - push;				//壁に沿ってるベクトル
		push *= -1;									//押し返されたベクトル
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f,velocity);
//		f.x = f.x * -1;
		//fを加工して
//		velocity = XMLoadFloat3(&f);

	}
	if (next.x <= -35.0f)
	{
		XMVECTOR n = XMVectorSet(1, 0, 0, 0);		//左の壁の法線(長さが1)
		n = n * -1;									//逆向きにする=壁に向かうベクトル
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//壁を押す力の量
		float ip = XMVectorGetX(ipvec);				//壁を押す力の大きさ
		XMVECTOR push = n * ip;						//壁を押すベクトル
		XMVECTOR th = velocity - push;				//壁に沿ってるベクトル
		push *= -1;									//押し返されたベクトル
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f, velocity);
//		f.x = f.x * -1;
		//fを加工して
//		velocity = XMLoadFloat3(&f);
	}
	if (next.z >= 20.0f)
	{
		XMVECTOR n = XMVectorSet(0, 0, -1, 0);		//左の壁の法線(長さが1)
		n = n * -1;									//逆向きにする=壁に向かうベクトル
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//壁を押す力の量
		float ip = XMVectorGetX(ipvec);				//壁を押す力の大きさ
		XMVECTOR push = n * ip;						//壁を押すベクトル
		XMVECTOR th = velocity - push;				//壁に沿ってるベクトル
		push *= -1;									//押し返されたベクトル
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f, velocity);
//		f.z = f.z * -1;
		//fを加工して
//		velocity = XMLoadFloat3(&f);
	}
	if (next.z <= -20.0f)
	{
		XMVECTOR n = XMVectorSet(0, 0, 1, 0);		//左の壁の法線(長さが1)
		n = n * -1;									//逆向きにする=壁に向かうベクトル
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//壁を押す力の量
		float ip = XMVectorGetX(ipvec);				//壁を押す力の大きさ
		XMVECTOR push = n * ip;						//壁を押すベクトル
		XMVECTOR th = velocity - push;				//壁に沿ってるベクトル
		push *= -1;									//押し返されたベクトル
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f, velocity);
//		f.z = f.z * -1;
		//fを加工して
//		velocity = XMLoadFloat3(&f);
	}
	transform_.position_ += velocity;
//	pos += velocity;
//	XMStoreFloat3(&transform_.position_, pos);
}

void Ball::Draw()
{
	if (hModel < 0)
		return;
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Ball::SetNumber(int no)
{
	number = no;
	hModel = Model::Load("DebugCollision/SphereCollider.fbx");
	std::string s = "no";
	s += std::to_string(number) + ".fbx";
	hModel = Model::Load(s);
	assert(hModel >= 0);
}

void Ball::AddForce(XMVECTOR f)
{
	velocity += f;
}
