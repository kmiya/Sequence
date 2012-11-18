#include "GameLib/Framework.h"
#include "SokoBan.h"
#include "Image.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Child.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Clear.h"

using namespace GameLib;

namespace sequence {
namespace game {
using namespace sequence;

Clear::Clear() : kClearImage_(nullptr) {
  kClearImage_ = new image::Image("data/image/clear.dds");
  ASSERT(kClearImage_);
}
Clear::~Clear() {
  SAFE_DELETE(kClearImage_);
}
Child* Clear::Update(Parent* parent) {
  kClearImage_->Draw();
  if (Framework::instance().isKeyTriggered(' ')) {
    parent->MoveTo(Parent::kStageSelect);
  }
  return this;
}

} // namespace game
} // namespace sequence