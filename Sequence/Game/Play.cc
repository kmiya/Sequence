#include "GameLib/Framework.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Clear.h"
#include "SokoBan.h"

using namespace GameLib;

namespace sequence {
namespace game {

Child* Play::Update(Parent* parent) {
  Child* next = this;
  if (Framework::instance().isKeyTriggered(' ')) {
    next = new Menu();
    ASSERT(next);
  } else {
    const int not_cleared = parent->GameUpdate();
    if (!not_cleared) {
      next = new Clear();
      ASSERT(next);
    }
  }
  return next;
}

} // namespace game
} // namespace sequence