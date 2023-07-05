#include "TestScene.h"
#include "ball.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Player.h"
#include "PowerGauge.h"
#include "Ready.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	static const struct {
		float x, y;
	} start[] = {
		{0, 0,},
		{4, 0,},
		{2, 2,},
		{2,-2,},
		{1, 1,},
		{1,-1,},
		{3, 1,},
		{3,-1,},
		{2, 0,},
	};
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	for (int i = 0; i < 9; i++)
	{
		Ball* b = Instantiate<Ball>(this);
		b->SetNumber(i + 1);
		b->SetPosition((start[i].x) * 1.732 + 10, 0, (0, start[i].y) * 1.2);
	}

	Player* p = Instantiate<Player>(this);
	Ball* b = Instantiate<Ball>(this);
	b->SetPosition(-10, 0, 10);
	b->SetNumber(0); //����
	p->SetMyBall(b); 


	PowerGauge* g = Instantiate<PowerGauge>(this);
	g->SetPosition(-0.8, -0.5);
	Ready* pReady = Instantiate<Ready>(this);
}

//�X�V
void TestScene::Update()
{
	TestScene* pScene = FindGameObject<TestScene>();
	if (pScene == nullptr)
		return;
	//�����ł߂荞��ł�ʂ�T���Ĉ����͂���
	std::list<Ball*> balls = FindGameObjects<Ball>();	//���ׂẴ{�[���̃��X�g
	for (auto itr1 = balls.begin(); itr1 != balls.end(); itr1++) {
		for (auto itr2 = itr1; itr2 != balls.end(); itr2++) {

			if (itr1 == itr2)
				continue;
			// *itr1��*itr2�̍��W�����āA�������͂���
			XMVECTOR distance = (*itr1)->GetPosition() - (*itr2)->GetPosition();
			if (Length(distance) < 1.0f * 2.0f) {

				//�d�Ȃ��Ă���
				float depth = 1.0f * 2.0f - Length(distance);	//�߂荞�ݗ�
				//�߂荞�ݗʂ̔������ړ�����΂���
				distance = XMVector3Normalize(distance) * depth / 2.0f;
				(*itr1) ->SetPosition((*itr1)->GetPosition() + distance);
				(*itr2)->SetPosition((*itr2)->GetPosition() + distance*(-1.0f));
			}
		}
	}


}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
