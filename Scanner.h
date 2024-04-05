
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
    for (Token &token : Tokens) {

      // token.printToken();
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

  char advance() {
    char c = source_code[current];
    current++;
    return c;
  }

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
    string val = source_code.substr(start, current);

    Tokens.push_back(StringLiteralToken(
        TokenKind::STRING, source_code.substr(start, (current)-start + 1)));
  }

  void numberLiteral() {
    start = current;
    while (isdigit(static_cast<unsigned char>(source_code[current])) ||
           source_code[current] == '.' && !atEnd()) {
      advance();
    }

    string val = source_code.substr(start, current);

    Tokens.push_back(NumberLiteralToken(
        TokenKind::NUMBER, source_code.substr(start, (current)-start + 1)));
  }

  void identifier() {
    start = current;
    while (isAlpha(source_code[current]) && !atEnd()) {
      advance();
    }

    if (reservedWords.find(source_code.substr(start, current)) !=
        reservedWords.end()) {
      Tokens.push_back(
          KeywordToken(reservedWords[source_code.substr(start, current)],
                       source_code.substr(start, (current)-start + 1)));
    } else {
      Tokens.push_back(
          IdentifierToken(TokenKind::IDENTIFIER,
                          source_code.substr(start, (current)-start + 1)));
    }
  }

  void scanToken() {
    char c = advance();
    switch (c) {
    case '(':
      Tokens.push_back(SpecialSymbolToken(TokenKind::LEFT_PAREN,
                                          source_code.substr(current, 1)));
      break;
    case ')':
      Tokens.push_back(SpecialSymbolToken(TokenKind::RIGHT_PAREN,
                                          source_code.substr(current, 1)));
      break;
    case '{':
      Tokens.push_back(SpecialSymbolToken(TokenKind::LEFT_BRACE,
                                          source_code.substr(current, 1)));
      break;
    case '}':
      Tokens.push_back(SpecialSymbolToken(TokenKind::RIGHT_BRACE,
                                          source_code.substr(current, 1)));
      break;
    case ',':
      Tokens.push_back(
          SpecialSymbolToken(TokenKind::COMMA, source_code.substr(current, 1)));
      break;
    case ';':
      Tokens.push_back(SpecialSymbolToken(TokenKind::SEMICOLON,
                                          source_code.substr(current, 1)));
      break;
    case '-':
      cout << c << "\n";
      Tokens.push_back(
          lookOneAhead('>')
              ? OperatorToken(TokenKind::RETURN_SYMBOL,
                              source_code.substr(start, (current)-start + 1))
              : OperatorToken(TokenKind::MINUS,
                              source_code.substr(current, 1)));
      break;
    case '+':
      Tokens.push_back(
          OperatorToken(TokenKind::PLUS, source_code.substr(current, 1)));
      break;
    case '/':
      Tokens.push_back(
          OperatorToken(TokenKind::SLASH, source_code.substr(current, 1)));
      break;
    case '*':
      Tokens.push_back(
          OperatorToken(TokenKind::STAR, source_code.substr(current, 1)));
      break;
    case '<':
      Tokens.push_back(
          lookOneAhead('=')
              ? OperatorToken(TokenKind::LESS_EQUAL,
                              source_code.substr(current, 1))
              : OperatorToken(TokenKind::LESS, source_code.substr(current, 1)));
      break;
    case '>':
      Tokens.push_back(lookOneAhead('=')
                           ? OperatorToken(TokenKind::GREATER_EQUAL,
                                           source_code.substr(current, 1))
                           : OperatorToken(TokenKind::GREATER,
                                           source_code.substr(current, 1)));
      break;
    case '=':
      Tokens.push_back(lookOneAhead('=')
                           ? OperatorToken(TokenKind::EQUAL_EQUAL,
                                           source_code.substr(current, 1))
                           : OperatorToken(TokenKind::EQUAL,
                                           source_code.substr(current, 1)));
      break;
    case '!':
      Tokens.push_back(
          lookOneAhead('=')
              ? OperatorToken(TokenKind::BANG_EQUAL,
                              source_code.substr(current, 1))
              : OperatorToken(TokenKind::BANG, source_code.substr(current, 1)));
      break;
    case ' ':
      // Handling for space character, presumably skipping it.
      break;

    // NOTE: String Literals
    case '"':
      stringLiteral(); // Implementation presumably handles literals
      break;
    default:
      // NOTE: Number Literals
      if (isdigit(static_cast<unsigned char>(c))) {
        numberLiteral(); // Implementation presumably handles number literals
      }

      // NOTE: Reserved words and identifiers
      if (isalpha(static_cast<unsigned char>(c))) {
        identifier(); // Implementation presumably handles identifiers
      }
    }
  }
};
