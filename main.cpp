#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Scanner.h"

using namespace std;

int main() {
  const char *stython_program_path = "example_program.sy";
  // FileMap file(stython_program_path);
  //
  // if (!file) {
  //   printf("Error: failed to open file\n");
  //   return 1;
  // }

  std::ifstream file(stython_program_path);
  if (!file) {
    std::cerr << "Failed to open the file." << std::endl;
  }

  // Use a stringstream to read the file contents into a string
  stringstream buffer;
  buffer << file.rdbuf();
  // Convert the stringstream into a string
  string source_code = buffer.str();
  std::string *source_code_ptr = &source_code;
  Scanner scanner(source_code);

  return 0;
}
