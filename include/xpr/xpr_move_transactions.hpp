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

#include <unordered_set>
#include <vector>

#include <xpr/xpr_placement_location.hpp>

namespace xpr {

    struct MovedBlock {
        MovedBlock(int block_id_, const PlacementLoc& old_loc_, const PlacementLoc& new_loc_)
            : block_id(block_id_), old_loc(old_loc_), new_loc(new_loc_) {}

        int block_id;
        PlacementLoc old_loc;
        PlacementLoc new_loc;
    };

    struct BlockToBeMoved {
        std::vector<MovedBlock> moved_blocks;
        std::unordered_set<PlacementLoc> moved_from;
        std::unordered_set<PlacementLoc> moved_to;
    };
}  // namespace xpr
