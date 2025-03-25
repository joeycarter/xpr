#include <iostream>
#include <string>

#include <cxxopts.hpp>

#include <xpr/version.h>
#include <xpr/xpr.hpp>

auto main(int argc, char** argv) -> int {
    cxxopts::Options options(*argv, "XPR: A place-and-route engine for quantum computers");

    // clang-format off
    options.add_options()
        ("h,help", "Show this help message and exit")
        ("v,version", "Show the current version information and exit")
    ;
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result["version"].as<bool>()) {
        std::cout << "xpr version " << XPR_VERSION << std::endl;
        return 0;
    }

    // xpr::Xpr xpr;

    return 0;
}
