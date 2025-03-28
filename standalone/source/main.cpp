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
#include <xpr/xpr_floorplan.hpp>
#include <xpr/xpr_placement_options.hpp>
#include <xpr/xpr_utils.hpp>

#include "netlist_generator.hpp"

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

    // Generate a random netlist with N QPUs ("blocks")
    auto netlist = generate_random_netlist(10'000, "netlist");

    // Generate a floor plan with given dimensions
    // The total number of available QPU slots is n_crate_x * n_crate_y * n_qpu_per_crate
    xpr::FloorPlan floorplan(70,    // n_crate_x
                             40,    // n_crate_y
                             5,     // n_qpu_per_crate
                             3.0f,  // scale_x
                             2.5f,  // scale_y
                             0.2f   // scale_qpu
    );

    xpr::PlacementOptions placer_options;

    xpr::Xpr xpr(*netlist, floorplan, placer_options);
    xpr.run();

    return 0;
}
