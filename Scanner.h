
// Scanner.h
#pragma once

#include "FileMap.h"
#include "Token.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

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
  unordered_map<string, TokenKind> reservedWords = {
      {"if", TokenKind::IF},         {"else", TokenKind::ELSE},
      {"for", TokenKind::FOR},       {"return", TokenKind::RETURN},
      {"number", TokenKind::NUMBER}, {"string", TokenKind::STRING},
      {"def", TokenKind::DEF},       {"void", TokenKind::VOID},
      {"break", TokenKind::BREAK},   {"continue", TokenKind::CONTINUE},
      {"const", TokenKind::CONST},

  };

  bool atEnd() { return current >= source_code.length(); }

  char advance() { return source_code[current++]; }

  void addToken(TokenKind token) {}

  bool lookOneAhead(char match) {
    if (source_code[current + 1] == match) {
      return true;
    } else {
      return false;
    }
  }

  bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
  }

  // Checks if a character is an alphabet letter, underscore, or digit
  bool isAlphaNumeric(char c) {
    return isAlpha(c) || isdigit(static_cast<unsigned char>(c));
  }

  void stringLiteral() {
    advance();
    start = current;
    while (source_code[current] != '"' && !atEnd()) {
      advance();
    }
    // NOTE: Now start is at the begening " and current is at the end "
    string val = source_code.substr(start, current - 1);

    Tokens.push_back(StringLiteralToken(start, current - 1, TokenKind::STRING));
  }

  void numberLiteral() {
    start = current;
    while (isdigit(static_cast<unsigned char>(source_code[current])) ||
           source_code[current] == '.' && !atEnd()) {
      advance();
    }

    string val = source_code.substr(start, current - 1);

    Tokens.push_back(NumberLiteralToken(start, current - 1, TokenKind::NUMBER));
  }

  void identifier() {
    start = current;
    while (isAlpha(source_code[current]) && !atEnd()) {
      advance();
    }

    if (reservedWords.find(source_code.substr(start, current - 1)) !=
        reservedWords.end()) {
      Tokens.push_back(
          KeywordToken(start, current - 1,
                       reservedWords[source_code.substr(start, current - 1)]));
    } else {
      Tokens.push_back(
          IdentifierToken(start, current - 1, TokenKind::IDENTIFIER));
    }
  }

  void scanToken() {
    char c = advance();
    switch (c) {
    case '(':
      Tokens.push_back(
          SpecialSymbolToken(current, current, TokenKind::LEFT_PAREN));
      break;
    case ')':
      Tokens.push_back(
          SpecialSymbolToken(current, current, TokenKind::RIGHT_PAREN));
      break;
    case '{':
      Tokens.push_back(
          SpecialSymbolToken(current, current, TokenKind::LEFT_BRACE));
      break;
    case '}':
      Tokens.push_back(
          SpecialSymbolToken(current, current, TokenKind::RIGHT_BRACE));
      break;
    case ',':
      Tokens.push_back(SpecialSymbolToken(current, current, TokenKind::COMMA));
      break;
    case ';':
      Tokens.push_back(
          SpecialSymbolToken(current, current, TokenKind::SEMICOLON));
      break;
    case '-':
      Tokens.push_back(OperatorToken(current, current, TokenKind::MINUS));
      break;
    case '+':
      Tokens.push_back(OperatorToken(current, current, TokenKind::PLUS));
      break;
    case '/':
      Tokens.push_back(OperatorToken(current, current, TokenKind::SLASH));
      break;
    case '*':
      Tokens.push_back(OperatorToken(current, current, TokenKind::STAR));
      break;
    case '<':
      Tokens.push_back(
          lookOneAhead('=')
              ? OperatorToken(current, current, TokenKind::LESS_EQUAL)
              : OperatorToken(current, current, TokenKind::LESS));
      break;
    case '>':
      Tokens.push_back(
          lookOneAhead('=')
              ? OperatorToken(current, current, TokenKind::GREATER_EQUAL)
              : OperatorToken(current, current, TokenKind::GREATER));
      break;
    case '=':
      Tokens.push_back(
          lookOneAhead('=')
              ? OperatorToken(current, current, TokenKind::EQUAL_EQUAL)
              : OperatorToken(current, current, TokenKind::EQUAL));
      break;
    case '!':
      Tokens.push_back(
          lookOneAhead('=')
              ? OperatorToken(current, current, TokenKind::BANG_EQUAL)
              : OperatorToken(current, current, TokenKind::BANG));
      break;
    case ' ':
      break;

    // NOTE: String Literals
    case '"':
      stringLiteral();
    default:

      // NOTE: Number Literals
      if (isdigit(static_cast<unsigned char>(c))) {
        numberLiteral();
      }

      // NOTE: Reserved words and identifiers
      if (isalpha(static_cast<unsigned char>(c))) {
        identifier();
      }
    }
  }
};
