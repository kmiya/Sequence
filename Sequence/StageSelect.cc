#include "GameLib/Framework.h"
#include "Image.h"
#include "Sequence/Parent.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Title.h"

using namespace GameLib;

namespace sequence {
using namespace sequence;

StageSelect::StageSelect() : kStageSelectImage_(nullptr) {
  kStageSelectImage_ = new image::Image("data/image/stageSelect.dds");
  ASSERT(kStageSelectImage_ && "Cannot find a stage selecting image.");
}
StageSelect::~StageSelect() {
  SAFE_DELETE(kStageSelectImage_);
}
Child* StageSelect::Update(Parent* parent) {
  Child* next = this;
  // Space button が押されたらステージセレクトへ
  int stage_number = 1;
  const char key[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (auto i = 1; i < 10; ++i) {
    if (Framework::instance().isKeyTriggered(key[i])) {
      parent->StartGame(i);
    }
  }
  // 0 が押されたらタイトルへ
  if (Framework::instance().isKeyTriggered('0')) {
    next = new Title();
  }
  kStageSelectImage_->Draw();
  return next;
}

} // namespace sequence