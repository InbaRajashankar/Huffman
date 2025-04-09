#pragma once

#include <string>
#include <vector>

std::string read_text(const std::string& path);
// TO-DO: figure out type of content
void write_text(const std::string& path, const std::string& s);

std::vector<bool> read_cmprsd(const std::string& path);
// TO-DO: figure out type of content
void write_cmprsd(const std::string& path, const std::vector<bool>& content);