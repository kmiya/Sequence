#ifndef _SokoBan_Sequence_Parent_h
#define _SokoBan_Sequence_Parent_h

namespace sequence {

class Child;

namespace game {
class Parent;
} // namespace game

class Parent {
public:
  typedef enum {kTitle, kStageSelect, kNone} kSeq;
  Parent();
  ~Parent();
  Child* Update(Parent* parent);
  void StartGame(const int stage_number);
  void MoveTo(const kSeq);

private:
  kSeq kMoveTo_;
  Child* kChild_;
  game::Parent* kGame_;
};

} // namespace sequence

#endif // _SokoBan_Sequence_Parent_h