#ifndef _SokoBan_Sequence_Game_Child_h
#define _SokoBan_Sequence_Game_Child_h

namespace sequence {
namespace game {

class Parent;

class Child {
public:
  virtual Child* Update(Parent*) = 0;
  virtual ~Child(){};
};

} // namespace game
} // namespace sequence

#endif // _SokoBan_Sequence_Game_Child_h