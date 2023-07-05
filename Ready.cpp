#include<cmath>
#include "Ready.h"
#include "Engine/Image.h"

namespace {
	float startX;	//�ړ��J�nX���W
	float endX;		//�ړ��I��X���W
	float totalTime;	//�ړ�����(�b)
	float currentTime;	//���݂̎���
}

Ready::Ready(GameObject* parent)
{

}

Ready::~Ready()
{

}

void Ready::Initialize()
{
	hImage = Image::Load("ready.png");
	startX = 5.0f;
	endX = 0;
	totalTime = 3.0;
	currentTime = 0.0f;
}

float easeInOutQuint(float x) {
	return x < 0.5 ? 16 * x * x * x * x : 1 - std::pow(-2 * x + 2, 5) / 2;
}

void Ready::Update()
{
	currentTime += 1.0f / 60.0f;	//1�t���[�����̎��Ԃ�i�߂�
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//������0.0~1.0�͈̔͂ɂ���
	float val = easeInOutQuint(t);//�C�[�W���O�֐����Ă�(t);	�A���Ă����l��0.0~1.0
	//val�����ƂɁAtransform_.position_��ݒ肷��
	transform_.position_.x = val * (endX - startX) + startX;


}

void Ready::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}
