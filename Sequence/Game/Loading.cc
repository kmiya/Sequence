#include "GameLib/Framework.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Loading.h"
#include "Sequence/Game/Play.h"
#include "Image.h"

namespace sequence {
namespace game {

Loading::Loading() : kLoadingImage_(nullptr), kCount_(0) {
  kLoadingImage_ = new image::Image("data/image/loading.dds");
  ASSERT(kLoadingImage_ && "Cannot open a loading image.");
}
Loading::~Loading() {
  SAFE_DELETE(kLoadingImage_);
}
Child* Loading::Update(Parent* parent) {
  Child* next = this;
  if (kCount_ == 60) {
    next = new Play();
    ASSERT(next);
  }
  ++kCount_;
  kLoadingImage_->Draw();
  return next;
}

} // namespace game
} // namespace sequence