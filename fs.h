#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

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

  Directory* navigateDirHelper(Directory* node, const std::string& dirName) {
    if(node == nullptr) return nullptr;
    if(node->name == dirName) return node;
    
    for(auto& d : node->dirs) {
      Directory* found = navigateDirHelper(d.get(), dirName);
      if(found != nullptr) return found;
    }
    return nullptr;
}

public:
  bool touch(const std::string& path, const std::vector<std::string> fileNames);
  bool mv(const std::string& src, const std::string& dst);
  std::vector<std::string> ls(const std::string& path);
  bool mkdir(const std::string& path);
  std::string echo(const std::string& text);
  
  Directory* navigateChild(const std::string& path) {
    size_t pos = path.rfind('/');
    std::string dirName = (pos == std::string::npos) ? "" : path.substr(0, pos);
    return navigateDirHelper(root.get(), dirName);
  }
  
  Directory* navigateParent(const std::string& path) {
    size_t pos = path.rfind('/');
    std::string parentPath = path.substr(0, pos);
    if(parentPath.empty()) return root.get();
    return navigateDirHelper(root.get(), parentPath);
  }
  
  VirtualFS() : root(initRoot()) {}
};