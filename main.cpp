#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>

const std::regex entry("<entry[^>]* form=\"([^\"]+)\"");
const std::regex entry_end("<\\/entry>");
// Define the regex pattern
const std::regex pattern("<([^>]+)>(.*?)<\\/\\1>");

const std::string filepath = "./wiktionaryXfr2010.xml";

const std::string def = "gloss";
const std::string etym = "etym";
const std::string eg = "example";

std::ifstream loadFile(std::string filepath) {
  // Load xml file
  std::ifstream dict_file(filepath);
  if (!dict_file) {
    throw std::runtime_error("File could not be loaded or does not exist.");
  }
  return dict_file;
}

int main() {
  unsigned int n = 10000;
  std::cout << "How many entries would you like to process? " << std::endl;
  std::cin >> n;
  int choice = 1;

  std::cout << "Menu:" << std::endl;
  std::cout << "1. Word" << std::endl;
  std::cout << "2. Word and Definition" << std::endl;
  std::cout << "3. Word, Etymology and Definition" << std::endl;
  std::cout << "Enter your choice (1-3), any other choice exits: ";
  std::cin >> choice;
  if (choice >= 4 || choice <= 0) {
    std::cout << "Exiting..." << std::endl;
    exit(1);
  }
  int i = 0;
  std::string line_data;
  auto dict_file = loadFile(filepath);

  // no parameters
  // getline has linear time O(n)
  while (getline(dict_file, line_data) && i <= n) {
    // get the word/phrase to process
    std::sregex_iterator iter(line_data.begin(), line_data.end(), entry);
    std::sregex_iterator iter2(line_data.begin(), line_data.end(), pattern);
    // Create an iterator to find all matches in the input string
    // regex_search is a O(n) operation on each processed line_data
    // yes, this means O(n^2)
    // it processes the regex expression using Thompsons algorithm

    // print word
    for (auto it = iter; it != std::sregex_iterator(); ++it) {
      if (i != n) {
        std::cout << std::endl;
        std::cout << it->str(1) << "\t";
      }
      i++;
    }

    switch (choice) {
    case 2:
      for (auto it2 = iter2;
           it2 != std::sregex_iterator() && it2->str(1) == def; ++it2) {
        std::cout << it2->str(2) << " ";
      }
      break;
    case 3:
      for (auto it2 = iter2; it2 != std::sregex_iterator() &&
                             ((it2->str(1) == def) || (it2->str(1) == etym));
           ++it2) {
        std::cout << it2->str(2) << " ";
      }
      break;
    }
  }
  dict_file.close();
  return 0;
}
