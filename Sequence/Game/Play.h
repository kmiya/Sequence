#ifndef _SokoBan_Sequence_Game_Play_h
#define _SokoBan_Sequence_Game_Play_h

#include "Sequence/Game/Child.h"

namespace sequence {
class Parent;

namespace game {

class Play : public Child {
public:
  Child* Update(Parent* parent);
};

} // namespace sequence
} // namespace game

#endif //_SokoBan_Sequence_Game_Play_h