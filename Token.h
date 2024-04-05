
#include "TokenKind.h"
#include <iostream>
#include <string>

#pragma once

using namespace std;

class Token {
public:
  Token(TokenKind kindIn, string value) : kind(kindIn), value(value) {}
  virtual ~Token() = default;

  virtual void printToken() const { cout << value << "\n"; }

  TokenKind kind;
  string value;
};

class KeywordToken : public Token {
public:
  KeywordToken(TokenKind kindIn, string value) : Token(kindIn, value) {}

  void printToken() const override { cout << value << "\n"; }
};

class IdentifierToken : public Token {
public:
  IdentifierToken(TokenKind kindIn, string value) : Token(kindIn, value) {}

  void printToken() const override { cout << value << "\n"; }
};

class SpecialSymbolToken : public Token {
public:
  SpecialSymbolToken(TokenKind kindIn, string value) : Token(kindIn, value) {}

  void printToken() const override { cout << value << "\n"; }
};

class OperatorToken : public Token {
public:
  OperatorToken(TokenKind kindIn, string value) : Token(kindIn, value) {}

  void printToken() const override { cout << value << "\n"; }
};

class StringLiteralToken : public Token {
public:
  StringLiteralToken(TokenKind kindIn, string value) : Token(kindIn, value) {}

  void printToken() const override { cout << value << "\n"; }
};

class NumberLiteralToken : public Token {
public:
  NumberLiteralToken(TokenKind kindIn, string value) : Token(kindIn, value) {}

  void printToken() const override { cout << value << "\n"; }
};
