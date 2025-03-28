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

#include <xpr/xpr_move_transactions.hpp>
#include <xpr/xpr_placement_location.hpp>

namespace xpr {

    class BlockLocRegistry {
    public:
        BlockLocRegistry() = default;

    public:
        inline const std::map<int, PlacementLoc>& block_locs() const { return block_locs_; }
        inline std::map<int, PlacementLoc>& mutable_block_locs() { return block_locs_; }

    public:
        void clear();
        void apply_move_blocks(const BlockToBeMoved& blocks_affected);
        void commit_move_blocks(const BlockToBeMoved& blocks_affected);
        void revert_move_blocks(const BlockToBeMoved& blocks_affected);

    private:  // Data
        std::map<int, PlacementLoc> block_locs_;
    };

}  // namespace xpr