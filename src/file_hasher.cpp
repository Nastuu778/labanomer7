#include "file_hasher.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include <boost/functional/hash.hpp>

std::size_t compute_file_hash(const boost::filesystem::path &file_path, std::size_t block_size)
{
    std::ifstream file(file_path.string(), std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Cannot open file: " + file_path.string());
    }

    std::vector<char> buffer(block_size);
    std::size_t hash = 0;

    while (file)
    {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes_read = file.gcount();
        if (bytes_read == 0)
            break;

        // Используем boost::hash_combine для комбинации блоков
        boost::hash_range(hash, buffer.begin(), buffer.begin() + bytes_read);
    }

    return hash;
}