#pragma once
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

std::vector<boost::filesystem::path> scan_directories(
    const std::vector<std::string> &dirs,
    const std::string &exclude_prefix,
    int max_depth);