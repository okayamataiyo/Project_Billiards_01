#include "TestScene.h"
#include "ball.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Player.h"
#include "PowerGauge.h"
#include "Ready.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
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
	b->SetNumber(0); //白玉
	p->SetMyBall(b); 


	PowerGauge* g = Instantiate<PowerGauge>(this);
	g->SetPosition(-0.8, -0.5);
	Ready* pReady = Instantiate<Ready>(this);
}

//更新
void TestScene::Update()
{
	TestScene* pScene = FindGameObject<TestScene>();
	if (pScene == nullptr)
		return;
	//ここでめり込んでる玉を探して引きはがす
	std::list<Ball*> balls = FindGameObjects<Ball>();	//すべてのボールのリスト
	for (auto itr1 = balls.begin(); itr1 != balls.end(); itr1++) {
		for (auto itr2 = itr1; itr2 != balls.end(); itr2++) {

			if (itr1 == itr2)
				continue;
			// *itr1と*itr2の座標を見て、無理やりはがす
			XMVECTOR distance = (*itr1)->GetPosition() - (*itr2)->GetPosition();
			if (Length(distance) < 1.0f * 2.0f) {

				//重なっている
				float depth = 1.0f * 2.0f - Length(distance);	//めり込み量
				//めり込み量の半分ずつ移動すればいい
				distance = XMVector3Normalize(distance) * depth / 2.0f;
				(*itr1) ->SetPosition((*itr1)->GetPosition() + distance);
				(*itr2)->SetPosition((*itr2)->GetPosition() + distance*(-1.0f));
			}
		}
	}


}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
