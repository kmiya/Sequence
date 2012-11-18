#ifndef _SokoBan_Sequence_Game_Parent_h
#define _SokoBan_Sequence_Game_Parent_h

namespace sokoban {
class SokoBan;
} // namespace sokoban

namespace image {
class Image;
}

namespace sequence {
class Parent;

namespace game {

class Child;

class Parent {
public:
  typedef enum {kTitle, kStageSelect, kNone} kSeq;
  Parent(const int stage_number);
  ~Parent();
  Child* Update(sequence::Parent* parent);
  sokoban::SokoBan* kGame_;
  void MoveTo(const kSeq seq);

private:
  kSeq kMoveTo_;
  Child* kChild_;
};

} // namespace game
} // namespace sequence

#endif // _SokoBan_Sequence_Game_Parent_h