#include "Engine/Direct3D.h"
#include "Engine/Image.h"
#include "Engine/Model.h"
#include "Button.h"

namespace {
	float startX;		//移動開始X座標
	float endX;			//移動終了X座標
	float transY;		//常にいるY座標
	float totalTime;	//移動時間(秒)
	float currentTime;	//現在の時間

	//今実行している行
	int seq_line;
	//シーケンスを実行している時間
	float seq_time;
	//やることをコマンド化
	enum ACT {
		A_SLIDEIN = 1,
		A_WAIT,
		A_END
	};
	struct Sequence {
		float time;	//時間
		ACT action;	//やること
		float param;//必要な値
	};
	Sequence tbl[] = {
		{0.0f,A_SLIDEIN, 5.0f },	//まずはスライドイン
		{3.0f,A_WAIT, 0.0f},		//1秒待ってから
		{4.0f,A_END, 0.0f}			//ここで消える
	};
	ACT currentAction;	//今実行しているアクション
	bool canMove;		//移動できる
}

Button::Button(GameObject* parent)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
}

Button::~Button()
{
}

void Button::Initialize()
{

	pushed = false;
	hImage = -1;
	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.0f;
}

void Button::Update()
{
}

void Button::Draw()
{

	if (pushed) {
		Image::SetTransform(hPush, transform_);
		Image::Draw(hPush);
	}
	else {
		Image::SetTransform(hImage, transform_);
		Image::Draw(hImage);
	}
}

void Button::Release()
{
}

void Button::SetImage(std::string normal, std::string pushed)
{
	hImage = Image::Load((normal + ".png").c_str());
	hPush = Image::Load((pushed + ".png").c_str());
	size = Image::GetSize(hImage);
}

void Button::SetPosition(int x, int y)
{
	transform_.position_.x = (x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(y - Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ / 2);
	transform_.position_.x = (x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(y - Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ / 2);
	XMFLOAT3 center = XMFLOAT3(x, y, 0);
}

void Button::Push(bool pushed)
{
	this->pushed = pushed;
}

bool Button::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center.x) > size.x / 2)
		return false;
	if (abs(mousePos.y - center.y) > size.y / 2)
		return false;
	return true;
}

void Button::SetMovePosition(int toX, int toY, float seconds)
{
	startPos = center;	//今の座標をコピー
	endPos = XMFLOAT3((float)toX, (float)toY, 0);
	totalTime = seconds;
	currentTime = 0.0f;
}
