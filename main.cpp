#include "FR_DICT.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    string user_input;
    cout << "Default run, 100 entries \n";
    int n = 100;
    vector<fr_dict::Word> dictionary = fr_dict::filter_xml_data(n);
    // O(N·log(N)) comparisons, where N is std::distance(first, last)
    // in other words N = dictionary.size()
    fr_dict::sort_dictionary(dictionary);
    fr_dict::dump_words_txt(dictionary, fr_dict::generated_words);
    cout << "Input a word to look for: " << endl;
    cin >> user_input;
    cout << fr_dict::search_definition_of(dictionary, user_input) << endl;
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
  return 0;
}
