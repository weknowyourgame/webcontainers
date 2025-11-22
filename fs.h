#pragma once
#include <vector>
#include <string>
#include <memory>

struct File {
  std::string name;
  std::vector<char> data;
};

struct Directory {
  std::string name;
  std::vector<std::unique_ptr<Directory>> dirs;
  std::vector<std::unique_ptr<File>> files;
};

class VirtualFS {
  std::unique_ptr<Directory> root;
public:
  VirtualFS();
  bool touch(const std::string& path);
  bool mv(const std::string& src, const std::string& dst);
  std::vector<std::string> ls(const std::string& path);
  bool mkdir(const std::string& path);
  std::string echo(const std::string& text);
};