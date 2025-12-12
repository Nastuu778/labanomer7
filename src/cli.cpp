#include "cli.hpp"
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

CliOptions parse_cli(int argc, char *argv[])
{
    CliOptions opts;
    po::options_description desc("Options");
    desc.add_options()("help,h", "Show help")("dir,d", po::value<std::vector<std::string>>(&opts.input_dirs)->required(), "Input directories (can be repeated)")("exclude,e", po::value<std::string>(&opts.exclude_prefix)->default_value(""), "Prefix to exclude (e.g. '.git')")("depth", po::value<int>(&opts.max_depth)->default_value(-1), "Max directory depth (-1 = unlimited)")("block-size,b", po::value<size_t>(&opts.block_size)->default_value(64 * 1024), "Block size for hashing (bytes)")("hash", po::value<std::string>(&opts.hash_algo)->default_value("md5"), "Hash algorithm (placeholder)");

    po::positional_options_description p;
    // Нет позиционных аргументов — всё через флаги

    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv)
                      .options(desc)
                      .positional(p)
                      .run(),
                  vm);

        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            std::exit(0);
        }

        po::notify(vm);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << desc << "\n";
        std::exit(1);
    }

    return opts;
}