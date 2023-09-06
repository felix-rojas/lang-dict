#include <fstream>
#include <iostream>
#include <string>

// TODO: avoid space contamination
using namespace std;

string entry("<entry form=");
string pageid("pageid");
string lexemepos("<lexeme pos=");
string definition_begin("<gloss>");
string definition_end("</gloss>");

int main() {
  // Load xml file
  ifstream dict_file("./wiktionaryXfr2010.xml");
  if (!dict_file) {
    cerr << "File could not be loaded" << endl;
    cerr << "Error code: " << stderr << endl;
    return -1;
  }

  // store string temporarily
  string line_data = "";
  while (getline(dict_file, line_data)) {
    // get the word/phrase to process
    size_t found = line_data.find(entry);
    if (found != string::npos) {
      cout << endl;
      size_t pos = line_data.find(pageid, found);
      cout << line_data.substr(found + entry.size(),
                               pos - (1 + (pageid.size() * 2)))
           << ", ";
    }

    // TODO: words can have multiple dfinitions and word types
    /*
    size_t lex_pos = line_data.find(lexemepos);
    if (lex_pos != string::npos) {
      cout << line_data.substr(lex_pos + lexemepos.size() + 1, lex_pos) << endl;
    }
    */
    size_t find_def_begin = line_data.find(definition_begin);
    size_t find_def_end = line_data.find(definition_end);
    if (find_def_begin != string::npos) {
      cout << "\"";
      cout << line_data.substr(find_def_begin + definition_begin.size(),
                               find_def_end - (3 + definition_end.size()));
      cout << "\", ";
    }
  }
  dict_file.close();
  return 0;
}
