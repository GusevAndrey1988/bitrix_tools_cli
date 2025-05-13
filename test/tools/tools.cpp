#include "tools.h"

#include <iostream>
#include <sstream>
#include <fstream>

void suppress_stdout(std::function<void()> fn)
{
    std::streambuf *saved_buf = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());

    fn();

    std::cout.rdbuf(saved_buf);
}

std::string read_whole_file(const std::string &path_to_file)
{
    std::ifstream file{path_to_file};
    return read_whole_file(file);
}

std::string read_whole_file(std::ifstream &in)
{
    std::string str((std::istreambuf_iterator<char>(in)),
                 std::istreambuf_iterator<char>());

    return str;
}