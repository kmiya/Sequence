#ifndef _SokoBan_File_h
#define _SokoBan_File_h

namespace file {

class File {
public:
  File(const char* file_name);
  ~File();
  int GetSize() const { return kSize_; };
  const char* GetData() const { return kData_; };
  unsigned GetUnsigned(const int p) const;
private:
  int kSize_;
  char* kData_;
};

} // namespace file

#endif // _SokoBan_File_h