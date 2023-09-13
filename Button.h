#pragma once
#include "Engine/GameObject.h"

//ボタンを管理するクラス
class Button : public GameObject
{
	
public:
	//コンストラクタ
	Button(GameObject* parent);
	~Button();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;

	void SetImage(std::string normal, std::string pushed);

	void SetPosition(int x, int y);		//ボタン表示位置

	void Push(bool pushed);				//ボタンを押したか、押してないか
	
	bool MouseInArea(XMFLOAT3 mousePos);//マウスがボタン内に入っているか

	/// <summary>
	/// ボタンを移動させる
	/// </summary>
	/// <param name="toX">移動後の座標X</param>
	/// <param name="toY">移動後の座標Y</param>
	/// <param name="seconds">移動時間(秒)</param>
	void SetMovePosition(int toX, int toY, float seconds);

	/// <summary>
	/// 動いているならtrue
	/// </summary>
	/// <returns></returns>
	bool IsMoving();

	/// <summary>
	/// 強制的に移動を終了させる
	/// </summary>
	void ForceMoveEnd();

private:
	int hImage;		//通常画像番号
	int pushed;		//押された画像
	int hPush;		//押されているか
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};

	//動きを作る
	XMFLOAT3 startPos;
	XMFLOAT3 endPos;
	XMFLOAT3 center;	//ボタンの中心座標(画面座標)
	XMFLOAT3 size;		//ボタンの画像サイズ
	float totalTime;
	float currentTime;
};

