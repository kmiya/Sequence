#ifndef _SokoBan_SokoBan_h
#define _SokoBan_SokoBan_h

#include "Object.h"

#include <vector>

namespace image {
class Image;
} // namespace image

namespace sokoban {

class Object;

class SokoBan {
public:
  SokoBan(const char *stage, const int &size);
  ~SokoBan();
  int Update(); // クリアか中止なら 0 を返す．それ以外は1．
  void Draw();
  void Reset(); // 初期状態に戻す

private:
  typedef struct { int x; int y; } Position;

  void SetSize(const char *stage, const int &size);
  void Move(const Position& from, const Position& move, const Position& next);
  int ClearOrNot() const;

  image::Image *kImage_;
  std::vector<std::vector<Object>> stage_, initial_state_;
  int kStageWidth_;
  int kStageHeight_;
  int kMoveCount_;
  const int kNotClear_;
};

} // namespace sokoban

#endif // _SokoBan_SokoBan_h