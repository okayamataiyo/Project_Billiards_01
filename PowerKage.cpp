#include "PowerKage.h"
#include "Engine/Image.h"

//�R���X�g���N�^
PowerKage::PowerKage(GameObject* parent)
	:GameObject(parent, "PowerKage"), hPictPowerKage_(-1), hPictPowerFlame_(-1),
	maxPw_(180), nowPw_(1)
{

}

//�f�X�g���N�^
PowerKage::~PowerKage()
{

}

//������
void PowerKage::Initialize()
{
	hPictPowerKage_ = Image::Load("LifeKage.png");
	assert(hPictPowerKage_ >= 0);

	hPictPowerFlame_ = Image::Load("LifeKageflame.png");
	assert(hPictPowerFlame_ >= 0);

	transform_.position_.x = -0.9f;
	transform_.position_.y = 0.85f;
}

//�X�V
void PowerKage::Update()
{

}

//�`��
void PowerKage::Draw()
{
	Transform transkage = transform_;
	transkage.scale_.x = (float)animPw_ / (float)maxPw_;
	Image::SetTransform(hPictPowerKage_, transkage);
	Image::Draw(hPictPowerKage_);

	Image::SetTransform(hPictPowerFlame_, transform_);
	Image::Draw(hPictPowerFlame_);

}

//�J��
void PowerKage::Release()
{

}
