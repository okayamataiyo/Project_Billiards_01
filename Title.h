#pragma once
#include "Engine/GameObject.h"

class Button;

//タイトルシーンを管理するクラス
class Title : public GameObject
{
	Button* start;
	Button* back;
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};
	SELECT selected;
	//int hPict_[PictNum_];	//画像番号
	int PushFlag_;			//画像を押した時に切り替わるフラグ
	Transform giveTrans;
	Transform backTrans;
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

	void SetPosition(int x, int y);
};

