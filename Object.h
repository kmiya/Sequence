//
// [�֎~����] SokoBan.h �ȊO����� include
//

#ifndef _SokoBan_Object_h
#define _SokoBan_Object_h

namespace image {
class Image;
} // namespace image

namespace sokoban {

class Object {
public:
  typedef struct { int x; int y; } Position;
  typedef enum { kUnknown, kEmpty, kWall, kPlayer, kBox, kGoal, kPlayerOnGoal, kBoxOnGoal } Item;
  typedef enum { kImagePlayer, kImageWall, kImageBox, kImageGoal, kImageEmpty } ImageID;
  
  Object();
  ~Object(){};
  Object(const Object& obj) : kDot_(32) {   // �v�f���m�̃R�s�[���s���R�s�[�R���X�g���N�^
        kComeFrom_ = obj.kComeFrom_;
        kItem_     = obj.kItem_;
  }
  Object& Copy(const Object& obj) {          // �R�s�[�֐�
    if (this == &obj) { return *this; }
    kComeFrom_ = obj.kComeFrom_;
    kItem_     = obj.kItem_;
    return *this;
  }
  Object& operator =(const Object& obj) {    // �R�s�[���Z�q
    return Copy(obj);
  }
  void Set(const char c, const int x, const int y);
  void Move(const int x, const int y, const Item ReplacedItem);
  void DrawBackground(const int x, const int y, const image::Image *image) const;
  void DrawForeground(const int x, const int y, const image::Image *image, const int move_count) const;
  void DrawCell(const int x, const int y, const ImageID id, const image::Image *image) const;
  void DrawCell(const int x, const int y, const int dx, const int dy, const ImageID id, const image::Image *image) const;

  Position kComeFrom_;   // �ړ��O�̈ʒu
  Item kItem_;           // ���ʒu�̏��

private:
  const int kDot_;       // �u���b�N�̉摜�̉��� & �c��
};

} // namespace sokoban

#endif // _SokoBan_Object_h