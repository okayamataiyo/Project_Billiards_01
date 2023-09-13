#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Title.h"
#include "Button.h"

/*
namespace {
	float startX;		//�ړ��J�nX���W
	float endX;			//�ړ��I��X���W
	float transY;		//��ɂ���Y���W
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
		A_END
	};
	struct Sequence {
		float time;	//����
		ACT action;	//��邱��
		float param;//�K�v�Ȓl
	};
	Sequence tbl[] = {
		{0.0f,A_SLIDEIN, 5.0f },	//�܂��̓X���C�h�C��
		{3.0f,A_WAIT, 0.0f},		//1�b�҂��Ă���
		{4.0f,A_END, 0.0f}			//�����ŏ�����
	};
	ACT currentAction;	//�����s���Ă���A�N�V����
	bool canMove;		//�ړ��ł���

}
*/

//�R���X�g���N�^
Title::Title(GameObject* parent)
	:GameObject(parent, "TitleScene")
{
	/*seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
	PushFlag_ = true;*/

}

//������
void Title::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

	//�摜�f�[�^�̃��[�h

	start = Instantiate<Button>(this);
	start->SetImage("FoodButtonGive", "FoodButtonGiveDisable");
	start->SetPosition(1920, 360 - 100);
	start->SetMovePosition(640, 360 - 100, 2.0f);
	back = Instantiate<Button>(this);
	back->SetImage("CommonButtonBack", "CommonButtonBackDisable");
	back->SetPosition(1920, 360 + 100);
	back->SetMovePosition(640, 360 + 100, 2.0f);

	//assert(hPict_ >= 0);
	/*
	startX = 5.0;
	endX = 0;
	totalTime = 3.0;
	currentTime = 0.0f;
	transY = 0.5f;
	*/
}

//�X�V
void Title::Update()
{
	/*
	seq_time += 1.0f / 60.0f;	//���Ԃ�i�߂�
	if (seq_time >= tbl[seq_line + 1].time) {	//���̍s�����s����
		seq_line++;
		switch (tbl[seq_line].action) {
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
		}

		//���̍s�����s����
	}

	currentTime += 1.0f / 60.0f;	//1�t���[�����̎��Ԃ�i�߂�
	if (currentTime > totalTime)	currentTime = totalTime;
	float t = currentTime / totalTime;//������0.0~1.0�͈̔͂ɂ���
	float val = easeInOutSine(t);//�C�[�W���O�֐����Ă�(t);	�A���Ă����l��0.0~1.0
	//val�����ƂɁAtransform_.position_��ݒ肷��
	giveTrans.position_.x = val * (endX - startX) + startX;
	backTrans.position_.x = val * (endX + startX) - startX;
	if (Input::IsKey(DIK_S))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
	if (Input::IsKey(DIK_W))	PushFlag_ = false;
	else	PushFlag_ = true;
	*/

	//�搶�̃R�[�h
	if (Input::IsMouseButtonDown(0)) {
		//�����Ă���Ȃ狭���X�g�b�v
		bool moving = false;
		if (start->IsMoving()) {
			start->ForceMoveEnd();
			moving = true;
		}
		if (back->IsMoving()) {
			back->ForceMoveEnd();
			moving = true;
		}
		//�����ĂȂ���΁������s
		if (!moving) {
			if (selected == START) {
				SceneManager* scene = dynamic_cast<SceneManager*>(FindObject("SceneManager"));
				scene->ChangeScene(SCENE_ID_TEST);
			}
		}
	}
	XMFLOAT3 pos = Input::GetMousePosition();
	if (start->MouseInArea(pos)) {
		start->Push(true);
		back->Push(false);
		selected = START;
	}
	else if (back->MouseInArea(pos)) {
		back->Push(true);
		start->Push(false);
		selected = BACK;
	}
	else {
		start->Push(false);
		back->Push(false);
		selected = NONE;
	}
}

//�`��
void Title::Draw()
{
	/*if (PushFlag_ == true) {
		Image::SetTransform(hPict_[0], giveTrans);
		Image::Draw(hPict_[0]);
		Image::SetTransform(hPict_[1], backTrans);
		Image::Draw(hPict_[1]);
	}
	else {
		Image::SetTransform(hPict_[2], giveTrans);
		Image::Draw(hPict_[2]);
		Image::SetTransform(hPict_[3], backTrans);
		Image::Draw(hPict_[3]);
	}*/

	//if(handle< 0 || handle >= )
}

void Title::Release()
{
}
