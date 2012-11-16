#ifndef _SokoBan_Image_h
#define _SokoBan_Image_h

namespace image {

class Image {
public:
  Image(const char* file_name);
  ~Image();
  int GetWidth() const { return kWidth_; };
  int GetHeight() const { return kHeight_; };
  void Draw( const int dstX, const int dstY, 
             const int srcX, const int srcY,
             const int width, const int height) const;
private:
  int kHeight_;
  int kWidth_;
  unsigned* kImage;
};

} // namespace image

#endif // _SokoBan_Image_h