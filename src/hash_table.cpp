#include <cstddef>
#include <iostream>
#include <string>

class Item {
private:
  std::string data;

public:
  Item(std::string d) { data = d; }

  std::string get_data() { return data; }

  void set_data(std::string data) { this->data = data; }
};

class HashTable {
  Item *hash_arr[300];
  int noOfItems;
  int tableLength;

public:
  HashTable() {
    tableLength = 300;
    noOfItems = 0;
    for (int i = 0; i < tableLength; i++) {
      hash_arr[i] = new Item("");
    }
  }

  int hash_function(std::string str) {
    int primaryNumber = 300;
    int hashValue = 0;
    for (int i = 0; i < str.length(); i++) {
      hashValue =
          primaryNumber * hashValue + str.at(i); // to generate index value
    }
    if (hashValue < 0)
      hashValue *= -1; // to avoid negative index
    return hashValue % tableLength;
  }

  void insert(Item *newString) {
    int probe = 0;
    std::string str = newString->get_data();
    int index = hash_function(str);
    while (hash_arr[index]->get_data() != "") {
      probe++;
      index++;
      index %= tableLength;
    }

    hash_arr[index] = newString;
    noOfItems++;

    std::cout << "String (" << str << ") inserted after " << probe << " probes"
              << " at index  " << index << std::endl;
  }

  std::string search(std::string str) {

    int index = hash_function(str);
    while (hash_arr[index]->get_data() != "") {

      if (hash_arr[index]->get_data() == str) {
        std::string temp = "found " + str + "at: ";
        temp += index;  
        return temp;
      }
      index++;
      index %= 300;
    }
    return "NOT FOUND";
  }

  void PrintHashTable() {
    int emptySlot = -1;
    std::cout << "\nSerial No\tData\t\tKey" << std::endl;
    for (int i = 0; i < 300; i++) {
      std::cout << i + 1 << "\t\t";
      if (hash_arr[i]->get_data() != "") {
        std::cout << hash_arr[i]->get_data() << "\t\t" << i << std::endl;
      } else {
        std::cout << "Empty slot\t" << emptySlot << std::endl;
      }
    }
  }
};