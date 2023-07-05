#include "PowerGauge.h"
#include "Engine/Image.h"


PowerGauge::PowerGauge(GameObject* parent)
	:GameObject(parent, "PowerGauge"), hPictPowerGauge_(-1), hPictPowerFlame_(-1)
//	,maxPw_(180), nowPw_(1),animPw_(0)
{

}

//�f�X�g���N�^
PowerGauge::~PowerGauge()
{

}

//������
void PowerGauge::Initialize()
{
	hPictPowerGauge_ = Image::Load("PowerGauge.png");
	assert(hPictPowerGauge_ >= 0);

	ImageWidth = 512;
	ImageHeight = 64;

	hPictPowerFlame_ = Image::Load("LifeKageflame.png");
	assert(hPictPowerFlame_ >= 0);

	transform_.position_.x = -0.5f;
	transform_.position_.y = -0.65f;
}

//�X�V
void PowerGauge::Update()
{
	nowPw_ += 0.01f;
	if (nowPw_ > maxPw_)
		nowPw_ = 0.0f;
}

//�`��
void PowerGauge::Draw()
{
//	Transform transGauge = transform_;
//	transGauge.scale_.x = (float)animPw_ / (float)maxPw_;
	int left = ImageWidth/2-ImageWidth/2*nowPw_;
	int width = ImageWidth * nowPw_;
	Image::SetRect(hPictPowerGauge_,left,0,width,ImageHeight);
	Image::SetTransform(hPictPowerGauge_, transform_);
	Image::Draw(hPictPowerGauge_);

	Image::SetTransform(hPictPowerFlame_, transform_);
	Image::Draw(hPictPowerFlame_);

}

//�J��
void PowerGauge::Release()
{

}
