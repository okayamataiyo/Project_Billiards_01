#include "TestScene.h"
#include "ball.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Player.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
//	Camera::SetPosition()
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	for (int i = 0; i < 9; i++)
	{
		Ball* b = Instantiate<Ball>(this);
		b->SetNumber(i + 1);
		b->SetPosition((i - 4) * 1.4, 0, (i - 4) * 1.4);
	}

	Player* p = Instantiate<Player>(this);
	Ball* b = Instantiate<Ball>(this);
	b->SetNumber(0); //����
	p->SetMyBall(b); 
}

//�X�V
void TestScene::Update()
{
	TestScene* pScene = FindGameObject<TestScene>();
	if (pScene == nullptr)
		return;
}

//�`��
void TestScene::Draw()
{

}

//�J��
void TestScene::Release()
{
}
