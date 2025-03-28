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

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

namespace xpr {

    class Netlist {
    public:
        Netlist(const std::string& netlist_name);

    public:
        inline const std::string& name() const { return name_; }
        inline const std::vector<std::string>& blocks() const { return blocks_; }
        std::vector<std::string> nets() const;

    public:
        // Adds a block to the netlist.
        void add_block(const std::string& block_name);

        // Adds a net between two blocks.
        void add_net(const std::string& source_block, const std::string& dest_block,
                     const std::string& net_name);

        // Prints the netlist.
        void print_netlist() const;

        // Returns block index based on block name.
        int get_block_index(const std::string& block_name) const;

        // Returns block name based on block index.
        std::string get_block_name(int block_index) const;

        bool contains_block(const std::string& block_name);

    private:
        std::string name_;  // Netlist name
        std::map<std::string, int>
            block_to_index_;               // Map block name to its index in the blocks vector
        std::vector<std::string> blocks_;  // Vector of block names
        std::map<int, std::set<std::pair<int, std::string>>>
            adjacency_list_;  // Adjacency list: block index -> set of (neighbor index, net name)
    };

}  // namespace xpr
