#include "GameLib/Framework.h"
#include "Sequence/Parent.h"
#include "Sequence/Child.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/StageSelect.h"

using namespace GameLib;

namespace sequence {

Parent::Parent() : kMoveTo_(kNone), kChild_(nullptr), kGame_(nullptr) {
  kChild_ = new Title();
}
Parent::~Parent() {
  SAFE_DELETE(kChild_);
  SAFE_DELETE(kGame_);
}
Child* Parent::Update(Parent* parent) {
  if (kGame_) {
    if (kChild_) {
      SAFE_DELETE(kChild_);
    }
    kGame_->Update(this);
    switch (kMoveTo_) {
      case kTitle:
        SAFE_DELETE(kGame_);
        kChild_ = new Title();
        ASSERT(kChild_);
        break;
      case kStageSelect:
        SAFE_DELETE(kGame_);
        kChild_ = new StageSelect();
        ASSERT(kChild_);
        break;
      default:
        kChild_ = nullptr;
    }
    kMoveTo_ = kNone;
    return kChild_;
  }
  Child* next = kChild_->Update(parent);
  if (next != kChild_) {
    SAFE_DELETE(kChild_);
    kChild_ = next;
  }
  return next;
}
void Parent::MoveTo(const kSeq seq) {
  kMoveTo_ = seq;
}
void Parent::StartGame(const int stage_number) {
  ASSERT(stage_number > 0 && stage_number < 10);
  kGame_ = new game::Parent(stage_number);
  ASSERT(kGame_);
}

} // namespace sequence