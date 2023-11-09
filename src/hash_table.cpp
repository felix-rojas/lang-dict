#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

class Item {
private:
  std::string data;
  int line_number;

public:
  Item() { set_data(""); }
  Item(const std::string &d) { set_data(d); }
  Item(const std::string &d, const int &line) { set_data(d); set_line(line); }
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

public:
  /** @addtogroup functions_group
   *
   *  @{
   */
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

  // ~HashTable() {
  //   try {
  //     for (int i = 0; i < table_len; i++) {
  //       std::cout << "Deleted: " << hash_arr[i]->get_data() << std::endl;
  //       try {
  //         delete hash_arr[i];
  //       } catch (const std::exception &e) {
  //         std::cerr << e.what() << std::endl;
  //       }
  //     }
  //   } catch (const std::exception &e) {
  //     std::cerr << e.what() << std::endl;
  //   }
  // }
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
      hash_arr[index] = Item(str,line);
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
  /** @} */ // end of functions_group
};