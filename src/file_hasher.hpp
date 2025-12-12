#pragma once
#include <string>
#include <boost/filesystem.hpp>

std::size_t compute_file_hash(const boost::filesystem::path &file_path, std::size_t block_size = 64 * 1024);