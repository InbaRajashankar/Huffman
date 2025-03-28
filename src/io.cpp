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
