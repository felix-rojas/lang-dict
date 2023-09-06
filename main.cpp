#include <fstream>
#include <iostream>
#include <string.h>

// TODO: avoid space contamination
using namespace std;

int main() {
  ifstream dict_file("./wiktionaryXfr2010.xml");
  if (!dict_file) {
    cerr << "File could not be loaded" << endl;
    cerr << "Error code: " << strerror(errno) << endl;
    return -1;
  }

  string line_data = "";
  while (getline(dict_file, line_data)) {
    cout << line_data << endl;
  }
  dict_file.close();
  return 0;
}
