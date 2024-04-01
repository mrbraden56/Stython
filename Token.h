#include <string>

#pragma once

using namespace ::std;

class Token {
public:
  Token(int *pos, int kindIn);
  virtual std::string toString();
  size_t pos() const;
  string kind() const; // Defines the type of token such as a BOOL, IDENTIFIER,
                       // INTLITERAL, etc
};

class KeywordToken : public Token {};

class IdentifierToken : public Token {};

class SpecialSymbolToken : public Token {};

class OperatorToken : public Token {};

class LiteralToken : public Token {};
