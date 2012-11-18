#include "SokoBan.h"
#include "GameLib\Framework.h"
#include "Image.h"
#include <assert.h>
#include <fstream>

using namespace std;
using namespace GameLib;

namespace sokoban {

SokoBan::SokoBan(const char *stage, const int &size)
  : kNotClear_(1),
    kStageWidth_(-1),
    kStageHeight_(-1),
    kMoveCount_(0)
{
  // TODO: 不正な値のチェック処理を入れる．プレーヤーの数など
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
  // 初期状態を保存
  initial_state_ = stage_;
  // 画像読み込み
  kImage_ = new image::Image("data/image/nimotsuKunImage2.dds");
  ASSERT(kImage_);
}
SokoBan::~SokoBan() {
  delete kImage_;
  kImage_ = nullptr;
}
int SokoBan::Update() {
  // 移動終了
  if (kMoveCount_ >= 32) {
    kMoveCount_ = 0;
    // 移動を初期化
    for (int y = 0; y < kStageHeight_; ++y) {
      for (int x = 0; x < kStageWidth_; ++x) {
        stage_[y][x].kComeFrom_.x = x;
        stage_[y][x].kComeFrom_.y = y;
      }
    }
    return ClearOrNot();
  }
  // 移動中
  if (kMoveCount_ > 0) {
    kMoveCount_ += 1;
    return kNotClear_;
  }
  int pos_x = -1, pos_y = -1;
  // プレーヤーの位置を探索
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      if (stage_[y][x].kItem_ == Object::kPlayer || stage_[y][x].kItem_ == Object::kPlayerOnGoal) {
        pos_x = x;
        pos_y = y;
      }
    }
  }
  if (pos_x == -1 || pos_y == -1) {
    cout << "プレーヤーが存在しません" << endl;
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
  Move(from, move, next);
  return kNotClear_;
}
void SokoBan::Move(const Position& from, const Position& move, const Position& next) {
  // 一つ先がステージの範囲内か確認
  if (move.x < 0 || move.y < 0 || move.x >= kStageWidth_ || move.y >= kStageHeight_) {
    return;
  }
  Object &s_from = stage_[from.y][from.x];
  Object &s_move = stage_[move.y][move.x];
  // 一つ先が空かゴールの場合
  if (s_move.kItem_ == Object::kEmpty) {           // 移動先が空
    s_move.Move(from.x, from.y, Object::kPlayer);
  } else if (s_move.kItem_ == Object::kGoal) {     // 移動先がゴール
    s_move.Move(from.x, from.y, Object::kPlayerOnGoal);
  // 二つ先が荷物か，ゴールの上の荷物
  } else if (s_move.kItem_ == Object::kBox || s_move.kItem_ == Object::kBoxOnGoal) {
    // 二つ先がステージの範囲内か確認
    if (next.x < 0 || next.y < 0 || next.x >= kStageWidth_ || next.y >= kStageHeight_) {
      return;
    }
    Object &s_next = stage_[next.y][next.x];
    if (s_next.kItem_ == Object::kGoal) {          // 二つ先がゴール
      s_next.Move(move.x, move.y, Object::kBoxOnGoal);
    } else if (s_next.kItem_ == Object::kEmpty) {  // 二つ先が空
      s_next.Move(move.x, move.y, Object::kBox);
    } else {
      return;
    }
    (s_move.kItem_ == Object::kBoxOnGoal) ? s_move.Move(from.x, from.y, Object::kPlayerOnGoal)
                                          : s_move.Move(from.x, from.y, Object::kPlayer);
  } else {
    return;
  }
  // 現在プレイヤーはゴールに乗っている？
  (s_from.kItem_ == Object::kPlayerOnGoal) ? s_from.Move(from.x, from.y, Object::kGoal)
                                           : s_from.Move(from.x, from.y, Object::kEmpty);
  // 移動アニメーション開始
  kMoveCount_ = 1;
}
void SokoBan::Draw() {
  // 背景を描写
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      stage_[y][x].DrawBackground(x, y, kImage_);
    }
  }
  // 箱とプレーヤーを描写
  for (int y = 0; y < kStageHeight_; ++y) {
    for (int x = 0; x < kStageWidth_; ++x) {
      stage_[y][x].DrawForeground(x, y, kImage_, kMoveCount_);
    }
  }
}
void SokoBan::Reset() {
  stage_ = initial_state_;
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
        //最大値更新
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
  return 0;
}

} // namespace sokoban