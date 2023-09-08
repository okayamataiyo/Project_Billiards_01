#include "PowerGauge.h"
#include "Engine/Image.h"
#include "assert.h"

PowerGauge::PowerGauge(GameObject* parent)
	:GameObject(parent, "PowerGauge"), hPictPowerGauge_(-1), hPictPowerFrame_(-1)
//	,maxPw_(180), nowPw_(1),animPw_(0)
{

}

//デストラクタ
PowerGauge::~PowerGauge()
{

}

//初期化
void PowerGauge::Initialize()
{
	//画像データをロード
	hPictPowerGauge_ = Image::Load("LifeGauge.png");
	assert(hPictPowerGauge_ >= 0);

	ImageWidth = Image::GetWidth(hPictPowerGauge_);
	ImageHeight = Image::GetHeight(hPictPowerGauge_);

	hPictPowerFrame_ = Image::Load("LifeGaugeflame.png");
	assert(hPictPowerFrame_ >= 0);

//	transform_.position_.x = -0.5f;
//	transform_.position_.y = -0.65f;
}

//更新
void PowerGauge::Update()
{
	/*nowPw_ += 0.01f;
	if (nowPw_ > maxPw_)
		nowPw_ = 0.0f;*/
}

//描画
void PowerGauge::Draw()
{
//	Transform transGauge = transform_;
//	transGauge.scale_.x = (float)animPw_ / (float)maxPw_;
	Image::SetTransform(hPictPowerFrame_, transform_);
	Image::Draw(hPictPowerFrame_);
	int left = ImageWidth/2-ImageWidth/2*nowPw_;
	int width = ImageWidth * nowPw_;
	Image::SetRect(hPictPowerGauge_,left,0,width,ImageHeight);
	Image::SetTransform(hPictPowerGauge_, transform_);
	Image::Draw(hPictPowerGauge_);

	Image::SetTransform(hPictPowerFrame_, transform_);
	Image::Draw(hPictPowerFrame_);

}

//開放
void PowerGauge::Release()
{

}

void PowerGauge::SetPosition(float x, float y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void PowerGauge::AddValue(float v)
{
	nowPw_ += v;
	if (nowPw_ < minPw_)
		nowPw_ = minPw_;
	else if (nowPw_ > maxPw_)
		nowPw_ = maxPw_;

}

void PowerGauge::SetValue(float v)
{
	assert(v >= 0.0f && v <= 1.0f);

	nowPw_ = v;
	if (nowPw_ < 0.0f)
		nowPw_ = 0.0f;
	else if (nowPw_ > maxPw_)
		nowPw_ = maxPw_;
}

float PowerGauge::GetValue()
{
	return nowPw_;
}
