#include "Object.h"
#include "Image.h"

namespace sokoban {
Object::Object() : kDot_(32) {
  Position kComeFrom_ = {0, 0};
  Item kItem_ = kUnknown;
}
void Object::Set(const char c, const int x, const int y) {
  switch(c) {
    case ' ': kItem_ = kEmpty;        break;
    case '#': kItem_ = kWall;         break;
    case 'p': kItem_ = kPlayer;       break;
    case 'o': kItem_ = kBox;          break;
    case '.': kItem_ = kGoal;         break;
    case 'P': kItem_ = kPlayerOnGoal; break;
    case 'O': kItem_ = kBoxOnGoal;    break;
    default : kItem_ = kUnknown;      break; // –³Œø‚È•¶Žš‚Í•Ç
  }
  kComeFrom_.x = x;
  kComeFrom_.y = y;
}
void Object::Move(const int x, const int y, const Item ReplacedItem) {
  kComeFrom_.x = x;
  kComeFrom_.y = y;
  kItem_ = ReplacedItem;
}
void Object::DrawBackground(const int x, const int y, const image::Image *image) const {
  ImageID id = kImageEmpty;
  switch (kItem_) {
    case kWall        : id = kImageWall; break;
    case kGoal        :
    case kPlayerOnGoal:
    case kBoxOnGoal   : id = kImageGoal; break;
    default           : id = kImageEmpty;
  }
  DrawCell(x, y, id, image);
}
void Object::DrawForeground(const int x, const int y, const image::Image *image, const int move_count) const {
  ImageID id = kImageEmpty;
  switch (kItem_) {
    case kPlayer      :
    case kPlayerOnGoal: id = kImagePlayer; break;
    case kBox         :
    case kBoxOnGoal   : id = kImageBox; break;
    default           : return;
  }
  const int dx = (x - kComeFrom_.x) * move_count;
  const int dy = (y - kComeFrom_.y) * move_count;
  DrawCell(kComeFrom_.x, kComeFrom_.y, dx, dy, id, image);
}
void Object::DrawCell(const int x, const int y, const ImageID id, const image::Image *image) const {
  DrawCell(x, y, 0, 0, id, image);
}
void Object::DrawCell(const int x, const int y, const int dx, const int dy, const ImageID id, const image::Image *image) const {
  image->Draw(x * kDot_ + dx, y * kDot_ + dy, id * kDot_, 0, kDot_, kDot_);
}

} // namespace sokoban;