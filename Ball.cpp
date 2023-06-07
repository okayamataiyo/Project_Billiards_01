#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <assert.h>


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
	//0.001������
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	//velocity�̒���len�����߂�
	//len����0.001���炷(0�ȉ��ɂȂ�����0�ɂ���)
	//velocity�̒�����len�ɂ���
//	XMVECTOR lenVec = XMVector3Length(velocity);
//	float len = XMVectorGetX(lenVec);
	float len = Length(velocity);
	len -= 0.001f;
	velocity = XMVector3Normalize(velocity) * len;

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
	assert(hModel >= 0);
}

void Ball::AddForce(XMVECTOR f)
{
	velocity += f;
}
