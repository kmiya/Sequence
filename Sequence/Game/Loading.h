#ifndef _SokoBan_Sequence_Game_Loading_h
#define _SokoBan_Sequence_Game_Loading_h

#include "Sequence/Game/Child.h"

namespace image {
class Image;
} // namespace image

namespace sequence {
class Parent;

namespace game {

class Loading : public Child {
public:
  Loading();
  ~Loading();
  Child* Update(Parent* parent);

private:
  image::Image* kLoadingImage_;
  int kCount_;
};

} // namespace sequence
} // namespace game

#endif //_SokoBan_Sequence_Game_Loading_h