
#pragma once

class Token {
public:
  virtual ~Token() {}
};

class KeywordToken : public Token {};

class IdentifierToken : public Token {};

class SpecialSymbolToken : public Token {};

class OperatorToken : public Token {};

class LiteralToken : public Token {};
