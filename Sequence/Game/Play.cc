#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Clear.h"
#include "SokoBan.h"

namespace sequence {
namespace game {

Child* Play::Update(Parent* parent) {
  const int not_cleared = parent->kGame_->Update();
  parent->kGame_->Draw(); // ‚±‚±‚É“ü‚ê‚È‚¢‚Æ‰æ–Ê•`Ê‚ªˆêè‡’x‚ê‚é
  Child* next = this;
  if (!not_cleared) {
    next = new Clear();
  }
  return next;
}

} // namespace game
} // namespace sequence