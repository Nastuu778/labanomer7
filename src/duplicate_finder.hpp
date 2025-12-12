#pragma once
#include <vector>
#include <unordered_map>
#include <boost/filesystem.hpp>

using Hash = std::size_t;
using DuplicateGroups = std::vector<std::vector<boost::filesystem::path>>;

DuplicateGroups find_duplicates(
    const std::vector<boost::filesystem::path> &files,
    std::size_t block_size = 64 * 1024);