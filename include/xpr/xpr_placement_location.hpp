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

#include <string>

namespace xpr {

    constexpr int UNPLACED_LOC = -1;

    struct PlacementLoc {
        PlacementLoc() = default;
        PlacementLoc(int xloc, int yloc, int nloc) : x(xloc), y(yloc), n(nloc) {}

        int x{UNPLACED_LOC};  // x position index in floor plan
        int y{UNPLACED_LOC};  // y position index in floor plan
        int n{UNPLACED_LOC};  // QPU index at a given x-y position

        std::string to_string() const;

        friend bool operator==(const PlacementLoc& lhs, const PlacementLoc& rhs) {
            return std::tie(lhs.x, lhs.y, lhs.n) == std::tie(rhs.x, rhs.y, rhs.n);
        }

        friend bool operator!=(const PlacementLoc& lhs, const PlacementLoc& rhs) {
            return !(lhs == rhs);
        }
    };

}  // namespace xpr
