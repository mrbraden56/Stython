#include <iostream>
#include <string>

#include "FileMap.h"
#include "Scanner.h"

int main() {
  const char *stython_program_path = "example_program.sy";
  FileMap file(stython_program_path);

  if (!file) {
    printf("Error: failed to open file\n");
    return 1;
  }

  // std::cout << *(file.Begin() + 1) << "\n";
  Scanner scanner(&file);

  return 0;
}
