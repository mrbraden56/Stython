
// Scanner.h
#pragma once

#include "FileMap.h"
#include <iostream>

class Scanner {
public:
  Scanner(FileMap *file) {
    if (file) { // Always good to check for nullptr
      for (const char *p = file->Begin(); p != file->End(); ++p) {
        std::cout << *p;
      }
    }
  }

  ~Scanner() {}

private:
};
