#include "filesystem_scanner.hpp"
#include <boost/filesystem.hpp>
#include <queue>
#include <iostream>

namespace fs = boost::filesystem;

// Вспомогательная функция: проверка глубины
int get_depth(const fs::path &p)
{
    return std::distance(p.begin(), p.end());
}

std::vector<fs::path> scan_directories(
    const std::vector<std::string> &dirs,
    const std::string &exclude_prefix,
    int max_depth)
{
    std::vector<fs::path> results;
    std::queue<std::pair<fs::path, int>> q; // (path, depth)

    for (const auto &dir : dirs)
    {
        fs::path p(dir);
        if (!fs::exists(p) || !fs::is_directory(p))
        {
            std::cerr << "Warning: skipping non-directory: " << p << "\n";
            continue;
        }
        q.emplace(p, 0);
    }

    while (!q.empty())
    {
        auto [current, depth] = q.front();
        q.pop();

        if (max_depth >= 0 && depth > max_depth)
            continue;

        if (fs::is_regular_file(current))
        {
            if (exclude_prefix.empty() ||
                current.filename().string().substr(0, exclude_prefix.size()) != exclude_prefix)
            {
                results.push_back(current);
            }
        }
        else if (fs::is_directory(current))
        {
            try
            {
                for (const auto &entry : fs::directory_iterator(current))
                {
                    if (fs::is_directory(entry.status()))
                    {
                        q.emplace(entry.path(), depth + 1);
                    }
                    else
                    {
                        q.emplace(entry.path(), depth);
                    }
                }
            }
            catch (const fs::filesystem_error &ex)
            {
                std::cerr << "Skipping inaccessible directory: " << current << " (" << ex.what() << ")\n";
            }
        }
    }

    return results;
}