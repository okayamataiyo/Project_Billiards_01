#pragma once
#include "Engine/GameObject.h"

namespace {
	const int PictNum_ = { 2 };
}

//タイトルシーンを管理するクラス
class Title : public GameObject
{
	int hPict_[PictNum_];	//画像番号
public:
	//コンストラクタ
	Title(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;
};

