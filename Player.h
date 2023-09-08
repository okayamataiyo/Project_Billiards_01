#pragma once
#include "Engine/GameObject.h"

class Ball;

class Player : public GameObject
{
public:
	Player(GameObject* parent);
	~Player();
	void Update();
	void Draw();

	//プレイヤーが操作する玉
	void SetMyBall(Ball* ball) { myBall = ball; }
private:
	int hModel;
//	int nowPw_;
//	int maxPw_;

	int PowerGaugeFlag = 0;

	float PowerComPenSate = 0;

	Ball* myBall;

	//向き(Y回転の角度:ラジアン)
	float direction;

	//力の大きさ
	float power;

};

