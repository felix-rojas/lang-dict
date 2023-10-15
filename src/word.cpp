/**
 * @file word.cpp
 * @brief Implementation of functions for the Word class in word.hpp
 */

#include "word.hpp"
// bug: std library compares using ascii values
// diacritic words have a higher ascii value
#include <algorithm>
#include <iterator>
#include <locale>
#include <string>

Word::Word() {
  this->index = 0;
  this->word = "";
}

Word::Word(const unsigned int &index, const std::string &word) {
  this->index = index;
  this->word = word;
}

bool Word::operator<(const Word &other) {

  const std::collate<char> &col =
      std::use_facet<std::collate<char>>(std::locale()); 
  const char *pb1 = this->word.data();
  const char *pb2 = other.word.data();

  return (col.compare(pb1, pb1 + this->word.size(), pb2,
                      pb2 + other.word.size()) < 0);
}

bool Word::operator>(const Word &other) {

  const std::collate<char> &col =
      std::use_facet<std::collate<char>>(std::locale()); 
  const char *pb1 = this->word.data();
  const char *pb2 = other.word.data();

  return !(col.compare(pb1, pb1 + this->word.size(), pb2,
                      pb2 + other.word.size()) < 0);
}
