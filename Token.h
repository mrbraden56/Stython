#include "TokenKind.h"
#include <string>

#pragma once

using namespace ::std;

class Token {
public:
  Token(int start, int end, TokenKind kindIn)
      : start(start), end(end), kind(kindIn) {}
  // virtual ~Token() = default;

  int start; // Starting position of the token
  int end;   // Ending position of the token
  TokenKind kind;
};

class KeywordToken : public Token {
public:
  KeywordToken(int start, int end, TokenKind kindIn)
      : Token(start, end, kindIn) {}
};

class IdentifierToken : public Token {
public:
  IdentifierToken(int start, int end, TokenKind kindIn)
      : Token(start, end, kindIn) {}
};

class SpecialSymbolToken : public Token {
public:
  SpecialSymbolToken(int start, int end, TokenKind kindIn)
      : Token(start, end, kindIn) {}
};

class OperatorToken : public Token {
public:
  OperatorToken(int start, int end, TokenKind kindIn)
      : Token(start, end, kindIn) {}
};

class StringLiteralToken : public Token {
public:
  string value; // Member to store the string value

  StringLiteralToken(int start, int end, TokenKind kindIn)
      : Token(start, end, kindIn) {}
};

class NumberLiteralToken : public Token {
public:
  string value; // Member to store the string value

  NumberLiteralToken(int start, int end, TokenKind kindIn)
      : Token(start, end, kindIn) {}
};
