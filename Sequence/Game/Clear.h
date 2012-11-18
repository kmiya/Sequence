#ifndef _SokoBan_Sequence_Game_Clear_h
#define _SokoBan_Sequence_Game_Clear_h

#include "Sequence/Game/Child.h"

namespace image {
class Image;
} // namespace image

namespace sequence {
namespace game {

class Parent;

class Clear : public Child {
public:
  Clear();
  ~Clear();
  Child* Update(Parent* parent);
private:
  image::Image* kClearImage_;
};

} // namespace game
} // namespace sequence

#endif // _SokoBan_Sequence_Game_Clear_h