/**
 * @file main.cpp
 * @brief Entry program file that takes arguments
 */

#include "FR_DICT.h"
#include "preprocess_xml.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <locale>

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
  if (argc <= 2) {
    cout << "Default run, 300 entries \n";
    cout << "Looking for the word: " << argv[1] << endl;
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

    start = std::chrono::system_clock::now();
    std::string target = argv[1];
    int test = p.find_word(target);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    if (test != -1) {
      cout << p.search_definition(test) << endl;
      cout << "Found: " << target << " in line " << test << " in ";
      cout << elapsed_seconds.count() << "seconds" << endl;

      start = std::chrono::system_clock::now();
      cout << p.search_definition(test) << endl;
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      cout << "Seconds to search definition: " << elapsed_seconds.count()
           << endl;
    } else {
      cout << "Target word not found." << endl;
    }

    start = std::chrono::system_clock::now();
    p.print_dictionary_sorted();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to sort and print dictionary: " << elapsed_seconds.count()
         << endl;

    return 0;

  } else if (argc > 2) {
    cout << "You chose to process: " << argv[1] << " definitions" << endl;
    cout << "Looking for the word: " << argv[2] << endl;
    string n = argv[1];
    string user_input = argv[2];
    fr_dict p(stoi(n));
    p.process_xml(stoi(n));
    p.load_dictionary();
    if (p.find_word(user_input) != -1) {
      cout << p.search_definition(p.find_word(user_input)) << endl;
    }
    cout << "Target word not found." << endl;

    cout << "Printing alphabetically sorted dictionary: " << endl;
    p.print_dictionary_sorted();
    return 0;
  } 
return 0;
}
