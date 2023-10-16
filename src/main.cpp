/**
 * @file main.cpp
 * @brief Entry program file that takes arguments
 */

#include "FR_DICT.h"
#include "hash_table.cpp"
#include "preprocess_xml.hpp"
#include "word.cpp"
#include "word.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <locale>

using std::cin;
using std::cout;
using std::endl;

/**
 * @brief The main entry point for the program.
 *
 * This function is the entry point for the program. It can take command-line
 * arguments using argc and argv.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of C-style strings containing the command-line
 * arguments.
 * @return Exit status of the program (0 for success).
 */

int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  if (argc < 2) {
    cout << "Default run, 300 entries \n";
    unsigned int n = 300;
    fr_dict p(n);
    if (!p.first_run()) {
      std::cout << "Loading previous " << n << " entries" << std::endl;
    } else {
      start = std::chrono::system_clock::now();
      p.process_xml(n);
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      cout << "Seconds to process the xml file: " << elapsed_seconds.count()
           << endl;
    }
    start = std::chrono::system_clock::now();
    p.load_dictionary();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to store dictionary in heap: " << elapsed_seconds.count()
         << endl;
    p.print_dictionary();

    start = std::chrono::system_clock::now();
    std::string test = p.find_word("homme");
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Found: " << test << " in ";
    cout << elapsed_seconds.count() << "seconds" << endl;
    /*
    // O(N·log(N)) comparisons, where N is std::distance(first, last)
    // in other words N = dictionary.size()
    start = std::chrono::system_clock::now();
    p.sort_dictionary();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to sort dictionary: " << elapsed_seconds.count() << endl;

    p.print_dictionary();
        start = std::chrono::system_clock::now();
        fr_dict::dump_words_txt(dictionary, fr_dict::generated_words);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        cout << "Seconds to save dictionary: " << elapsed_seconds.count() <<
      endl; cout << "Input a word to look for: " << endl; cin >> user_input;
        // O(n) + O(n)
        // looks for word in the vector and uses its index to linearly
        // go through the definitions
        start = std::chrono::system_clock::now();
        cout << fr_dict::search_definition_of(dictionary, user_input) << endl;
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        cout << "Seconds to search definition: " << elapsed_seconds.count() <<
      endl; fr_dict::dict_file.close(); return 0; } else if (argc >= 2) { cout
      << "You chose to process: " << argv[1] << " definitions" << endl; cout <<
      "Looking for the word: " << argv[2] << endl; string n = argv[1]; string
      user_input = argv[2]; vector<fr_dict::Word> dictionary =
      fr_dict::filter_xml_data(stoi(n));
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