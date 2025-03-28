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

#include <xpr/xpr_netlist.hpp>
#include <xpr/xpr_utils.hpp>

namespace xpr {

    Netlist::Netlist(const std::string& netlist_name) : name_(netlist_name) {}

    // Adds a block to the netlist.
    void Netlist::add_block(const std::string& block_name) {
        if (contains_block(block_name)) {
            return;
        }

        block_to_index_[block_name] = blocks_.size();
        blocks_.push_back(block_name);
        adjacency_list_[blocks_.size() - 1]
            = std::set<std::pair<int, std::string>>();  // Initialize adjacency list for the new
                                                        // block.
    }

    // Adds a net between two blocks.
    void Netlist::add_net(const std::string& source_block, const std::string& dest_block,
                          const std::string& net_name) {
        XPR_ASSERT_FMT(contains_block(source_block), "Source block '{}' does not exist",
                       source_block);
        XPR_ASSERT_FMT(contains_block(dest_block), "Dest block '{}' does not exist", dest_block);

        int source_index = block_to_index_[source_block];
        int dest_index = block_to_index_[dest_block];

        adjacency_list_[source_index].insert(std::make_pair(dest_index, net_name));
    }

    // Prints the netlist.
    void Netlist::print_netlist() const {
        std::cout << "Netlist:" << std::endl;
        for (size_t i = 0; i < blocks_.size(); ++i) {
            std::cout << "Block " << blocks_[i] << " (Index " << i << "):" << std::endl;
            for (const auto& neighbor : adjacency_list_.at(i)) {
                std::cout << "  -> " << blocks_[neighbor.first] << " (Net: " << neighbor.second
                          << ")" << std::endl;
            }
        }
    }

    // Returns block index based on block name.
    int Netlist::get_block_index(const std::string& block_name) const {
        if (block_to_index_.find(block_name) != block_to_index_.end()) {
            return block_to_index_.at(block_name);
        }
        return -1;  // Block not found
    }

    // Returns block name based on block index.
    std::string Netlist::get_block_name(int block_index) const {
        if (block_index >= 0 && static_cast<size_t>(block_index) < blocks_.size()) {
            return blocks_[block_index];
        }
        return "";  // Invalid index
    }

    bool Netlist::contains_block(const std::string& block_name) {
        return block_to_index_.find(block_name) != block_to_index_.end();
    }

    std::vector<std::string> Netlist::nets() const {
        std::vector<std::string> nets;
        for (const auto& pair : adjacency_list_) {
            for (const auto& neighbor : pair.second) {
                nets.push_back(neighbor.second);
            }
        }
        return nets;
    }

}  // namespace xpr
