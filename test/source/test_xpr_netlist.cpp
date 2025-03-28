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

#include <string>

#include <doctest/doctest.h>

#include <xpr/xpr_netlist.hpp>

TEST_CASE("Test trivial netlist initialization") {
    xpr::Netlist netlist("my_netlist");

    CHECK(netlist.name() == "my_netlist");
}

TEST_CASE("Test netlist initialization") {
    xpr::Netlist netlist("my_netlist");

    netlist.add_block("A");
    netlist.add_block("B");
    netlist.add_block("C");

    netlist.add_net("A", "B", "net_AB");
    netlist.add_net("A", "C", "net_AC");
    netlist.add_net("B", "C", "net_BC");

    SUBCASE("Test blocks") {
        std::vector<std::string> expected_blocks = {"A", "B", "C"};
        CHECK(netlist.blocks() == expected_blocks);
    }

    SUBCASE("Test nets") {
        std::vector<std::string> expected_nets = {"net_AB", "net_AC", "net_BC"};
        CHECK(netlist.nets() == expected_nets);
    }
}
