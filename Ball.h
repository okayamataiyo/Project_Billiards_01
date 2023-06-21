#include "Engine/GameObject.h"
#pragma once
class Ball : public GameObject
{

public:
	//コンストラクタ
//引数：parent  親オブジェクト（SceneManager）
	Ball(GameObject* parent);

	~Ball();

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//ボール番号(1~9)を指定,白玉は0
	void SetNumber(int no);

	//ボールに力を加える
	void AddForce(XMVECTOR f);

	XMVECTOR GetVelocity() { return velocity; }

	XMFLOAT3 GetNextPosition() { return GetPosition() + velocity; }
private:
	int hModel;

	//ボールの番号
	int number;

	//移動速度
	XMVECTOR velocity;


};

