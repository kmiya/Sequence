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
  // 固定フレームレート (およそ 1/5ms = 200 [fps])
  Framework::instance().setFrameRate(200);
  mainLoop();
}
} // namespace GameLib

void mainLoop() {
  // 終了判定
  if (Framework::instance().isEndRequested()){
    if (gPlayGame){
      SAFE_DELETE(gPlayGame);
    }
  }
  // 初期化処理
  if (!gPlayGame) {
    gPlayGame = new sequence::Parent();
    ASSERT(gPlayGame && "Cannnot start a game.");
    gPlayGame->Update(gPlayGame);
    return;
  }
  // メインループ
  if (Framework::instance().isKeyOn('q')) {
    SAFE_DELETE(gPlayGame);
    Framework::instance().requestEnd();
    return;
  }
  gPlayGame->Update(gPlayGame);
}