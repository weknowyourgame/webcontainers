#include <vector>
#include <string>

class File {
public:
  std::string name;
  std::string extension;
};

class Directory {
public:
  std::vector<Directory*> subfolders;
  std::vector<File*> files;

  Directory(const std::string& dir) : name(dir) {}
};

