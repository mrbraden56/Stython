#include <iostream>
#include <string>

#include "FileMap.cpp"
/* g++ main.cpp FileMap.cpp -o com */
int main() {
  const char *stython_program_path = "example_program.sy";
  FileMap file(stython_program_path);

  if (!file) {
    printf("Error: failed to open file\n");
    return 1;
  }

  /*   Scanner scanner(file.Begin(), file.End()); */
  for (const char *p = file.Begin(); p != file.End(); ++p) {
    std::cout << *p; // Print each character
  }

  return 0;
}
