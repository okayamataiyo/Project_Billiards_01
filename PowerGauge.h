#pragma once
#include "Engine/GameObject.h"

//パワーケージシーンを管理するクラス
//ゲージクラスは、ゲージの最大を100%(つまり1.0)となるように作る。
//表示の大きさによって、表示サイズを変えれるように作る。
//表示する位置は、外から(使う側)から指定出来るようにする。
//加算する関数と、減産する関数と、現在の値を取得する関数を用意する。



class PowerGauge : public GameObject
{
	int hPictPowerGauge_;	//画像番号(ゲージの中身)
	int hPictPowerFrame_;	//画像番号(ゲージの外枠)
	float nowPw_;		//今の値
	const float maxPw_ = 1.0f;	//最大値
	float animPw_;		//dispHp	表示用の値
	int ImageWidth;		//ゲージ画像の幅
	int ImageHeight;	//ゲージ画像の高さ


public:
	static constexpr float MIN = 0.0f;
	static constexpr float MAX = 1.0f;

	//コンストラクタ
	PowerGauge(GameObject* parent);

	//デストラクタ
	~PowerGauge();

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
//		nowPw_ = nowPw;
//		maxPw_ = maxPw;
//		animPw_ = (animPw_ * 9 + nowPw_) / 10;
	}

	void SetPosition(float x, float y);

	/// <summary>
	/// 値を加減算する
	/// </summary>
	/// <param name="v"></param>
	void AddValue(float v);

	void SetValue(float v);

	float GetValue();
};

