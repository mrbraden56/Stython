
// Scanner.h
#pragma once

#include "FileMap.h"
#include "Flex.h"
#include <iostream>

class Scanner {
  Flex *flex;

public:
  Scanner(FileMap *file) {
    for (const char *p = file->Begin(); p != file->End(); ++p) {
      flex->accept(p);
    }
  }

  ~Scanner() {}

private:
};
