#include <iostream>
#include <string>

#include "io.h"
#include "encode.h"
#include "decode.h"
// CHECK FOR MEMORY LEAKS SOMEHOW

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << ("Invalid number of arguments! Try -h for help.") << std::endl;
    return 1;
  }

  std::string arg1 = argv[1];
  // encode
  if (arg1 == "-e") {
    if (argc == 4) {
      std::cout << "Encode file" << std::endl;
    } else {
      std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
      return 1;
    }

  // decode
  } else if (arg1 == "-d") {
    if (argc == 4) {
      std::cout << "Decode file" << std::endl;
    } else {
      std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
      return 1;
    }

  // help
  } else if (arg1 == "-h") {
    std::cout << "./huff:\n";
    std::cout << "\t-e [SRC] [DEST]: Encode [SRC] to [DEST]\n";
    std::cout << "\t-d [SRC] [DEST]: Decode [SRC] to [DEST]\n";
    std::cout << "\t-h : Help Menu" << std::endl;
  
  // invalid args
  } else {
    std::cerr << ("Invalid arguments! Try -h for help.") << std::endl;
    return 1;
  }
    
  return 0;
}