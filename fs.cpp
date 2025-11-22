#include <vector>
#include <string>
#include <map>

static std::map<std::string, std::vector<char>> disk;

class File {
public:
  std::string name;
  std::string extension;
  std::string path;
  std::vector<char> data;
};

class Directory {
public:
  std::vector<Directory*> subfolders;
  std::vector<File*> files;
  std::string path;

  Directory(const std::string& dir) : name(dir) {}
};

class VirtualFS {
public:

  bool _touch(int file_count, vector<File*> files){

  }
  
  bool _mv(File* old_file, File* new_file){

  }
  
  std::vector<std::string> _ls(){

  }

  bool _cd(File* old_dir, File* new_dir){

  }

  std::string _echo(File* text){

  }

  bool _mkdir(Directory* dir_name){

  }
};

