#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::regex entry("<entry form=\"([^\"]*)\"");
std::regex entry_end("<\\/entry>");
// Define the regex pattern
std::regex pattern("<([^>]+)>(.*?)<\\/\\1>");

int main() {
  // Load xml file
  std::ifstream dict_file("./wiktionaryXfr2010.xml");
  if (!dict_file) {
    std::cerr << "File could not be loaded" << std::endl;
    std::cerr << "Error code: " << stderr << std::endl;
    return -1;
  }
  int i = 0;
  std::string line_data;
  while (getline(dict_file, line_data) && i < 400) {
    // get the word/phrase to process
    std::sregex_iterator iter(line_data.begin(), line_data.end(), pattern);
    // Create an iterator to find all matches in the input string
    std::sregex_iterator end;

    std::smatch match;
    if (std::regex_search(line_data, match, entry) && match.size() > 1) {
      std::cout << std::endl;
      std::cout << match[1] << ", ";
    }

    // Loop through the matches and extract the content between tags
    while (iter != end) {
      std::smatch match = *iter;
      std::cout << match[1] << ", " << match[2] << ", ";
      ++iter;
    }
    if (std::regex_search(line_data, match, entry_end))
      std::cout << std::endl;
    i++;
  }

  dict_file.close();
  return 0;
}
