#include "GameLib/Framework.h"
#include "Sequence/Parent.h"
#include <iostream>
#include <memory>

using namespace GameLib;

void mainLoop();

namespace {
sequence::Parent* gPlayGame = nullptr;
}

namespace GameLib {
void Framework::update() {
  // �Œ�t���[�����[�g (���悻 1/5ms = 200 [fps])
  Framework::instance().setFrameRate(200);
  mainLoop();
}
} // namespace GameLib

void mainLoop() {
  // �I������
  if (Framework::instance().isEndRequested()){
    if (gPlayGame){
      SAFE_DELETE(gPlayGame);
    }
  }
  // ����������
  if (!gPlayGame) {
    gPlayGame = new sequence::Parent();
    ASSERT(gPlayGame && "Cannnot start a game.");
    gPlayGame->Update(gPlayGame);
    return;
  }
  // ���C�����[�v
  if (Framework::instance().isKeyOn('q')) {
    SAFE_DELETE(gPlayGame);
    Framework::instance().requestEnd();
    return;
  }
  gPlayGame->Update(gPlayGame);
}