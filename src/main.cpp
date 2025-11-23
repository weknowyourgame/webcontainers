#include <emscripten/bind.h>
#include "fs.h"
#include <vector>
#include <string>

using namespace emscripten;

// Global VirtualFS instance
VirtualFS* g_fs = nullptr;

// Initialize the filesystem
void init_fs() {
  if (g_fs == nullptr) {
    g_fs = new VirtualFS();
  }
}

// Expose mkdir
bool wasm_mkdir(const std::string& path) {
  init_fs();
  return g_fs->mkdir(path);
}

// Expose touch - accepts vector of strings
bool wasm_touch(const std::string& path, const std::vector<std::string>& fileNames) {
  init_fs();
  return g_fs->touch(path, fileNames);
}

// Expose mv
bool wasm_mv(const std::string& src, const std::string& dst) {
  init_fs();
  return g_fs->mv(src, dst);
}

// Expose ls - returns vector
std::vector<std::string> wasm_ls(const std::string& path) {
  init_fs();
  return g_fs->ls(path);
}

// Expose echo
std::string wasm_echo(const std::string& text) {
  init_fs();
  return g_fs->echo(text);
}

EMSCRIPTEN_BINDINGS(filesystem) {
  function("mkdir", &wasm_mkdir);
  function("touch", &wasm_touch);
  function("mv", &wasm_mv);
  function("ls", &wasm_ls);
  function("echo", &wasm_echo);
  
  register_vector<std::string>("VectorString");
}
