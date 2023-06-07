#include "Player.h"
#include "Ball.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent)
{
	direction = 0.0f;
	power = 0.3f;
}

Player::~Player()
{

}

void Player::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//‚±‚±‚Å‹Ê‚ð‘Å‚Â
		myBall->AddForce(XMVectorSet(0.1f, 0, 0.1f, 0));
	}
	if (Input::IsKeyDown(DIK_S))
	{
		myBall->AddForce(XMVectorSet(-0.1f, 0, -0.1f, 0));
	}
}

void Player::Draw()
{

}
