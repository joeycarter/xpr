// Copyright 2025 Xanadu Quantum Technologies Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
