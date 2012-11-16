#include "GameLib\Framework.h"
using namespace GameLib;

#include "SokoBan.h"
using namespace sokoban;

#include "File.h"

#include <iostream>
#include <memory>

void mainLoop();

namespace {
SokoBan *kGame = nullptr;
unsigned kPreviousTime_[10];
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
    if (kGame){
      delete kGame;
      kGame = nullptr;
    }
  }
  // 初期化処理
  if (!kGame) {
    file::File file("stageData.txt");
    if (!file.GetData()) {
      GameLib::cout << "stage file could not be read." << endl;
      Framework::instance().requestEnd();
      return;
		}
    kGame = new SokoBan(file.GetData(), file.GetSize());
    GameLib::cout << "\n\n === New Game ===" << endl;
    kGame->Draw(); // 初回描写
    return;
  }
  // メインループ
  if (Framework::instance().isKeyOn('q')) {
		delete kGame;
  	kGame = nullptr;
		Framework::instance().requestEnd();
    return;
	}
  const int not_cleared = kGame->Update();
  kGame->Draw(); // ここに入れないと画面描写が一手順遅れる
  if (!not_cleared) {
    delete kGame;
    kGame = nullptr;
  }
}