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
  void MoveTo(const kSeq seq);
  void GameReset() const;
  int GameUpdate() const;

private:
  kSeq kMoveTo_;
  Child* kChild_;
  sokoban::SokoBan* kGame_;
};

} // namespace game
} // namespace sequence

#endif // _SokoBan_Sequence_Game_Parent_h