#include <algorithm>
#include <cstddef>
#include <iostream>
#include <locale>
#include <ostream>
#include <string>
#include <vector>

  /**
   * @brief Auxiliary struct for french locale string comparator
   *
   * @return true if french word goes alphabetically first
   */
struct localeComparator {
    std::locale loc;
    const std::collate<char>& collate;
    localeComparator(const std::locale& loc) : loc(loc), collate(std::use_facet<std::collate<char>>(loc)) {}
    bool operator()(const std::string& s1, const std::string& s2) const {
        return collate.compare(s1.data(), s1.data() + s1.size(), s2.data(), s2.data() + s2.size()) < 0;
    }
};


class Item {
private:
  std::string data;
  int line_number;

public:
  Item() { set_data(""); }
  Item(const std::string &d) { set_data(d); }
  Item(const std::string &d, const int &line) {
    set_data(d);
    set_line(line);
  }
  std::string get_data() { return data; }
  int get_line() { return line_number; }
  void set_data(std::string str_data) { this->data = str_data; }
  void set_line(int line) { this->line_number = line; }
};

class HashTable {
  static const int SIZE = 500;
  Item hash_arr[SIZE];
  int number_items;
  int table_len;
  /** @addtogroup functions_group
   *
   *  @{
   */
private:
  int partition(std::vector<std::string> &vec, int low, int high) {
    int i = low, j = high;
    std::string pivot = vec[(low + high) / 2];

    while (i <= j) {
      while (vec[i] < pivot)
        i++;
      while (vec[j] > pivot)
        j--;
      if (i <= j) {
        std::swap(vec[i], vec[j]);
        i++;
        j--;
      }
    }
    return i;
  }
  /**
   * @brief Quicksort for strings.
   * Complexity is O(N^2) in the worst case,
   * where the string pivot is either the largest or the smallest element.
   * \f$O(N^2)\f$
   * This sort was chosen because the average case requires \f$O(N log (N))\f$
   * time
   *
   */
  void quickSort(std::vector<std::string> &vec, int low, int high) {
    if (low < high) {
      int pivotIndex = partition(vec, low, high);
      quickSort(vec, low, pivotIndex - 1);
      quickSort(vec, pivotIndex, high);
    }
  }

public:
  /**
   * @brief Construct a new Hash Table object, allocate item positions.
   * \f$O(N)\f$
   *
   */
  HashTable() {
    table_len = SIZE;
    number_items = 0;
    try {
      for (int i = 0; i < table_len; i++) {
        hash_arr[i] = Item();
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  HashTable(unsigned int n) {
    table_len = n;
    number_items = 0;
    try {
      for (int i = 0; i < table_len; i++) {
        hash_arr[i] = Item();
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  /**
   * @brief simple hash function that increases the value on each loop according
   * to the integer value of the char. \f$O(N)\f$ where N is the str length.
   *
   * @param str String to hash
   * @return int Calculated key value of the string
   */
  int hash_function(const std::string &str) {
    int primaryNumber = SIZE;
    unsigned long hashValue = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
      hashValue = primaryNumber * hashValue + str.at(i);
    }
    if (hashValue < 0)
      hashValue *= -1;
    return hashValue % table_len;
  }

  /**
   * @brief Linear probing to insert value. Worst case is \f$O(N)\f$ for the
   * last value if the keys happen to be poisoned (they are generated
   * sequentially).
   *
   * @param str
   */
  void insert(const std::string &str, const int &line) {
    try {
      int index = hash_function(str);
      while (hash_arr[index].get_data() != "") {
        index++;
        index %= table_len;
      }
      hash_arr[index] = Item(str, line);
      number_items++;
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  /**
   * @brief Searches in \f$O(N)\f$ time where N is the length of the str to
   * hash.
   *
   * @param str String to hash and look for
   * @return std::string
   */
  int search(const std::string &str) {
    try {
      int index = hash_function(str);
      std::string search_res = "";
      int count = 0;
      while (hash_arr[index].get_data() != "" && count != SIZE) {
        if (hash_arr[index].get_data() == str)
          return hash_arr[index].get_line();
        index++;
        count++;
        index %= SIZE;
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
    return -1;
  }

  /**
   * @brief Prints every location with a value in it. \f$O(N)\f$.
   *
   */
  void print_hash_table() {
    try {
      for (int i = 0; i < SIZE - 1; i++) {
        std::cout << i << " ";
        if (hash_arr[i].get_data() != "") {
          std::cout << hash_arr[i].get_data() << std::endl;
        }
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  /**
   * @brief Prints every word with a value in it using the user's locale to
   * determine the order. This is \f$O(N^2)f$ complexity, where the worst case
   * is the Quicksort's worst case.
   * If it finds a french locale to use in collate, it will use those rules, else it will sort using global locale.
   *
   */
  void print_sorted_words(std::string locale) {
    std::vector<std::string> words;
    words.reserve(SIZE);
    try {
      for (int i = 0; i < SIZE - 1; i++) {
        if (hash_arr[i].get_data() != "") {
          words.push_back(hash_arr[i].get_data());
        }
      }
      if (locale.find("fr")) {
        std::sort(words.begin(), words.end(), localeComparator(std::locale(locale)));
      } else {
        quickSort(words, 0, words.size() - 1);
      }
      for (auto word : words) {
        std::cout << word << std::endl;
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  /** @} */ // end of functions_group
};