#pragma once
#include <vector>
#include "dir.cpp"

extern "C" {
  void _touch(int file_count, vector<File*> files);
  void _mv(File* old_file, File* new_file);
  void _ls();
  void _cd(File* old_dir, File* new_dir);
  void _echo(File* text);
}

