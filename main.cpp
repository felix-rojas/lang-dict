#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

const std::regex entry("<entry form=\"([^\"]*)\"");
const std::regex entry_end("<\\/entry>");
// Define the regex pattern
const std::regex pattern("<([^>]+)>(.*?)<\\/\\1>");

const std::string filepath = "./wiktionaryXfr2010.xml";

std::ifstream loadFile(std::string filepath) {
  // Load xml file
  std::ifstream dict_file(filepath);
  if (!dict_file) {
    std::cerr << "File could not be loaded" << std::endl;
  }
  return dict_file;
}

int main() {
  int i = 0;
  std::string line_data;
  auto dict_file = loadFile(filepath);

  // getline has linear time O(n)
  while (getline(dict_file, line_data) && i < 400) {
    // get the word/phrase to process
    std::sregex_iterator iter(line_data.begin(), line_data.end(), pattern);
    // Create an iterator to find all matches in the input string
    std::sregex_iterator end;

    // generate a string match type to store results
    std::smatch match;
    // regex_search is a O(n) operation on each processed line
    // it processes the regex expression using Thompsons algorithm
    if (std::regex_search(line_data, match, entry) && match.size() > 1) {
      std::cout << match[1] << "\t";
    }

    // Loop through the matches and extract the content between tags
    while (iter != end) {
      std::smatch match = *iter;
      std::cout << match[1] << "\t" << match[2] << "\t";
      ++iter;
    }
    if (std::regex_search(line_data, match, entry_end)) {
      std::cout << std::endl;
      i++;
    }
  }

  dict_file.close();
  return 0;
}
