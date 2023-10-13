#ifndef FR_DICT_H
#define FR_DICT_H

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "word.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::regex;
using std::sregex_iterator;
using std::string;
using std::vector;

class fr_dict {

public:



  // Perform binary search
  // O log(n)
  inline int findWord(const std::vector<Word> &wordVector,
                      const std::string &target) {
    int left = 0;
    int right = wordVector.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (wordVector[mid].word == target) {
        return wordVector[mid].index; // Word found, return its index
      } else if (wordVector[mid].word < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return -1;
  }

  // O(n) gets the entire line until it finds the number of line
  inline string searchDefinition(int desiredRowNumber) {
    ifstream file(generated_dictionary); // Open the file
    if (!file.is_open()) {
      return "Could not open the file.";
    }
    string line;
    int currentRowNumber = 0;
    while (getline(file, line) && currentRowNumber != desiredRowNumber) {
      currentRowNumber++;
    }
    return line;
    file.close(); // Close the file

    if (currentRowNumber != desiredRowNumber) {
      return "Not found";
    }
    return "Not found";
  }

  // O(N)
  ifstream dict_file = loadFile(filepath);


  // IntroSort
  // O(N·log(N)) comparisons, where N is std::distance(first, last)
  // in other words N = dictionary.size()
  void sort_dictionary(vector<Word> &dictionary) { return; }

  // O(n)
  void dump_words_txt(const vector<Word> &dictionary,
                             string filename) {
    ofstream word_examples(filename);
    for (int i = 0; i < dictionary.size(); i++) {
      word_examples << dictionary[i].word << endl;
    }
  }

  // O(log(n) + n)
  string search_definition_of(const vector<Word> &dictionary,
                                     const string input) {
    int word_index = findWord(dictionary, input);
    return searchDefinition(word_index);
  }
}; // class fr_dict

#endif
