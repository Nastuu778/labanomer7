#pragma once
#include <string>
#include <vector>
#include <boost/program_options.hpp>

struct CliOptions
{
    std::vector<std::string> input_dirs;
    std::string exclude_prefix;
    int max_depth = -1;            // -1 = unlimited
    std::string hash_algo = "md5"; // пока заглушка
    size_t block_size = 64 * 1024; // 64KB
};

CliOptions parse_cli(int argc, char *argv[]);