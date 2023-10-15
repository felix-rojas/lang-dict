/**
 * @file word.hpp
 * @brief Header file for the Word class
 */

#ifndef WORD_H
#define WORD_H

#include <locale>
#include <string>
#include <vector>


class Word {
public:
  unsigned int index;
  std::string word;
  Word();
  Word(const unsigned int &, const std::string &);
  bool operator<(const Word &other);
  bool operator>(const Word &other);
};

#endif // WORD_H