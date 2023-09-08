#include <cmath>
#include <vector>
#include "Ready.h"
#include "Engine/Image.h"
#include "Player.h"

namespace {
	float startX;	//�ړ��J�nX���W
	float endX;		//�ړ��I��X���W
	float totalTime;	//�ړ�����(�b)
	float currentTime;	//���݂̎���

	//�����s���Ă���s
	int seq_line;
	//�V�[�P���X�����s���Ă��鎞��
	float seq_time;
	//��邱�Ƃ��R�}���h��
	enum ACT {
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDE_OUT,
		A_END
	};
	struct Sequence {
		float time;	//����
		ACT action;	//��邱��
		float param;//�K�v�Ȓl
	};
//	std::vector<Sequence> tbl[] = {
	Sequence tbl[] = {

		{0.0f,A_SLIDEIN, 5.0f},		//�܂��̓X���C�h�C��
		{3.0f,A_WAIT,0.0f},			//1�b�҂��Ă���
		{4.0f,A_SLIDE_OUT,-5.0f},	//�X���C�h�A�E�g
		{5.0f,A_END, 0.0f}			//�����ŏ�����
	};
	ACT currentAction;	//�����s���Ă���A�N�V����
	bool canMove;		//�ړ��ł���
}

Ready::Ready(GameObject* parent)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
	hImage = 0;
}

Ready::~Ready()
{

}

void Ready::Initialize()
{
	hImage = Image::Load("ready.png");
	startX = 5.0f;
	endX = 0;
	totalTime = 3.0;
	currentTime = 0.0f;
}

float easeInOutQuint(float x) {
	return x < 0.5 ? 16 * x * x * x * x : 1 - std::pow(-2 * x + 2, 5) / 2;
}

void Ready::Update()
{
	seq_time += 1.0f / 60.0f;	//���Ԃ�i�߂�
	if (seq_time >= tbl[seq_line + 1].time) {	//���̍s�����s����
		seq_line++;
		switch (tbl[seq_line].action) {
		case A_END:
				KillMe();
				break;
		case A_SLIDEIN:
			startX = tbl[seq_line].param;//param����0�Ɍ������Ĉړ�
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_WAIT:
			startX = transform_.position_.x;//���̏ꏊ�œ����Ȃ�
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_SLIDE_OUT:
			canMove = true;
			startX = transform_.position_.x;	//���̏ꏊ����param�Ɍ������Ĉړ�
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		}

		//���̍s�����s����
	}

	currentTime += 1.0f / 60.0f;	//1�t���[�����̎��Ԃ�i�߂�
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//������0.0~1.0�͈̔͂ɂ���
	float val = easeInOutQuint(t);//�C�[�W���O�֐����Ă�(t);	�A���Ă����l��0.0~1.0
	//val�����ƂɁAtransform_.position_��ݒ肷��
	transform_.position_.x = val * (endX - startX) + startX;


}

bool Ready::Finished() {
	return canMove;
}

void Ready::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//�C�[�W���O(0.0~1.0��⊮����Ȑ�)
//�X�v���C��(4�ȏ�̓_�����炩�ɒʂ�Ȑ��⊮)