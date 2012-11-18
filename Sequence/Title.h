#ifndef _SokoBan_Sequence_Title_h
#define _SokoBan_Sequence_Title_h

#include "Sequence/Child.h"

namespace image {
class Image;
} // namespace image

namespace sequence {
using namespace sequence;

class Parent;

class Title : public Child {
public:
  Title();
  ~Title();
  Child* Update(Parent* parent);

private:
  image::Image* kTitleImage_;
};

} // namespace sequence

#endif // _SokoBan_Sequence_Title_h