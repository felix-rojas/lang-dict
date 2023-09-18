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
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::regex;
using std::sregex_iterator;
using std::string;
using std::vector;

namespace fr_dict {

const regex entry("<entry[^>]* form=\"([^\"]+)\"");
const regex entry_end("<\\/entry>");
// Define the regex pattern
const regex pattern("<([^>]+)>(.*?)<\\/\\1>");

const string filepath = "./wiktionaryXfr2010.xml";

const string def = "gloss";
const string etym = "etym";
const string eg = "example";

const string generated_dictionary = "dict.tsv";
const string generated_words = "words.txt";


inline ifstream loadFile(const string &filepath) {
  // Load xml file
  ifstream dict_file(filepath);
  if (!dict_file) {
    throw std::runtime_error("File could not be loaded or does not exist.");
  }
  return dict_file;
}

struct Word {
  int index;
  string word;
  Word(const string &w, const int &i) {
    this->word = w;
    this->index = i;
  }
  bool operator<(const Word &other) const { return this->word < other.word; }
};

// bug: std library compares using ascii values
// diacritic words have a higher ascii value
inline bool compareWord(const Word &a, const Word &b) { return a.word < b.word; }


// Perform binary search
// O log(n) 
inline int findWord(const std::vector<Word> &wordVector, const std::string &target) {
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
inline ifstream dict_file = loadFile(filepath);
// O(N)
inline ofstream file(generated_dictionary);

// O(n²)
inline vector<Word> filter_xml_data(int n = 100) {
  int i = 0;
  vector<Word> dictionary;
  string line_data;
  string temp;
  ifstream dict_file = loadFile(filepath);
  ofstream file(generated_dictionary);

  while (getline(dict_file, line_data) && i < n) {
    sregex_iterator iter(line_data.begin(), line_data.end(), entry);
    sregex_iterator iter2(line_data.begin(), line_data.end(), pattern);

    for (auto it2 = iter2; it2 != sregex_iterator() && ((it2->str(1) == def));
         ++it2) {
      file << it2->str(2) << " ";
    }
    // save to dictionary in dynamic memory
    for (auto it = iter; it != sregex_iterator(); ++it) {
      if (i <= n) {
        if (i != 0)
          file << endl;
        temp = it->str(1);
        // another o(n)
        for (int chars = 0; chars < temp.length(); chars++)
          temp[chars] = tolower(temp[chars]);
        dictionary.push_back(Word(temp, i));
        i++;
      }
    }
  }
  return dictionary;
}

// IntroSort
// O(N·log(N)) comparisons, where N is std::distance(first, last)
// in other words N = dictionary.size()
inline void sort_dictionary(vector<Word> &dictionary) {
  sort(dictionary.begin(), dictionary.end(), compareWord);
}

// O(n)
inline void dump_words_txt(const vector<Word> &dictionary,
                    string filename = generated_words) {
  ofstream word_examples(filename);
  for (int i = 0; i < dictionary.size(); i++) {
    word_examples << dictionary[i].word << endl;
  }
}

// O(log(n) + n)
inline string search_definition_of(const vector<Word> &dictionary,
                            const string input) {
  int word_index = findWord(dictionary, input);
  return searchDefinition(word_index);
}
}

#endif