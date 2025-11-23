#pragma once
#include <vector>
#include <string>
#include <memory>

struct File {
  std::string name;
  std::vector<char> data;

  File(const std::string& n,
    const std::vector<char>& d = {}) 
    : name(n), data(d) {}
};

struct Directory {
  std::string name;
  std::vector<std::unique_ptr<Directory>> dirs;
  std::vector<std::unique_ptr<File>> files;

  Directory(const std::string& n,
    const std::vector<std::unique_ptr<Directory>> d = {},
    const std::vector<std::unique_ptr<File>> f = {}) 
    : name(n), dirs(std::move(d)), files(std::move(f)) {}
};

class VirtualFS {
  struct DirWithFiles {
    std::string name;
    std::vector<std::string> files;
  };
  
  std::unique_ptr<Directory> root;
  
  std::unique_ptr<Directory> initRoot(){
    auto rootDir = std::make_unique<Directory>("/");

    std::vector<DirWithFiles> initialDirs = {
      {"home", {"readme.txt"}},
      {"bin", {}},
      {"etc", {}},
      {"tmp", {}}
    };

    for(const auto& d : initialDirs){
      auto dir = std::make_unique<Directory>(d.name);
      for(const auto& f : d.files){
        dir->files.push_back(std::make_unique<File>(f));
      }
      rootDir->dirs.push_back(std::move(dir));
    }
    return rootDir;
  }

public:
  bool touch(const std::string& path);
  bool mv(const std::string& src, const std::string& dst);
  std::vector<std::string> ls(const std::string& path);
  bool mkdir(const std::string& path);
  std::string echo(const std::string& text);

  VirtualFS() : root(initRoot()) {}

};