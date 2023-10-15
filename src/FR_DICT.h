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

#include "preprocess_xml.hpp"
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

private:
  Preprocess prep;
  unsigned int number_of_words;
  std::vector<Word> dictionary;

public:
  /**
   * @brief Construct a new fr_dict object and allocate space in heap to store
   * the words
   *
   * @param number_of_entries
   */
  fr_dict(unsigned int number_of_entries) {
    std::vector<Word> dictionary;
    dictionary.reserve(number_of_entries);
    number_of_words = number_of_entries;
  }
  /**
   * @brief Performs binary search to find the target word in Complexity
   * \f$O(log(N))\f$ .
   *
   * @param word_vector Vector container with all the words
   * @param target Word to look for
   * @return int Index of the target word
   */
  int find_word(const std::vector<Word> &word_vector,
                const std::string &target) {
    int left = 0;
    int right = word_vector.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (word_vector[mid].word == target) {
        return word_vector[mid].index; // Word found, return its index
      } else if (word_vector[mid].word < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return -1;
  }

  
  /**
   * @brief Looks for the stored definition of the word in the dictionary.
    It has complexity \f$O(N)\f$ as it gets the entire line until it finds the number of line.
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
    ifstream file(prep.generated_words); // Open the file
    if (!file.is_open()) {
      throw "Could not open the file.";
    }
    std::string line;
    while (std::getline(file, line)) {
      unsigned int pos = line.find(' ');
      unsigned int index = stoi(line.substr(0, pos));
      std::string word = line.substr(pos);
      Word *fr_word = new Word(index, word);
      dictionary.push_back(*fr_word);
    }
  }

/**
 * @brief Auxiliary method for quick_sort 
 */
int partition(std::vector<Word> &vec, int low, int high){
    int i = low, j = high;
    Word mid = vec[(low + high) / 2];

    while (i <= j) {
        while (vec[i] < mid)
            i++;
        while (vec[j] > mid)
            j--;
        if (i <= j) {
            std::swap(vec[i], vec[j]);
            i++; j--;
        }
    }
    return i;
}

/**
 * @brief Modified quicksort to sort the container with the words
 * 
 * @param vec Dictionary to sort
 * @param low Lower point
 * @param high High point
 */
void quick_sort(std::vector<Word> &vec, int low, int high){
    if (low < high) {
        int pivot = partition(vec, low, high);
        quick_sort(vec, low, pivot-1);
        quick_sort(vec, pivot+1, high);
    }
}

/**
 * @brief Sorts the dictionary using quicksort. Average \f$O(N \times log(N))\f$ and Worst \f$O(N^2)\f$. 
 * 
 */
void sort_dictionary(){
  quick_sort(dictionary, 0, dictionary.size()-1);
}

void print_dictionary() {
  for (auto i : dictionary) {
    cout << i.word << endl;
  }
}
// O(log(n) + n)
string search_definition_of(const vector<Word> &dictionary,
                            const string input) {
  int word_index = find_word(dictionary, input);
  return search_definition(word_index);
}

bool first_run() { return prep.not_first_run(); }

void process_xml(unsigned int entries) { prep.filter_xml_data(entries); }
}
; // class fr_dict

#endif
