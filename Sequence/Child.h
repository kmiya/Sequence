#ifndef _SokoBan_Sequence_Child_h
#define _SokoBan_Sequence_Child_h

namespace sequence {

class Parent;

class Child {
public:
  virtual Child* Update(Parent*) = 0;
  virtual ~Child(){};
};

} // namespace sequence

#endif // _SokoBan_Sequence_Child_h