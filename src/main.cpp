#include <iostream>
#include <string>

#include "io.h"
#include "encode.h"
#include "decode.h"
// CHECK FOR MEMORY LEAKS SOMEHOW

void encode_file(const std::string& src, const std::string& dest_huff, const std::string& dest_json);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << ("Invalid number of arguments! Try -h for help.") << std::endl;
    return 1;
  }

  std::string arg1 = argv[1];
  // encode
  if (arg1 == "-e") {
    if (argc == 5) {
      std::string src_path = argv[2];
      if (src_path.rfind(".txt") != src_path.size() - 4) {
        std::cerr << "Invalid argument, source should be a .txt file." << std::endl;
        return 1;
      }

      std::string dest_h_path = argv[3];
      if (dest_h_path.rfind(".huff") != dest_h_path.size() - 5) {
        std::cerr << "Invalid argument, destination 1 should be .huff file." << std::endl;
        return 1;
      }

      std::string dest_j_path = argv[4];
      if (dest_j_path.rfind(".json") != dest_j_path.size() - 5) {
        std::cerr << "Invalid argument, destination 2 should be a .json file." << std::endl;
        return 1;
      }

      std::cout << "Encoding " << src_path << "..." << std::endl;
      encode_file(src_path, dest_h_path, dest_j_path);
      std::cout << "Encoded to " << dest_h_path << " with embedding table at ";
      std::cout << dest_j_path << std::endl;

    } else {
      std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
      return 1;
    }

  // decode
  } else if (arg1 == "-d") {
    if (argc == 5) {
      std::cout << "Decode file" << std::endl;
    } else {
      std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
      return 1;
    }

  // help
  } else if (arg1 == "-h") {
    std::cout << "./huff:\n";
    std::cout << "\t-e [SRC.txt] [DEST.huff] [DEST.json]: Encode [SRC] to [DEST]\n";
    std::cout << "\t-d [SRC.huff] [SRC.json] [DEST.txt]: Decode [SRC] to [DEST]\n";
    std::cout << "\t-h : Help Menu" << std::endl;
  
  // invalid args
  } else {
    std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
    return 1;
  }
    
  return 0;
}

/**
 * @brief encodes a file
 * 
 * @param src file path, source .txt file
 * @param dest_h file path, destination .huff compressed file
 * @param dest_j file path, destination .json file storing embedding map
 */
void encode_file(const std::string& src, const std::string& dest_huff, const std::string& dest_json) {
  const std::string file_text = read_text(src);

  std::vector<bool> embedding_vector;
  Encode encoder = Encode(file_text);
  encoder.count_chars();
  std::shared_ptr<Node> n = encoder.build_tree();
  encoder.build_e_map(n);
  encoder.build_embedding(embedding_vector);

  write_cmprsd(dest_huff, embedding_vector);
  write_mapjson(dest_json, encoder.get_e_map());
}