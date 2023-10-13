// #include "FR_DICT.h"
#include "preprocess_xml.hpp"

#include <chrono>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  class Preprocess p;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  if (argc < 2) {
    string user_input;
    cout << "Default run, 300 entries \n";
    unsigned int n = 300;
    if (p.not_first_run()) {
      std::cout << "Loading previous "<< n << " entries" << std::endl;
    } else {
      start = std::chrono::system_clock::now();
      p.filter_xml_data(n);
      end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = end - start;
      cout << "Seconds to load dictionary: " << elapsed_seconds.count() << endl;
    }

    // O(N·log(N)) comparisons, where N is std::distance(first, last)
    // in other words N = dictionary.size()
    /*
    start = std::chrono::system_clock::now();
    fr_dict::sort_dictionary(dictionary);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to sort dictionary: " << elapsed_seconds.count() << endl;

    start = std::chrono::system_clock::now();
    fr_dict::dump_words_txt(dictionary, fr_dict::generated_words);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to save dictionary: " << elapsed_seconds.count() << endl;
    cout << "Input a word to look for: " << endl;
    cin >> user_input;
    // O(n) + O(n)
    // looks for word in the vector and uses its index to linearly
    // go through the definitions
    start = std::chrono::system_clock::now();
    cout << fr_dict::search_definition_of(dictionary, user_input) << endl;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to search definition: " << elapsed_seconds.count() << endl;
    fr_dict::dict_file.close();
    return 0;
  } else if (argc >= 2) {
    cout << "You chose to process: " << argv[1] << " definitions" << endl;
    cout << "Looking for the word: " << argv[2] << endl;
    string n = argv[1];
    string user_input = argv[2];
    vector<fr_dict::Word> dictionary = fr_dict::filter_xml_data(stoi(n));
    // O(N·log(N)) comparisons, where N is std::distance(first, last)
    // in other words N = dictionary.size()
    fr_dict::sort_dictionary(dictionary);
    fr_dict::dump_words_txt(dictionary, fr_dict::generated_words);
    cout << fr_dict::search_definition_of(dictionary, user_input) << endl;
    fr_dict::dict_file.close();
    return 0;
  }
    */
    return 0;
  }
}