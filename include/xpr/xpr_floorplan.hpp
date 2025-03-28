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

#include <tuple>

namespace xpr {

    struct PlacementLoc;

    /**
     * @brief The "floor plan" of the quantum computer.
     *
     * Think of the floor plan as a two-dimensional array of QPU "crates", where a crate holds some
     * number of QPUs. The floor plan defines the number of available QPUs and the physical spacing
     * between them.
     */
    class FloorPlan {
    public:
        FloorPlan(int n_crate_x, int n_crate_y, int n_qpu_per_crate);
        FloorPlan(int n_crate_x, int n_crate_y, int n_qpu_per_crate, float scale_x, float scale_y,
                  float scale_qpu);

    public:  // Accessors
        inline int n_crate_x() const { return n_crate_x_; }
        inline int n_crate_y() const { return n_crate_y_; }
        inline int n_qpu_per_crate() const { return n_qpu_per_crate_; }
        inline float scale_x() const { return scale_x_; }
        inline float scale_y() const { return scale_y_; }
        inline float scale_qpu() const { return scale_qpu_; }

    public:
        std::tuple<int, int, int> unflatten_index(int flat_index) const;

    public:
        float distance_euclidean(const PlacementLoc& p1, const PlacementLoc& p2);
        float distance_manhattan(const PlacementLoc& p1, const PlacementLoc& p2);

    private:
        bool is_loc_valid(const PlacementLoc& loc);
        void check_floorplan_params();

    private:                   // Data
        int n_crate_x_;        // Number of QPU crates along x
        int n_crate_y_;        // Number of QPU crates along y
        int n_qpu_per_crate_;  // Number of QPUs per crate
        float scale_x_{1.f};   // Scale along x, i.e. distance between two adjacent crates in [m]
        float scale_y_{1.f};   // Scale along x, i.e. distance between two adjacent crates in [m]
        float scale_qpu_{
            1.f};  // Scale within crate, i.e. distance between two adjacent QPUs in [m]
    };

}  // namespace xpr