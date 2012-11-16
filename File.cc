#include <fstream>

#include "File.h"

using namespace file;

File::File(const char* file_name) : kSize_(0), kData_(nullptr) {
  using namespace std;
	ifstream in(file_name, ifstream::binary);
	if (!in) {
    // cannot open the file
	} else {
		in.seekg(0, ifstream::end);
		kSize_ = static_cast<int>(in.tellg());
		in.seekg(0, ifstream::beg);
		kData_ = new char[kSize_];
		in.read(kData_, kSize_);
	}
}
File::~File() {
  delete[] kData_;
  kData_ = nullptr;
}
unsigned File::GetUnsigned(const int p) const {
  const unsigned char* up;
  up = reinterpret_cast<const unsigned char*>(kData_);
  unsigned ret = up[p];
  ret |= (up[p + 1] << 8 );
  ret |= (up[p + 2] << 16);
  ret |= (up[p + 3] << 24);
  return ret;
}