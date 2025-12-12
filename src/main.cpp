#include <iostream>
#include <boost/filesystem.hpp>
#include "cli.hpp"
#include "filesystem_scanner.hpp"
#include "duplicate_finder.hpp"

int main(int argc, char *argv[])
{
    try
    {
        auto opts = parse_cli(argc, argv);

        std::cout << "Scanning directories...\n";
        auto files = scan_directories(opts.input_dirs, opts.exclude_prefix, opts.max_depth);

        std::cout << "Found " << files.size() << " files.\n";
        std::cout << "Searching for duplicates...\n";

        auto groups = find_duplicates(files, opts.block_size);

        if (groups.empty())
        {
            std::cout << "No duplicates found.\n";
        }
        else
        {
            std::cout << "Duplicate groups found: " << groups.size() << "\n";
            for (size_t i = 0; i < groups.size(); ++i)
            {
                std::cout << "\nGroup " << (i + 1) << ":\n";
                for (const auto &f : groups[i])
                {
                    std::cout << "  " << f << "\n";
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}