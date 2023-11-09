/**
 * @file test.cpp
 * @brief Program file for testing
 */

#include "FR_DICT.h"
#include "preprocess_xml.hpp"

#include <filesystem>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <locale>
#include <vector>
#include <string>

using std::cout;
using std::endl;

const std::filesystem::path test_words = "../out/test_words.txt";

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  cout << "Default run, 300 entries \n";
  unsigned int n = 300;

  fr_dict p(n);

  if (!p.first_run()) {
    std::cout << "Loading previous " << n << " entries" << std::endl;
    start = std::chrono::system_clock::now();
    p.load_dictionary();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to store pre-existing dictionary: "
         << elapsed_seconds.count() << endl;
  } else {
    start = std::chrono::system_clock::now();
    p.process_xml(n);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to process the xml file: " << elapsed_seconds.count()
         << endl;

    start = std::chrono::system_clock::now();
    p.load_dictionary();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Seconds to store dictionary in heap: " << elapsed_seconds.count()
         << endl;
  }

std::ifstream file(test_words); 
    if (!file.is_open()) {
        std::cout << "Error opening the file." << std::endl;
        return 1;
    }

  cout << "-------------------------------------" << endl;
  cout << "------ Dictionary search test ----------" << endl;
  cout << "-------------------------------------" << endl;

std::string test_strings_input;
std::vector<string> test_strings;

while (std::getline(file, test_strings_input)) {
    test_strings.push_back(test_strings_input);
    test_strings_input = "";
}

file.close();

for(std::string s : test_strings) {
    cout << s << endl;
}

for(int i = 0; i < n; i++) {
  start = std::chrono::system_clock::now();
  std::string string_to_find = test_strings[i];
  int test = p.find_word(string_to_find);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  cout << "Found: " << string_to_find << " in line " << test << " in ";
  cout << elapsed_seconds.count() << " seconds" << endl;
}

  cout << "-------------------------------------" << endl;
  cout << endl;


  cout << "-------------------------------------" << endl;
  cout << "------ Printing dictionary ----------" << endl;
  cout << "-------------------------------------" << endl;
  p.print_dictionary();
  cout << "-------------------------------------" << endl;
  cout << endl;


  // } else if (argc >= 2) {
  //   cout << "You chose to process: " << argv[1] << " definitions" << endl;
  //   cout << "Looking for the word: " << argv[2] << endl;
  //   string n = argv[1];
  //   string user_input = argv[2];
  //   fr_dict p(stoi(n));
  //   p.load_dictionary();
  //   int res = stoi(p.find_word(user_input));
  //   cout << p.search_definition(res) << endl;
  //   return 0;
  return 0;
}
