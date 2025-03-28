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

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <vector>

#include "netlist_generator.hpp"

std::unique_ptr<xpr::Netlist> generate_random_netlist(size_t n_blocks,
                                                      const std::string& netlist_name) {
    auto netlist = std::make_unique<xpr::Netlist>(netlist_name);
    for (size_t i = 0; i < n_blocks; ++i) {
        netlist->add_block(std::to_string(i));
    }

    // TODO: it would be nice if we didn't have to store this temporary vector and just generate
    // the randomly ordered IDs on the fly
    auto randomly_ordered_block_ids_src = generate_random_vector(n_blocks * 1.5, n_blocks);
    auto randomly_ordered_block_ids_dst = generate_random_vector(n_blocks * 1.5, n_blocks);

    for (size_t i = 0; i < randomly_ordered_block_ids_src.size(); ++i) {
        std::string src_block = std::to_string(randomly_ordered_block_ids_src[i]);
        std::string dst_block = std::to_string(randomly_ordered_block_ids_dst[i]);
        std::string net_name = src_block + "_" + dst_block;
        netlist->add_net(src_block, dst_block, net_name);
    }

    return netlist;
}

std::vector<int> generate_random_vector(int n, int k) {
    assert(n >= k && "generate_random_vector: Require n >= k");

    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = i % k;
    }

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the vector
    std::shuffle(result.begin(), result.end(), gen);

    return result;
}
