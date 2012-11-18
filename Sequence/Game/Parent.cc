#include "GameLib/Framework.h"
#include "Sequence/Parent.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Child.h"
#include "Sequence/Game/Loading.h"
#include "SokoBan.h"
#include "File.h"

#include <sstream>
using namespace std;

namespace sequence {
namespace game {

Parent::Parent(const int stage_number) : kMoveTo_(kNone), kChild_(nullptr), kGame_(nullptr) {
  ostringstream oss;
  oss << "data/stageData/" << stage_number << ".txt";
  file::File file(oss.str().c_str());
  oss.str("");
  ASSERT(file.GetData() && "Cannot find a stage data.");
  kGame_ = new sokoban::SokoBan(file.GetData(), file.GetSize());
  kGame_->Draw();
  kChild_ = new Loading();
  ASSERT(kChild_);
}
Parent::~Parent() {
  SAFE_DELETE(kChild_);
  SAFE_DELETE(kGame_);
}
Child* Parent::Update(sequence::Parent* parent) {
  Child* next = kChild_->Update(this);
  if (next != kChild_) {
    SAFE_DELETE(kChild_);
    kChild_ = next;
  }
  switch(kMoveTo_) {
    case kTitle:
      parent->MoveTo(sequence::Parent::kTitle);
      break;
    case kStageSelect:
      parent->MoveTo(sequence::Parent::kStageSelect);
      break;
    default:
      next = nullptr;
      break;
  }
  kMoveTo_ = kNone;
  return next;
}
void Parent::MoveTo(const kSeq seq) {
  kMoveTo_ = seq;
}

} // namespace game
} // namespace sequence