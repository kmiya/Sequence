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
  // �Œ�t���[�����[�g (���悻 1/5ms = 200 [fps])
  Framework::instance().setFrameRate(200);
  mainLoop();
}

} // namespace GameLib

void mainLoop() {
  // �I������
  if (Framework::instance().isEndRequested()){
    if (kGame){
      delete kGame;
      kGame = nullptr;
    }
  }
  // ����������
  if (!kGame) {
    file::File file("stageData.txt");
    if (!file.GetData()) {
      GameLib::cout << "stage file could not be read." << endl;
      Framework::instance().requestEnd();
      return;
		}
    kGame = new SokoBan(file.GetData(), file.GetSize());
    GameLib::cout << "\n\n === New Game ===" << endl;
    kGame->Draw(); // ����`��
    return;
  }
  // ���C�����[�v
  if (Framework::instance().isKeyOn('q')) {
		delete kGame;
  	kGame = nullptr;
		Framework::instance().requestEnd();
    return;
	}
  const int not_cleared = kGame->Update();
  kGame->Draw(); // �����ɓ���Ȃ��Ɖ�ʕ`�ʂ���菇�x���
  if (!not_cleared) {
    delete kGame;
    kGame = nullptr;
  }
}