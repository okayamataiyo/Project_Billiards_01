#include "PowerKage.h"
#include "Engine/Image.h"

//コンストラクタ
PowerKage::PowerKage(GameObject* parent)
	:GameObject(parent, "PowerKage"), hPictPowerKage_(-1), hPictPowerFlame_(-1),
	maxPw_(180), nowPw_(1),animPw_(0)
{

}

//デストラクタ
PowerKage::~PowerKage()
{

}

//初期化
void PowerKage::Initialize()
{
	hPictPowerKage_ = Image::Load("PowerKage.png");
	assert(hPictPowerKage_ >= 0);

	hPictPowerFlame_ = Image::Load("LifeKageflame.png");
	assert(hPictPowerFlame_ >= 0);

	transform_.position_.x = -0.5f;
	transform_.position_.y = -0.65f;
}

//更新
void PowerKage::Update()
{

}

//描画
void PowerKage::Draw()
{
	Transform transkage = transform_;
	transkage.scale_.x = (float)animPw_ / (float)maxPw_;
	Image::SetTransform(hPictPowerKage_, transkage);
	Image::Draw(hPictPowerKage_);

	Image::SetTransform(hPictPowerFlame_, transform_);
	Image::Draw(hPictPowerFlame_);

}

//開放
void PowerKage::Release()
{

}
