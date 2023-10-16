#include <cstddef>
#include <iostream>
#include <string>

class Item {
private:
  std::string data;

public:
  Item() { set_data(""); }
  ~Item() { data.clear(); }
  Item(const std::string &d) { set_data(d); }
  std::string get_data() { return data; }
  void set_data(std::string data) { this->data = data; }
};

class HashTable {
  static const int SIZE = 300;
  Item *hash_arr[SIZE];
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
    Item *new_item = new Item;
    for (int i = 0; i < table_len; i++) {
      hash_arr[i] = new_item;
    }
  }

  ~HashTable() {
    number_items = 0;
    for (int i = 0; i < table_len; i++) {
      delete hash_arr[i];
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
    for (int i = 0; i < str.length(); i++) {
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
  void insert(const std::string &str) {
    Item *item = new Item;
    item->set_data(str);
    int probe = 0;
    int index = hash_function(str);
    while (hash_arr[index]->get_data() != "") {
      probe++;
      index++;
      index %= table_len;
    }
    hash_arr[index] = item;
    number_items++;
  }

  /**
   * @brief Searches in \f$O(N)\f$ time where N is the length of the str to
   * hash.
   *
   * @param str String to hash and look for
   * @return std::string
   */
  std::string search(const std::string &str) {
    int index = hash_function(str);
    std::string search_res = "";
    int count = 0;
    while (hash_arr[index]->get_data() != "" && count != SIZE) {
      if (hash_arr[index]->get_data() == str)
        return search_res += std::to_string(index);
      index++;
      count++;
      index %= SIZE;
    }
    return "NOT FOUND";
  }

  /**
   * @brief Prints every location with a value in it. \f$O(N)\f$.
   *
   */
  void print_hash_table() {
    for (int i = 0; i < SIZE; i++) {
      std::cout << i << " ";
      if (hash_arr[i]->get_data() != "") {
        std::cout << hash_arr[i]->get_data() << std::endl;
      }
    }
  }
  /** @} */ // end of functions_group
};