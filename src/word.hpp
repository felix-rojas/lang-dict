/**
 * @file word.hpp
 * @brief Header file for the Word class
 */

#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
public:
  int index;
  std::string word;
  std::string definition;
  Word(const std::string &w, const int &i);
  bool operator<(const Word &other);
  bool compareWord(const Word &a, const Word &b);
  void addDefinition(const std::string &w);
  friend class fr_dict;
};

#endif // WORD_H