#pragma once

// 補完しながら移動するクラス
// 値はfloatの場合

class Mover {
public:
	Mover();
	~Mover();
	void Update(); // 補完する計算をする部分

	/// <summary>
	/// 移動を開始させる
	/// </summary>
	/// <param name="from">スタートの値</param>
	/// <param name="target">終了の値</param>
	/// <param name="sec">変化させる時間</param>
	void Start(float from, float target, float sec);

	/// <summary>
	/// 今の値から移動させる
	/// </summary>
	/// <param name="target">終了の値</param>
	/// <param name="sec">変化させる時間</param>
	void MoveTo(float target, float sec);

	/// <summary>
	/// 今の値を返す
	/// </summary>
	/// <returns>今の値</returns>
	float GetCurrent() { return currentValue; }

	/// <summary>
	/// 補完移動が終わったか調べる
	/// </summary>
	/// <returns>終わったらtrue</returns>
	bool IsFinished() {
		return (currentTime >= moveTime);
	}

private:
	float begin; // 開始時の値
	float end;   // 終了時の値
	float moveTime; // 移動総時間
	float currentTime; // 今の経過時間
	float currentValue; // 今の値
	// rate(割合)はcurrentTime / moveTimeで求まります
};