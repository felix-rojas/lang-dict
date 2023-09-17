#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::regex;
using std::sregex_iterator;
using std::string;
using std::vector;

const regex entry("<entry[^>]* form=\"([^\"]+)\"");
const regex entry_end("<\\/entry>");
// Define the regex pattern
const regex pattern("<([^>]+)>(.*?)<\\/\\1>");

const string filepath = "./wiktionaryXfr2010.xml";

const string def = "gloss";
const string etym = "etym";
const string eg = "example";

ifstream loadFile(const string &filepath) {
  // Load xml file
  ifstream dict_file(filepath);
  if (!dict_file) {
    throw std::runtime_error("File could not be loaded or does not exist.");
  }
  return dict_file;
}


struct Word {
  int index;
  string word;
  Word(const string &w, const int &i) {
    this->word = w;
    this->index = i;
  }
  bool operator<(const Word &other) const {
        return this->word < other.word;
    }
};

bool compareWord(const Word &a, const Word &b) { return a.word < b.word; }

struct Definition {
  string definition;
  Definition(const string &w) { this->definition = w; }
};

// bug: std library compares using ascii values
// diacritic words have a higher ascii value

// Perform binary search
int findWord(const std::vector<Word> &wordVector, const std::string &target) {
    int left = 0;
    int right = wordVector.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (wordVector[mid].word == target) {
            return wordVector[mid].index; // Word found, return its index
        } else if (wordVector[mid].word < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

vector<Word> dictionary;

// O(n) gets the entire line until it finds the number of line
std::string searchDefinition(int desiredRowNumber) {
  std::ifstream file("dict.tsv"); // Open the file
  if (!file.is_open()) {
    return "Could not open the file.";
  }
  std::string line;
  int currentRowNumber = 0;
  while (std::getline(file, line) && currentRowNumber != desiredRowNumber) {
    currentRowNumber++;
  }
  return line;
  file.close(); // Close the file

  if (currentRowNumber != desiredRowNumber) {
    return "Not found";
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Default run, 100 entries \n";
    int n = 100;
    int i = 0;

    string line_data;
    string temp;
    auto dict_file = loadFile(filepath);
    ofstream file("dict.tsv");

    // no parameters
    // getline has linear time O(n)
    while (getline(dict_file, line_data) && i < n) {
      sregex_iterator iter(line_data.begin(), line_data.end(), entry);
      sregex_iterator iter2(line_data.begin(), line_data.end(), pattern);

      for (auto it2 = iter2; it2 != sregex_iterator() && ((it2->str(1) == def));
           ++it2) {
        file << it2->str(2) << " ";
      }
      // print word
      for (auto it = iter; it != sregex_iterator(); ++it) {
        if (i <= n) {
          if (i != 0)
            file << endl;
          temp = it->str(1);
          // another o(n)
          for (int chars = 0; chars < temp.length(); chars++)
            temp[chars] = tolower(temp[chars]);
          dictionary.push_back(Word(temp, i));
          i++;
        }
      }
    }

    // O(N·log(N)) comparisons, where N is std::distance(first, last)
    // in other words N = dictionary.size()
    sort(dictionary.begin(), dictionary.end(), compareWord);
    std::string input;
    cout << "Dictionary sorted. Type a word to search:" << endl;
    cin >> input;

    int word_index = findWord(dictionary, input);
    cout << searchDefinition(word_index) << endl;

    dict_file.close();

  } else if (argc >= 2) {
    int n = *argv[1];
    int i = 0;

    string line_data;
    string temp;
    auto dict_file = loadFile(filepath);
    ofstream file("dict.tsv");

    // no parameters
    // getline has linear time O(n)
    while (getline(dict_file, line_data) && i < n) {
      sregex_iterator iter(line_data.begin(), line_data.end(), entry);
      sregex_iterator iter2(line_data.begin(), line_data.end(), pattern);

      for (auto it2 = iter2; it2 != sregex_iterator() && ((it2->str(1) == def));
           ++it2) {
        file << it2->str(2) << " ";
      }
      // print word
      for (auto it = iter; it != sregex_iterator(); ++it) {
        if (i <= n) {
          if (i != 0)
            file << endl;
          temp = it->str(1);
          // another o(n)
          for (int chars = 0; chars < temp.length(); chars++)
            temp[chars] = tolower(temp[chars]);
          dictionary.push_back(Word(temp, i));
          i++;
        }
      }
    }

    sort(dictionary.begin(), dictionary.end(), compareWord);

    for (int i = 0; i < dictionary.size(); i++) {
      cout << dictionary[i].index << " " << dictionary[i].word << ": ";
      cout << searchDefinition(dictionary[i].index) << endl;
    }
    dict_file.close();
  }
  return 0;
}
