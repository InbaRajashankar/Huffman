# Huffman
A C++ program that compresses and decompresses text files using Huffman encoding.

## Installation
### Prerequisites  
- A C++17-compatible compiler (`g++`, `clang`, or MSVC).  
- `make` (for building).  

### Build Instructions  
```sh
$ git clone [repo-url]  
$ cd Huffman  
$ make  
```

## Usage
### Options
```sh
$ ./huff -h
./huff:
	-e [SRC.txt] [DEST.huff] [DEST.json]: Encode [SRC] to [DEST]
	-d [SRC.huff] [SRC.json] [DEST.txt]: Decode [SRC] to [DEST]
	-h : Help Menu
```

Encoding: 
- `SRC.txt`: the file you want to encode
- `DEST.huff`: compressed file that stores the encoded plaintext
- `DEST.json`: json file that stores the embedding map

Decoding:
- `SRC.huff`: the compressed file you want to decode
- `SRC.json`: json file that stores the embedding map for the file
- `DEST.txt`: the text file that will store the output plaintext

### Example
Using the provided dune.txt example text file...

Encode:
```sh
$ ./huff -e tests/text_files/dune.txt dune.huff dune.json
Encoding tests/text_files/dune.txt...
Encoded to dune.huff with embedding table at dune.json
```

Decode:
```
$ ./huff -d dune.huff dune.json dune2.txt
Decoding dune.huff...
dune.huff decoded
```

## License
MIT License.

Copyright (c) 2025 Krish Inba Rajashankar

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.