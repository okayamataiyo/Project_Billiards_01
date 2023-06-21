#include "Engine/GameObject.h"
#pragma once

class Ball;

class Player : public GameObject
{
public:
	Player(GameObject* parent);
	~Player();
	void Update();
	void Draw();

	//�v���C���[�����삷���
	void SetMyBall(Ball* ball) { myBall = ball; }
private:
	int hModel;

	int nowPw_;
	int maxPw_;

	int PowerKageFlug = 0;

	float PowerComPenSate = 0;

	Ball* myBall;

	//����(Y��]�̊p�x:���W�A��)
	float direction;

	//�͂̑傫��
	float power;

};

