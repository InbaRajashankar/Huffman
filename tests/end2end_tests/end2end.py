import os
import subprocess

def end_to_end():
  if "huff" not in os.listdir():
    raise Exception("No executable (huff) to test!")
  
  text_files_path = "./tests/text_files/"
  text_files = os.listdir(text_files_path)
  for file in text_files:
    file_base = file.split(".")[0]

    # Encode the file
    print(f"Encoding {file}")
    subprocess.run([
      "./huff", "-e",
      text_files_path+file,
      "./tests/end2end_tests/dump/"+file_base+".huff", 
      "./tests/end2end_tests/dump/"+file_base+".json"
      ])
    print(f"{file} encoded.")

    # decode the file
    print(f"Decoding {file_base}.huff...")
    subprocess.run([
      "./huff", "-d",
      "./tests/end2end_tests/dump/"+file_base+".huff", 
      "./tests/end2end_tests/dump/"+file_base+".json",
      "./tests/end2end_tests/dump/"+file_base+"2.txt",
      ])
    print(f"{file_base}.huff decoded")

    # check if contents match
    source_text = open(text_files_path+file, "r").read()
    re_formed_text = open("./tests/end2end_tests/dump/"+file_base+"2.txt", "r").read()
    if source_text == re_formed_text:
      print(f"\n{file_base} encoding/decoding SUCCESS!\n")
    else:
      print(f"\n{file_base} encoding/decoding FAIL.\n")

def main():
  end_to_end()

if __name__ == "__main__":
  main()