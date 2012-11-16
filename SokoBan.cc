#include "SokoBan.h"
using namespace std;

#include "GameLib\Framework.h"
using namespace GameLib;

#include "Image.h"

#include <assert.h>
#include <fstream>

namespace sokoban {

SokoBan::SokoBan(const char *stage, const int &size)
  : kNotClear_(1),
    kStageWidth_(-1),
    kStageHeight_(-1),
    kMoveCount_(0)
{
  // TODO: �s���Ȓl�̃`�F�b�N����������D�v���[���[�̐��Ȃ�
  SetSize(stage, size);
  vector<Object> line(kStageWidth_);
  int x = 0, y = 0;
  for (int i = 0; i < size; ++i) {
    if (stage[i] != '\n') {
      if (x < kStageWidth_) {
        line[x].Set(stage[i], x, y);
        ++x;
      }
    } else {
      stage_.push_back(line);
      x = 0;
      ++y;
    }
  }
  // �摜�ǂݍ���
  kImage_ = new image::Image("data/image/nimotsuKunImage2.dds");
}
SokoBan::~SokoBan() {
  delete kImage_;
  kImage_ = nullptr;
}
int SokoBan::Update() {
  // �ړ��I��
  if (kMoveCount_ >= 32) {
    kMoveCount_ = 0;
    // �ړ���������
    for (int y = 0; y < kStageHeight_; ++y) {
      for (int x = 0; x < kStageWidth_; ++x) {
        stage_[y][x].kComeFrom_.x = x;
        stage_[y][x].kComeFrom_.y = y;
      }
    }
  }
  // �ړ���
  if (kMoveCount_ > 0) {
    kMoveCount_ += 1;
    return kNotClear_;
  }
  int pos_x = -1, pos_y = -1;
  // �v���[���[�̈ʒu��T��
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      if (stage_[y][x].kItem_ == Object::kPlayer || stage_[y][x].kItem_ == Object::kPlayerOnGoal) {
        pos_x = x;
        pos_y = y;
      }
    }
  }
  if (pos_x == -1 || pos_y == -1) {
    cout << "�v���[���[�����݂��܂���" << endl;
    Framework::instance().requestEnd();
  }
  Position from, move, next;
  from.x = pos_x; from.y = pos_y;
  move.x = pos_x; move.y = pos_y;
  next.x = pos_x; next.y = pos_y;
  Framework f = Framework::instance();
  const bool inputW = f.isKeyOn('w');
  const bool inputA = f.isKeyOn('a');
  const bool inputS = f.isKeyOn('s');
  const bool inputZ = f.isKeyOn('z');
  if (inputW) {
    move.y -= 1; next.y -= 2;
  } else if (inputA) {
    move.x -= 1; next.x -= 2;
  } else if (inputS) {
    move.x += 1; next.x += 2;
  } else if (inputZ) {
    move.y += 1; next.y += 2;
  }
  return Move(from, move, next);
}
int SokoBan::Move(const Position& from, const Position& move, const Position& next) {
  // ��悪�X�e�[�W�͈͓̔����m�F
  if (move.x < 0 || move.y < 0 || move.x >= kStageWidth_ || move.y >= kStageHeight_) {
    return kNotClear_;
  }
  Object &s_from = stage_[from.y][from.x];
  Object &s_move = stage_[move.y][move.x];
  // ��悪�󂩃S�[���̏ꍇ
  if (s_move.kItem_ == Object::kEmpty) {           // �ړ��悪��
    s_move.Move(from.x, from.y, Object::kPlayer);
  } else if (s_move.kItem_ == Object::kGoal) {     // �ړ��悪�S�[��
    s_move.Move(from.x, from.y, Object::kPlayerOnGoal);
  // ��悪�ו����C�S�[���̏�̉ו�
  } else if (s_move.kItem_ == Object::kBox || s_move.kItem_ == Object::kBoxOnGoal) {
    // ��悪�X�e�[�W�͈͓̔����m�F
    if (next.x < 0 || next.y < 0 || next.x >= kStageWidth_ || next.y >= kStageHeight_) {
      return kNotClear_;
    }
    Object &s_next = stage_[next.y][next.x];
    if (s_next.kItem_ == Object::kGoal) {          // ��悪�S�[��
      s_next.Move(move.x, move.y, Object::kBoxOnGoal);
    } else if (s_next.kItem_ == Object::kEmpty) {  // ��悪��
      s_next.Move(move.x, move.y, Object::kBox);
    } else {
      return kNotClear_;
    }
    (s_move.kItem_ == Object::kBoxOnGoal) ? s_move.Move(from.x, from.y, Object::kPlayerOnGoal)
                                          : s_move.Move(from.x, from.y, Object::kPlayer);
  } else {
    return kNotClear_;
  }
  // ���݃v���C���[�̓S�[���ɏ���Ă���H
  (s_from.kItem_ == Object::kPlayerOnGoal) ? s_from.Move(from.x, from.y, Object::kGoal)
                                           : s_from.Move(from.x, from.y, Object::kEmpty);
  // �ړ��A�j���[�V�����J�n
  kMoveCount_ = 1;
  return ClearOrNot();
}
void SokoBan::Draw() {
  // �w�i��`��
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      stage_[y][x].DrawBackground(x, y, kImage_);
    }
  }
  // ���ƃv���[���[��`��
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      stage_[y][x].DrawForeground(x, y, kImage_, kMoveCount_);
    }
  }
}
void SokoBan::SetSize(const char *stage, const int &size) {
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i){
		switch (stage[i]){
			case '#': case ' ': case 'o': case 'O':
			case '.': case 'p': case 'P':
				++x;
				break;
			case '\n': 
				++y;
				//�ő�l�X�V
				kStageWidth_ = max(kStageWidth_, x);
				kStageHeight_ = max(kStageHeight_, y);
				x = 0;
				break;
		}
	}
}
int SokoBan::ClearOrNot() const {
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      if (stage_[y][x].kItem_ == Object::kBox)
        return kNotClear_;
    }
  }
  cout << "\nCongratulations!" << endl;
  return 0;
}

} // namespace sokoban