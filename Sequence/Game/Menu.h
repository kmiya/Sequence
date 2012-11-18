#ifndef _SokoBan_Sequence_Game_Menu_h
#define _SokoBan_Sequence_Game_Menu_h

#include "Sequence/Game/Child.h"

namespace image {
class Image;
} // namespace image

namespace sequence {
class Parent;

namespace game {

class Menu : public Child {
public:
  Menu();
  ~Menu();
  Child* Update(Parent* parent);

private:
  image::Image* kMenuImage_;
};

} // namespace sequence
} // namespace game

#endif //_SokoBan_Sequence_Game_Menu_h