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

#include <cassert>
#include <cmath>
#include <limits>

#include <xpr/xpr_floorplan.hpp>
#include <xpr/xpr_placement_location.hpp>
#include <xpr/xpr_utils.hpp>

static constexpr int MAX_INDEX = std::numeric_limits<int>::max() / 2;

namespace xpr {

    FloorPlan::FloorPlan(int n_crate_x, int n_crate_y, int n_qpu_per_crate)
        : n_crate_x_(n_crate_x), n_crate_y_(n_crate_y), n_qpu_per_crate_(n_qpu_per_crate) {
        // Bounds checks
        XPR_ASSERT_FMT(n_crate_x_ >= 0 && n_crate_x_ < MAX_INDEX, "Invalid n_crate_x: {}",
                       n_crate_x_);
        XPR_ASSERT_FMT(n_crate_y_ >= 0 && n_crate_y_ < MAX_INDEX, "Invalid n_crate_y: {}",
                       n_crate_y_);
        XPR_ASSERT_FMT(n_qpu_per_crate_ >= 0 && n_qpu_per_crate_ < MAX_INDEX,
                       "Invalid n_qpu_per_crate: {}", n_qpu_per_crate_);
    }

    FloorPlan::FloorPlan(int n_crate_x, int n_crate_y, int n_qpu_per_crate, float scale_x,
                         float scale_y, float scale_qpu)
        : n_crate_x_(n_crate_x),
          n_crate_y_(n_crate_y),
          n_qpu_per_crate_(n_qpu_per_crate),
          scale_x_(scale_x),
          scale_y_(scale_y),
          scale_qpu_(scale_qpu) {
        // Bounds checks
        XPR_ASSERT_FMT(n_crate_x_ >= 0 && n_crate_x_ < MAX_INDEX, "Invalid n_crate_x: {}",
                       n_crate_x_);
        XPR_ASSERT_FMT(n_crate_y_ >= 0 && n_crate_y_ < MAX_INDEX, "Invalid n_crate_y: {}",
                       n_crate_y_);
        XPR_ASSERT_FMT(n_qpu_per_crate_ >= 0 && n_qpu_per_crate_ < MAX_INDEX,
                       "Invalid n_qpu_per_crate: {}", n_qpu_per_crate_);

        XPR_ASSERT_FMT(scale_x_ > 0, "Invalid scale_x: {}", scale_x_);
        XPR_ASSERT_FMT(scale_y_ > 0, "Invalid scale_y: {}", scale_y_);
        XPR_ASSERT_FMT(scale_qpu_ > 0, "Invalid scale_qpu: {}", scale_qpu_);
    }

    std::tuple<int, int, int> FloorPlan::unflatten_index(int flat_index) const {
        int max_flat_index = n_crate_x_ * n_crate_y_ * n_qpu_per_crate_ - 1;
        XPR_ASSERT(flat_index <= max_flat_index, "flat index out of bounds");

        // Calculate k index
        int k = flat_index % n_qpu_per_crate_;

        // Calculate j index
        int j = (flat_index / n_qpu_per_crate_) % n_crate_y_;

        // Calculate i index
        int i = flat_index / (n_crate_y_ * n_qpu_per_crate_);

        return std::make_tuple(i, j, k);
    }

    float FloorPlan::distance_euclidean(const PlacementLoc& loc1, const PlacementLoc& loc2) {
        XPR_ASSERT_FMT(is_loc_valid(loc1), "Invalid physical location: {}", loc1.to_string());
        XPR_ASSERT_FMT(is_loc_valid(loc2), "Invalid physical location: {}", loc2.to_string());

        int delta_x = std::abs(loc1.x - loc2.x);
        int delta_y = std::abs(loc1.y - loc2.y);

        return std::hypot(delta_x * scale_x_, delta_y * scale_y_);
    }

    float FloorPlan::distance_manhattan(const PlacementLoc& loc1, const PlacementLoc& loc2) {
        XPR_ASSERT_FMT(is_loc_valid(loc1), "Invalid physical location: {}", loc1.to_string());
        XPR_ASSERT_FMT(is_loc_valid(loc2), "Invalid physical location: {}", loc2.to_string());

        int delta_x = std::abs(loc1.x - loc2.x);
        int delta_y = std::abs(loc1.y - loc2.y);

        return (delta_x * scale_x_) + (delta_y * scale_y_);
    }

    bool FloorPlan::is_loc_valid(const PlacementLoc& loc) {
        return (loc.x < n_crate_x_) && (loc.y < n_crate_y_) && (loc.y < n_qpu_per_crate_);
    }

}  // namespace xpr
