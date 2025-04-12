#include <string>
#include <vector>
#include <fstream>
#include <iostream>

/**
 * @brief reads contents of a .txt file as a string
 * 
 * @param path the string filepath
 * @return a string containing the file's contents
 */
std::string read_text(const std::string& path) {
  std::string buffer;
  std::string text = "";
  std::ifstream in_file(path);

  if (!in_file.is_open())
    throw std::runtime_error("Could not open file: " + path); 
  
  while (getline(in_file, buffer)) {
    text.append(buffer+"\n");
  }

  in_file.close();
  return text;
}

/**
 * @brief writes string output to text file
 * 
 * @param path filepath
 * @param s string to be written
 */
void write_text(const std::string& path, const std::string& s) {
  std::ofstream out_file(path);
  if (!out_file.is_open())
    throw std::runtime_error("Could not open file: " + path);
  out_file << s;
  out_file.close();
}

/**
 * @brief reads the binary of a file as a boolean vector
 * 
 * @param path string filepath
 * @return the boolean vector of file's contents
 */
std::vector<bool> read_cmprsd(const std::string& path) {
  std::vector<bool> vec;
  std::ifstream in_file(path, std::ios::binary);

  if (!in_file.is_open())
    throw std::runtime_error("Could not open file: " + path);

  char byte;
  while (in_file.get(byte)) {
    for (int i = 7; i >= 0; --i) {
      bool bit = (byte >> i) & 1;
      vec.push_back(bit);
    }
  }

  in_file.close();
  return vec;
}

/**
 * @brief writes boolean (bit) vector into file
 * 
 * @param path filepath
 * @param content bits to be written
 */
void write_cmprsd(const std::string& path, const std::vector<bool>& content) {
  std::ofstream out_file(path);
  if (!out_file.is_open())
    throw std::runtime_error("Could not open file: " + path);

  // write content a byte at a time
  unsigned char byte = 0;
  int n_bits = 0;
  for (bool bit : content) {
    byte = (byte << 1) | bit;
    ++n_bits;
    if (n_bits == 8) {
      out_file.put(byte);
      byte = 0;
      n_bits = 0;
    }
  }

  // if there are any bytes left over, write them
  if (n_bits != 0) {
    byte <<= (8 - n_bits); // shift to most significant digit
    out_file.put(byte);
  }

  out_file.close();
}

/**
 * @brief reads contents of json into unorderedmap
 * 
 * @param path the json filepath
 */
std::unordered_map<char, std::vector<bool>> read_mapjson(const std::string& path) {
  std::unordered_map<char, std::vector<bool>> map;
  std::ifstream in_file(path);
  std::string buffer;

  if (!in_file.is_open())
    throw std::runtime_error("Could not open file: " + path); 
  
  while (getline(in_file, buffer)) {
    // form the vector
    if (buffer.find(":") != std::string::npos) {
      std::bitset<8> c_bits(buffer.substr(2,8));
      char c = static_cast<char>(c_bits.to_ulong());

      std::vector<bool> b_v;
      for (const char& b : buffer.substr(11)) {
        if (b == '0')
          b_v.push_back(false);
        else if (b == '1')
          b_v.push_back(true);
      }

      // insert into map
      map[c] = std::move(b_v);
    }
  }

  in_file.close();
  return map;
}

/**
 * @brief write an unordered_map to a .json file
 * 
 * @param path filepath
 * @param map the map
 */
void write_mapjson(const std::string& path, const std::unordered_map<char, std::vector<bool>>& map) {
  std::ofstream out_file(path);
  if (!out_file.is_open())
    throw std::runtime_error("Could not open file: " + path);
  
  // Iterate through the map, and insert entries
  size_t map_size = map.size();
  size_t cur_ind = 1;
  out_file << "{\n";
  for (const auto& item : map) {
    out_file << "\t\"";

    // Convert char to its 8-bit binary representation
    std::bitset<8> bits(item.first);
    for (int i = 7; i >= 0; i--)
      out_file << (bits.test(i) ? '1' : '0');

    out_file << "\": \"";

    // Insert bools in vector one by one
    for (const bool b : item.second)
      out_file << b;
    
    // Don't add comma after last element
    if (cur_ind < map_size) 
      out_file << "\",\n";
    else
      out_file << "\"\n";
    ++cur_ind;
  }
  out_file << "}";
  out_file.close();
}

// int main() {
//   std::unordered_map<char, std::vector<bool>> test_map;
//   test_map['a'] = {true, false, true};
//   test_map['b'] = {false, false, true, true, false};
//   test_map['c'] = {true, true, true, true};
//   test_map['d'] = {false};
//   test_map['e'] = {true, false, true, false, true, false, true, false};
//   test_map['f'] = {false, false, false};
//   test_map['g'] = {true, false, true, true, false, true, false, true, true, true};
//   test_map['z'] = {};
//   test_map['@'] = {true, true, false};
//   test_map['#'] = {false, true, false, true};
//   test_map['1'] = {true};
//   write_mapjson("poop.json", test_map);
//   std::unordered_map<char, std::vector<bool>> test_map2 = read_mapjson("poop.json");
//   for (const auto& item : test_map2) {
//     std::cout << item.first << " ";
//     for (const bool& b : item.second)
//       std::cout << b;
//     std::cout << '\n';
//   }
//   return 0;
// }
