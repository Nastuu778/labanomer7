#include "duplicate_finder.hpp"
#include "file_hasher.hpp"
#include <unordered_map>
#include <iostream>

DuplicateGroups find_duplicates(
    const std::vector<boost::filesystem::path> &files,
    std::size_t block_size)
{
    // Сначала группируем по размеру (оптимизация)
    std::unordered_map<uintmax_t, std::vector<boost::filesystem::path>> by_size;
    for (const auto &f : files)
    {
        try
        {
            uintmax_t size = boost::filesystem::file_size(f);
            by_size[size].push_back(f);
        }
        catch (...)
        {
            std::cerr << "Skipping unreadable file: " << f << "\n";
        }
    }

    // Теперь хешируем только файлы с одинаковым размером (>1 файл)
    std::unordered_map<Hash, std::vector<boost::filesystem::path>> by_hash;
    for (auto &[size, group] : by_size)
    {
        if (group.size() <= 1)
            continue;

        for (const auto &f : group)
        {
            try
            {
                Hash h = compute_file_hash(f, block_size);
                by_hash[h].push_back(f);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Hash error for " << f << ": " << e.what() << "\n";
            }
        }
    }

    // Формируем группы дубликатов (только где >=2 файла)
    DuplicateGroups result;
    for (auto &[hash, paths] : by_hash)
    {
        if (paths.size() >= 2)
        {
            result.push_back(std::move(paths));
        }
    }

    return result;
}