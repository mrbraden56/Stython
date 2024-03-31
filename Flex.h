#pragma once

#include <iostream>

class Flex {
public:
  Flex() {
    std::string keyword_if = "if";
    std::string keyword_else = "else";
    std::string keyword_for = "for";
    std::string keyword_return = "return";
    std::string keyword_int = "int";
    std::string keyword_string = "string";
    std::string keyword_char = "char";
    std::string keyword_def = "def";
    std::string keyword_void = "void";
    std::string keyword_break = "break";
    std::string keyword_continue = "continue";
    std::string keyword_const = "const";

    std::string identifiers =
        "^(?!for|else| … |continue)([a-zA-Z_][a-zA-Z0-9_]*)$";

    std::string special_symbols = "[;,@]|\\(\\)|\\{\\}";

    std::string operators = "\\+|-|\\/|\\*|==|!=|<=|>=|<|>|\\!";

    std::string literal_int = "\\b\\d+\\b";
    std::string literal_float = "\\b\\d+\\.\\d+([eE][+-]?\\d+)?\\b";
    std::string literal_boolean = "\\b(true|false)\\b";

    std::string white_space = "\\s+";
  }

  void accept(const char *p) {}

  ~Flex() {}

private:
};
