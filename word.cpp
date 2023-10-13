#include "word.hpp"
// bug: std library compares using ascii values
// diacritic words have a higher ascii value

Word::Word(const std::string &w, const int &i) {
  this->word = w;
  this->index = i;
}

bool Word::operator<(const Word &other) { return this->word < other.word; }

bool Word::compareWord(const Word &a, const Word &b) { return a.word < b.word; }
