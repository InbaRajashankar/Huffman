#include <iostream>
#include <string>

#include "io.h"
#include "encode.h"
#include "decode.h"
// CHECK FOR MEMORY LEAKS SOMEHOW

void encode_file(const std::string& src, const std::string& dest_huff, const std::string& dest_json);
void decode_file(const std::string& src_h, const std::string& src_j, const std::string& dest);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << ("Invalid number of arguments! Try -h for help.") << std::endl;
    return 1;
  }

  std::string arg1 = argv[1];
  // encode
  if (arg1 == "-e") {
    if (argc != 5) {
      std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
      return 1;
    }
    
    std::string src_path = argv[2];
    if (src_path.rfind(".txt") != src_path.size() - 4) {
      std::cerr << "Invalid argument, source should be a .txt file." << std::endl;
      return 1;
    }

    std::string dest_h_path = argv[3];
    if (dest_h_path.rfind(".huff") != dest_h_path.size() - 5) {
      std::cerr << "Invalid argument, first destination should be .huff file." << std::endl;
      return 1;
    }

    std::string dest_j_path = argv[4];
    if (dest_j_path.rfind(".json") != dest_j_path.size() - 5) {
      std::cerr << "Invalid argument, second destination should be a .json file." << std::endl;
      return 1;
    }

    std::cout << "Encoding " << src_path << "..." << std::endl;
    encode_file(src_path, dest_h_path, dest_j_path);
    std::cout << "Encoded to " << dest_h_path << " with embedding table at ";
    std::cout << dest_j_path << std::endl;

  // decode
  } else if (arg1 == "-d") {
    if (argc != 5) {
      std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
      return 1;
    }

    std::string src_h_path = argv[2];
    if (src_h_path.rfind(".huff") != src_h_path.size() - 5) {
      std::cerr << "Invalid argument, first source should be a .huff file." << std::endl;
      return 1;
    }

    std::string src_j_path = argv[3];
    if (src_j_path.rfind(".json") != src_j_path.size() - 5) {
      std::cerr << "Invalid argument, second source should be .json file." << std::endl;
      return 1;
    }

    std::string dest_path = argv[4];
    if (dest_path.rfind(".txt") != dest_path.size() - 4) {
      std::cerr << "Invalid argument, destination should be a .txt file." << std::endl;
      return 1;
    }

    std::cout << "Decoding " << src_h_path << "..." << std::endl;
    decode_file(src_h_path, src_j_path, dest_path);
    std::cout << src_h_path << "decoded" << std::endl;

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

/**
 * @brief decodes a file
 * 
 * @param src_h file path, source .huff compressed file
 * @param src_j file path, source .json file storing embedding map
 * @param dest file path, source .txt file
 */
void decode_file(const std::string& src_h, const std::string& src_j, const std::string& dest) {
  std::vector<bool> bits = read_cmprsd(src_h);
  std::unordered_map<char, std::vector<bool>> embedding_map = read_mapjson(src_j);

  Decode decoder = Decode();
  decoder.rebuild_tree(embedding_map);
  std::string plaintext = decoder.decode_bits(bits);

  write_text(dest, plaintext);
}