#pragma once
#include "Engine/GameObject.h"

//パワーケージシーンを管理するクラス
class PowerKage : public GameObject
{
	int hPictPowerKage_;
	int hPictPowerFlame_;

	int nowPw_, maxPw_, animPw_;
public:
	//コンストラクタ
	PowerKage(GameObject* parent);

	//デストラクタ
	~PowerKage();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPw(int nowPw, int maxPw)
	{
		nowPw_ = nowPw;
		maxPw_ = maxPw;
		animPw_ = (animPw_ * 9 + nowPw_) / 10;
	}
};

