#ifndef FR_DICT_H
#define FR_DICT_H

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "hash_table.cpp"
#include "preprocess_xml.hpp"

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

private:
  Preprocess prep;
  unsigned int number_of_words;
  HashTable *hash_dictionary;

public:
  /**
   * @brief Construct a new fr_dict object and allocate space in heap to store
   * the words
   *
   * @param number_of_entries
   */
  fr_dict(unsigned int number_of_entries) {
    hash_dictionary = new HashTable();
    number_of_words = number_of_entries;
  }
  /**
   * @brief Performs binary search to find the target word in Complexity
   * \f$O(N)\f$ .
   *
   * @param target Word to look for
   * @return int Index of the target word
   */
  std::string find_word(const std::string &target) {
    return hash_dictionary->search(target);
  }

  /**
   * @brief Looks for the stored definition of the word in the dictionary.
    It has complexity \f$O(N)\f$ as it gets the entire line until it finds the
   number of line.
   *
   * @param desired_row_number
   * @return string "Not found" if there is no definition, "Could not open
   * file" if the file has been corrupted or the definition if it is found.
   */
  string search_definition(int desired_row_number) {
    ifstream file(prep.generated_dictionary); // Open the file
    if (!file.is_open()) {
      return "Could not open the file.";
    }
    string line;
    int current_row_number = 0;
    while (getline(file, line) && current_row_number != desired_row_number) {
      current_row_number++;
    }
    return line;
    file.close(); // Close the file

    if (current_row_number != desired_row_number) {
      return "Not found";
    }
    return "Not found";
  }

  void load_dictionary() {
    std::ifstream file(prep.generated_words); // Open the file
    if (!file.is_open()) {
      std::cerr << "Could not open the file." << std::endl;
    }
    std::string line;
    while (std::getline(file, line)) {
      int pos = line.find(' ');
      std::string word = line.substr(pos);
      Item *item = new Item(word);
      hash_dictionary->insert(item);
    }
  }

  void print_dictionary() { hash_dictionary->PrintHashTable(); }

  bool first_run() { return prep.not_first_run(); }

  void process_xml(unsigned int entries) { prep.filter_xml_data(entries); }
}; // class fr_dict

#endif
