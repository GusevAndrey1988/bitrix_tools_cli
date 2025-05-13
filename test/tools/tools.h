#pragma once

#include <functional>
#include <string>

void suppress_stdout(std::function<void()> fn);

std::string read_whole_file(const std::string &path_to_file);
std::string read_whole_file(std::ifstream &in);