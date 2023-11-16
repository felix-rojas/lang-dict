#ifndef PREPROCESS_XML_HPP_
#define PREPROCESS_XML_HPP_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using std::regex;
using std::sregex_iterator;
using std::string;
using std::vector;

/**
 * @brief Class for preprocessing the XML data using optimized regex patterns
 *
 */
class Preprocess {
private:
  const std::regex entry = regex("<entry[^>]* form=\"([^\"]+)\"",
                                 std::regex::optimize | std::regex::icase);
  const std::regex entry_end =
      std::regex("<\\/entry>", std::regex::optimize | std::regex::icase);
  // Define the regex pattern
  const std::regex pattern = std::regex(
      "<([^>]+)>(.*?)<\\/\\1>", std::regex::optimize | std::regex::icase);

  const std::string def = "gloss";
  const std::string etym = "etym";
  const std::string eg = "example";

  friend class fr_dict;

  const std::filesystem::path filepath = "../res/wiktionaryXfr2010.xml";
  const std::filesystem::path generated_dictionary = "../out/dict.tsv";
  const std::filesystem::path generated_words = "../out/words.txt";

public:
  /** @addtogroup functions_group
   *
   *  @{
   */

  /**
   * @brief check if the preprocessing has been ran before.
   * Complexity \f$O(1)\f$ .
   *
   * @return true it is NOT the first, files must NOT be generated
   * @return false it IS the first run and the files must be generated
   */
  bool not_first_run() {
    return std::filesystem::exists(generated_dictionary) &&
           std::filesystem::exists(generated_words);
  }

  /**
   * @brief Filters data using the predefined regex patterns. Dumps
   * definitions and words to separate files.
   * Complexity \f$O(n^2)\f$ .
   *
   *
   * @param entries is the number of dictionary entries to acquire
   */
  void filter_xml_data(unsigned int entries) {
    unsigned int i = 0;
    std::string line_data;
    std::string temp;
    std::ifstream dict_file(this->filepath);
    std::ofstream definitions(this->generated_dictionary);
    std::ofstream words(this->generated_words);

    while (getline(dict_file, line_data) && i < entries) {
      std::sregex_iterator iter(line_data.begin(), line_data.end(), entry);
      std::sregex_iterator iter2(line_data.begin(), line_data.end(), pattern);

      // save words to file
      for (auto it = iter; it != sregex_iterator(); ++it) {
        if (i <= entries) {
          if (i != 0)
            definitions << "\n";
          // word is stored in temp
          temp = it->str(1);
          // another o(n)
          for (unsigned int chars = 0; chars < temp.length(); chars++)
            temp[chars] = tolower(temp[chars]);
          words << i << " " << temp << "\n";
          i++;
        }
      }
      // save definitions to file
      for (auto it2 = iter2; it2 != sregex_iterator() && ((it2->str(1) == def));
           ++it2) {
        definitions << it2->str(2) << " ";
      }
    }
    words.close();
    definitions.close();
    dict_file.close();
  }

  /** @} */ // end of functions_group
};

#endif // PREPROCESS_XML_HPP_