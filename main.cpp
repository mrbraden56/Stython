#include <iostream>
#include <string>

#include "FileMap.cpp"

int main() {
  const char *stython_program_path = "example_program.sy";
  FileMap file(stython_program_path);

  if (!file) {
    printf("Error: failed to open file\n");
    return 1;
  }

  /*   printf("Source: %.*s\n", file.Size(), file.Begin()); */
  /*   Scanner scanner(file.Begin(), file.End()); */
  for (const char *p = file.Begin(); p != file.End(); ++p) {
    std::cout << *p; // Print each character
  }

  return 0;
}
