#include "fs.h"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

bool VirtualFS::touch(const std::string& path, const std::vector<std::string> fileNames){
  // access the dir
  Directory* currDir = VirtualFS::navigateChild(path);
  if(currDir == nullptr) return false;

  for(const auto& f : fileNames){
    currDir->files.push_back(std::make_unique<File>(f));
  }

  return true;
}

// only supports dirs for now
bool VirtualFS::mv(const std::string& src, const std::string& dst){
  // get the srcP and destination Dir
    Directory* srcParent = navigateParent(src);
    Directory* dstDir = navigateChild(dst);

    if(srcParent == nullptr || dstDir == nullptr) return false;

    // get the name of dir to move
    size_t pos = src.rfind('/');
    std::string srcDirName = src.substr(pos + 1);
    
    // find and move from srcP to dstDir
    for(auto it = srcParent->dirs.begin(); it != srcParent->dirs.end(); ++it) {
        if((*it)->name == srcDirName) {
            dstDir->dirs.push_back(std::move(*it));
            srcParent->dirs.erase(it);
            return true;
        }
    }
    return false;
}


std::vector<std::string> VirtualFS::ls(const std::string& path){
  std::vector<std::string> files;
  // get the curr Dir
  Directory* curr = navigateToPath(path);
  if(curr == nullptr) return files;

  // add dirs
  for(const auto& dir : curr->dirs) {
    files.push_back(dir->name + "/");
  }
  
  // add files
  for(const auto& file : curr->files) {
    files.push_back(file->name);
  }
  return files;
}

// navigating child doesnt make sense
bool VirtualFS::mkdir(const std::string& path){
  // get the currDir
  Directory* parentDir = navigateParent(path);
  if(parentDir == nullptr) return false;
  
  // get the dirName
  size_t pos = path.rfind('/');
  std::string dirName = path.substr(pos + 1);
  
  parentDir->dirs.push_back(std::make_unique<Directory>(dirName));
  return true;
}

std::string VirtualFS::echo(const std::string& text){
  return text;
}
