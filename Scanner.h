
// Scanner.h
#pragma once

#include "FileMap.h"
#include "Token.h"
#include <iostream>
#include <vector>

using namespace std;

struct TokenType {
  Token LEFT_PARENTH;
};

class Scanner {

public:
  Scanner(const std::string &fileContent) : source_code(fileContent) {}

  void generateTokens() {
    while (!atEnd()) {
      scanToken();
    }
  }

  ~Scanner() {}

private:
  std::vector<Token> Tokens;

  string source_code;
  int start = 0;   // Used to track start of the token
  int current = 0; // Used to track where we currently are
  int line = 0;

  bool atEnd() { return current >= source_code.length(); }

  char advance() { return source_code[current++]; }

  /* addToken(TokenType token) {} */

  void scanToken() {
    char c = advance();
    switch (c) {
    case '(':
      /* addToken(); */
    }
  }
};
