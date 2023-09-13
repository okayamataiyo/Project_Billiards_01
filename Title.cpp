#include <cmath>
#include <vector>
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Title.h"

namespace {
	float startX;		//移動開始X座標
	float endX;			//移動終了X座標
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

//コンストラクタ
Title::Title(GameObject* parent)
	:GameObject(parent, "TitleScene"), hPict_{-1, -1}
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;

}

//初期化
void Title::Initialize()
{
	//画像データのロード
	hPict_[1] = Image::Load("FoodButtonGive.png");
	hPict_[2] = Image::Load("CommonButtonBack.png");
	assert(hPict_ >= 0);
	startX = 5.0;
	endX = 0;
	totalTime = 3.0;
	currentTime = 0.0f;
}

float easeInOutSine(float x) {
	return -(std::cos(3.14 * x) - 1) / 2;
}

//更新
void Title::Update()
{
	seq_time += 1.0f / 60.0f;	//時間を進める
	if (seq_time >= tbl[seq_line + 1].time) {	//次の行を実行する
		seq_line++;
		switch (tbl[seq_line].action) {
		case A_SLIDEIN:
			startX = tbl[seq_line].param;//paramから0に向かって移動
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_WAIT:
			startX = transform_.position_.x;//今の場所で動かない
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		}

		//その行を実行する
	}

	currentTime += 1.0f / 60.0f;	//1フレーム分の時間を進める
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//ここを0.0~1.0の範囲にする
	float val = easeInOutSine(t);//イージング関数を呼ぶ(t);	帰ってきた値は0.0~1.0
	//valをもとに、transform_.position_を設定する
	transform_.position_.x = val * (endX - startX) + startX;
	if (Input::IsKey(DIK_S))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

//描画
void Title::Draw()
{
	Image::SetTransform(hPict_[1], transform_);
	Image::Draw(hPict_[1]);

	Image::SetTransform(hPict_[2], transform_);
	Image::Draw(hPict_[2]);
}

void Title::Release()
{
}
