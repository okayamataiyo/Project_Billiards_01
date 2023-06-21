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
	//0.001������
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	//velocity�̒���len�����߂�
	//len����0.001���炷(0�ȉ��ɂȂ�����0�ɂ���)
	//velocity�̒�����len�ɂ���
//	XMVECTOR lenVec = XMVector3Length(velocity);
//	float len = XMVectorGetX(lenVec);
	float len = Length(velocity);
	len -= 0.001f;
	if (len < 0.0f) len = 0.0f;
	velocity = XMVector3Normalize(velocity) * len;
	//�{�[���ǂ����Ŕ��˂���
	std::list<Ball*> all = GetParent()->FindGameObjects<Ball>();
	for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++) {
		if (*itr == this)continue;
		XMFLOAT3 next = transform_.position_ + velocity;		//�����̈ړ���̈ʒu
		XMFLOAT3 other = (*itr)->GetNextPosition();				//����̈ړ���̈ʒu
		if (Length(next - other) <1.0f * 2.0f ) { //�ʂ̔��a2��

			XMVECTOR n = other - next;
			n = XMVector3Normalize(n);			//n�̒�����1�ɂ���
			XMVECTOR powDot = XMVector3Dot(velocity, n);
			float pow = XMVectorGetX(powDot);	//�����͂̑傫��
			//n�͉����͂̌����Apow�͉����͂̑傫��
			XMVECTOR push = n * pow;			//�����x�N�g��������ɓn������
			velocity -= push;
			(*itr)->AddForce(push);

			n = next - other;
			n = XMVector3Normalize(n);			//n�̒�����1�ɂ���
			powDot = XMVector3Dot((*itr)->GetVelocity(), n);
			pow = XMVectorGetX(powDot);			//�����͂̑傫��
			//n�͉����͂̌����Apow�͉����͂̑傫��
			push = n * pow;						//�����x�N�g��������ɓn������
			(*itr)->AddForce(-push);			//���肩�����
			AddForce(push);						//�����ɉ�����
		}
	
	}
	
	//�ǂɔ��˂���
	XMFLOAT3 next = transform_.position_ + velocity;
	if (next.x >= 35.0f)
	{
		XMVECTOR n = XMVectorSet(-1, 0, 0, 0);		//�E�̕ǂ̖@��(������1)
		n = n * -1;									//�t�����ɂ���=�ǂɌ������x�N�g��
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//�ǂ������̗͂�
		float ip = XMVectorGetX(ipvec);				//�ǂ������͂̑傫��
		XMVECTOR push = n * ip;						//�ǂ������x�N�g��
		XMVECTOR th = velocity - push;				//�ǂɉ����Ă�x�N�g��
		push *= -1;									//�����Ԃ��ꂽ�x�N�g��
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f,velocity);
//		f.x = f.x * -1;
		//f�����H����
//		velocity = XMLoadFloat3(&f);

	}
	if (next.x <= -35.0f)
	{
		XMVECTOR n = XMVectorSet(1, 0, 0, 0);		//���̕ǂ̖@��(������1)
		n = n * -1;									//�t�����ɂ���=�ǂɌ������x�N�g��
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//�ǂ������̗͂�
		float ip = XMVectorGetX(ipvec);				//�ǂ������͂̑傫��
		XMVECTOR push = n * ip;						//�ǂ������x�N�g��
		XMVECTOR th = velocity - push;				//�ǂɉ����Ă�x�N�g��
		push *= -1;									//�����Ԃ��ꂽ�x�N�g��
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f, velocity);
//		f.x = f.x * -1;
		//f�����H����
//		velocity = XMLoadFloat3(&f);
	}
	if (next.z >= 20.0f)
	{
		XMVECTOR n = XMVectorSet(0, 0, -1, 0);		//���̕ǂ̖@��(������1)
		n = n * -1;									//�t�����ɂ���=�ǂɌ������x�N�g��
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//�ǂ������̗͂�
		float ip = XMVectorGetX(ipvec);				//�ǂ������͂̑傫��
		XMVECTOR push = n * ip;						//�ǂ������x�N�g��
		XMVECTOR th = velocity - push;				//�ǂɉ����Ă�x�N�g��
		push *= -1;									//�����Ԃ��ꂽ�x�N�g��
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f, velocity);
//		f.z = f.z * -1;
		//f�����H����
//		velocity = XMLoadFloat3(&f);
	}
	if (next.z <= -20.0f)
	{
		XMVECTOR n = XMVectorSet(0, 0, 1, 0);		//���̕ǂ̖@��(������1)
		n = n * -1;									//�t�����ɂ���=�ǂɌ������x�N�g��
		XMVECTOR ipvec = XMVector3Dot(velocity, n);	//�ǂ������̗͂�
		float ip = XMVectorGetX(ipvec);				//�ǂ������͂̑傫��
		XMVECTOR push = n * ip;						//�ǂ������x�N�g��
		XMVECTOR th = velocity - push;				//�ǂɉ����Ă�x�N�g��
		push *= -1;									//�����Ԃ��ꂽ�x�N�g��
		velocity = push + th;

//		XMFLOAT3 f;
//		XMStoreFloat3(&f, velocity);
//		f.z = f.z * -1;
		//f�����H����
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
