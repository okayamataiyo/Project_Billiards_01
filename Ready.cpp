#include<cmath>
#include "Ready.h"
#include "Engine/Image.h"

namespace {
	float startX;	//移動開始X座標
	float endX;		//移動終了X座標
	float totalTime;	//移動時間(秒)
	float currentTime;	//現在の時間
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
	currentTime += 1.0f / 60.0f;	//1フレーム分の時間を進める
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//ここを0.0~1.0の範囲にする
	float val = easeInOutQuint(t);//イージング関数を呼ぶ(t);	帰ってきた値は0.0~1.0
	//valをもとに、transform_.position_を設定する
	transform_.position_.x = val * (endX - startX) + startX;


}

void Ready::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}
