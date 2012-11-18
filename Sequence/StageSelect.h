#ifndef _SokoBan_Sequence_StageSelect_h
#define _SokoBan_Sequence_StageSelect_h

#include "Sequence/Child.h"

namespace image {
class Image;
} // namespace image

namespace sequence {
using namespace sequence;

class Parent;

class StageSelect : public Child {
public:
  StageSelect();
  ~StageSelect();
  Child* Update(Parent* parent);

private:
  image::Image* kStageSelectImage_;
};

} // namespace sequence

#endif // _SokoBan_Sequence_StageSelect_h