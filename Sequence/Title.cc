#include "GameLib/Framework.h"
#include "Image.h"
#include "Sequence/Parent.h"
#include "Sequence/Child.h"
#include "Sequence/Title.h"
#include "Sequence/StageSelect.h"

using namespace GameLib;

namespace sequence {
using namespace sequence;

Title::Title() : kTitleImage_(nullptr) {
  kTitleImage_ = new image::Image("data/image/title.dds");
  ASSERT(kTitleImage_ && "A title image didn't found!");
}
Title::~Title() {
  SAFE_DELETE(kTitleImage_);
}
Child* Title::Update(Parent* parent) {
  Child* next = this;
  // Space button が押されたらステージセレクトへ
  if (Framework::instance().isKeyTriggered(' ')) {
    next = new StageSelect();
    ASSERT(next);
  }
  kTitleImage_->Draw();
  return next;
}

} // namespace sequence