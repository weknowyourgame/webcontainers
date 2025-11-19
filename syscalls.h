#pragma once

extern "C" {
  void _touch(int file_count, const char* file_names[]);
  void _mv(const char* old_file, const char* new_file);
  void _ls();
  void _cd(const char* old_dir, const char* new_dir);
  void _echo(const char* text);
}
