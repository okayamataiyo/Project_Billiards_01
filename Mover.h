#pragma once

// �⊮���Ȃ���ړ�����N���X
// �l��float�̏ꍇ

class Mover {
public:
	Mover();
	~Mover();
	void Update(); // �⊮����v�Z�����镔��

	/// <summary>
	/// �ړ����J�n������
	/// </summary>
	/// <param name="from">�X�^�[�g�̒l</param>
	/// <param name="target">�I���̒l</param>
	/// <param name="sec">�ω������鎞��</param>
	void Start(float from, float target, float sec);

	/// <summary>
	/// ���̒l����ړ�������
	/// </summary>
	/// <param name="target">�I���̒l</param>
	/// <param name="sec">�ω������鎞��</param>
	void MoveTo(float target, float sec);

	/// <summary>
	/// ���̒l��Ԃ�
	/// </summary>
	/// <returns>���̒l</returns>
	float GetCurrent() { return currentValue; }

	/// <summary>
	/// �⊮�ړ����I����������ׂ�
	/// </summary>
	/// <returns>�I�������true</returns>
	bool IsFinished() {
		return (currentTime >= moveTime);
	}

private:
	float begin; // �J�n���̒l
	float end;   // �I�����̒l
	float moveTime; // �ړ�������
	float currentTime; // ���̌o�ߎ���
	float currentValue; // ���̒l
	// rate(����)��currentTime / moveTime�ŋ��܂�܂�
};