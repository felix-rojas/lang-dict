#ifndef FR_DICT_H_
#define FR_DICT_H_

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
  HashTable hash_dictionary;

public:
  /**
   * @brief Construct a new fr_dict object and allocate space in heap to store
   * the words
   *
   * @param number_of_entries
   */
  fr_dict(unsigned int number_of_entries) {
    number_of_words = number_of_entries;
    hash_dictionary = HashTable(number_of_entries);
  }
  /**
   * @brief Destroy the fr dict object
   *
   */
  ~fr_dict() { number_of_words = 0; }
  /** @defgroup functions_group All functions
   *  This is the functions group with its asymptotic analysis
   *  @{
   */

  /**
   * @brief Performs search to find the target word in Complexity
   * \f$O(N)\f$ because it needs to hash the target string first, where N is the
   * size of the string.
   *
   * @param target Word to look for
   * @return int Index of the target word
   * @see HashTable::search();
   */
  int find_word(const std::string &target) {
    return hash_dictionary.search(target);
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
    if (desired_row_number == -1)
      return "Definition not found";
    else {
      ifstream file(prep.generated_dictionary); // Open the file
      if (!file.is_open()) {
        return "Could not open the file.";
      }
      string line;
      int current_row_number = 0;
      while (getline(file, line) && current_row_number != desired_row_number) {
        current_row_number++;
      }
      file.close(); // Close the file
      return line;
    }
  }
  /**
   * @brief Looks for french available locales C++ of user
   *
   * @return true if it has a french locale, false if not
   */
  bool has_french_locale() {
    std::locale l("");
    std::string user_locale = l.name();
    return user_locale.find("fr");
  }

  /**
   * @brief Loads the words into the hash_dictionary in \f$O(N)\f$ time since it
   * goes line by line.
   *
   */
  void load_dictionary() {
    std::ifstream file(prep.generated_words); // Open the file
    if (!file.is_open()) {
      std::cerr << "Could not open the file." << std::endl;
    }
    std::string line;
    while (std::getline(file, line)) {
      long pos = line.find(' ');
      std::string word = line.substr(pos + 1);
      std::string line_placement = line.substr(0, pos);
      hash_dictionary.insert(word, std::stoi(line_placement));
    }
  }

  /**
   * @brief Prints the hash dictionary in \f$O(N)\f$
   * @see HashTable::print_hash_table();
   */
  void print_dictionary() { hash_dictionary.print_hash_table(); }

  /**
   * @brief Prints the hash dictionary in \f$O(N^2))\f$ time.
   * Checks for user locale to print sorting warning.
   * @see HashTable::.print_sorted_words();
   */
  void print_dictionary_sorted() {
    std::locale l("");
    std::string user_locale = l.name();
    if (!has_french_locale()) {
      cout << "Current environment doesn't have a french locale." << std::endl;
      cout << "Words will be sorted according to locale: " << user_locale
           << std::endl;
      hash_dictionary.print_sorted_words(user_locale);
    } else {
      hash_dictionary.print_sorted_words(user_locale);
    }
  }

  /**
   * @brief Checks if it is the first run. \f$O(1)\f$
   *
   * @return true if it is the first run
   * @return false if it isnt the first run
   * @see Preprocess::not_first_run();
   */
  bool first_run() { return prep.not_first_run(); }

  /**
   * @brief Filters the selecteed amount of entries in the xml file.
   * \f$O(N^2)\f$.
   *
   * @param entries words to be processed
   * @see Preprocess::filter_xml_data();
   */
  void process_xml(unsigned int entries) { prep.filter_xml_data(entries); }

  /** @} */ // end of functions_group
};          // class fr_dict

#endif // FR_DICT_H_
