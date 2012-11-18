#include "Image.h"
using namespace image;

#include "File.h"

#include "GameLib\Framework.h"
using namespace GameLib;

Image::Image(const char* file_name) : kHeight_(0), kWidth_(0), kImage_(nullptr) {
  file::File file(file_name);
  kHeight_ = file.GetUnsigned(12);
  kWidth_  = file.GetUnsigned(16);
  kImage_ = new unsigned[kHeight_ * kWidth_];
  for ( int i = 0; i < kHeight_ * kWidth_; ++i) {
    kImage_[i] = file.GetUnsigned(128 + i * 4);
  }
}
Image::~Image() {
  delete[] kImage_;
  kImage_ = nullptr;
}
void Image::Draw() const {
  Draw(0, 0, 0, 0, kWidth_, kHeight_);
}
void Image::Draw( const int dstX, const int dstY, 
                  const int srcX, const int srcY,
                  const int width, const int height) const
{
  Framework f             = Framework::instance();
  unsigned *vram          = f.videoMemory();
  const int window_height = f.height();
  const int window_width  = f.width();
  const int maximum_size  = window_height * window_width;
  // y が不要な計算はループの外に出して高速化
  const int pre_targetY   = dstY * window_width + dstX;
  const int pre_sourceY   = srcY * kWidth_ + srcX;
  for (int y = 0; y < height; ++y) {
    // x が不要な計算はループの外に出して高速化
    const int targetY = y * window_width + pre_targetY;
    const int sourceY = y * kWidth_ + pre_sourceY;
    for (int x = 0; x < width; ++x) {
      const int pos = targetY + x;
      // 画像メモリの範囲外に書き込んでないかチェック
      if (pos >= 0 && pos < maximum_size) {
        unsigned *dst = &vram[pos];
        const unsigned src = kImage_[sourceY + x];
        const unsigned srcA = (src & 0xff000000) >> 24;
        const unsigned srcR = src & 0x00ff0000;
        const unsigned srcG = src & 0x0000ff00;
        const unsigned srcB = src & 0x000000ff;
        const unsigned dstR = *dst & 0x00ff0000;
        const unsigned dstG = *dst & 0x0000ff00;
        const unsigned dstB = *dst & 0x000000ff;
        const unsigned r = (srcR - dstR) * srcA / 255 + dstR;
        const unsigned g = (srcG - dstG) * srcA / 255 + dstG;
        const unsigned b = (srcB - dstB) * srcA / 255 + dstB;
        *dst = (r & 0xff0000) | (g & 0x00ff00) | b;
      } else {
        // 範囲外書き込み
        //cout << "[Image.cc] Out of range error! (" << x << "," << y << ")" << endl;
        return;
      }
    }
  }
}
void Image::DrawBlack() const {
  Framework f    = Framework::instance();
  unsigned *vram = f.videoMemory();
  const auto height = f.height();
  const auto width  = f.width();
  for (auto y = 0; y < height; ++y) {
    for (auto x = 0; x < width; ++x) {
      vram[y * height + x] = 0x00000000;
    }
  }
}