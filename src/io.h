#pragma once

#include <string>
#include <vector>
#include <unordered_map>

std::string read_text(const std::string& path);
void write_text(const std::string& path, const std::string& s);

std::vector<bool> read_cmprsd(const std::string& path);
void write_cmprsd(const std::string& path, const std::vector<bool>& content);

std::unordered_map<char, std::vector<bool>> read_mapjson(const std::string& path);
void write_mapjson(const std::string& path, const std::unordered_map<char, std::vector<bool>>& map);
