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

#include <cmath>

#include <doctest/doctest.h>

#include <xpr/xpr_floorplan.hpp>
#include <xpr/xpr_placement_location.hpp>

TEST_CASE("Test FloorPlan initialization") {
    xpr::FloorPlan floorplan1(7, 6, 5);

    CHECK(floorplan1.n_crate_x() == 7);
    CHECK(floorplan1.n_crate_y() == 6);
    CHECK(floorplan1.n_qpu_per_crate() == 5);
    CHECK(floorplan1.scale_x() == 1.f);
    CHECK(floorplan1.scale_y() == 1.f);
    CHECK(floorplan1.scale_qpu() == 1.f);

    xpr::FloorPlan floorplan2(7, 6, 5, 0.7f, 0.6f, 0.5f);

    CHECK(floorplan2.n_crate_x() == 7);
    CHECK(floorplan2.n_crate_y() == 6);
    CHECK(floorplan2.n_qpu_per_crate() == 5);
    CHECK(floorplan2.scale_x() == 0.7f);
    CHECK(floorplan2.scale_y() == 0.6f);
    CHECK(floorplan2.scale_qpu() == 0.5f);
}

TEST_CASE("Test FloorPlan::distance_euclidean()") {
    SUBCASE("without floorplan scaling") {
        xpr::FloorPlan floorplan(7, 6, 5);

        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.0));
        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{1, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(1.0));
        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{0, 1, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(1.0));
        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{1, 1, 0})
              == doctest::Approx(std::sqrt(2)));
    }

    SUBCASE("with floorplan scaling") {
        xpr::FloorPlan floorplan(7, 6, 5, 0.7f, 0.6f, 0.5f);

        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.0));
        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{1, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.7f));
        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{0, 1, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.6));
        CHECK(floorplan.distance_euclidean(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{1, 1, 0})
              == doctest::Approx(std::sqrt(0.6 * 0.6 + 0.7 * 0.7)));
    }
}

TEST_CASE("Test FloorPlan::distance_manhattan()") {
    SUBCASE("without floorplan scaling") {
        xpr::FloorPlan floorplan(7, 6, 5);

        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == 0);
        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{1, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == 1);
        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{0, 1, 0}, xpr::PlacementLoc{0, 0, 0})
              == 1);
        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{1, 1, 0})
              == 2);
    }

    SUBCASE("with floorplan scaling") {
        xpr::FloorPlan floorplan(7, 6, 5, 0.7f, 0.6f, 0.5f);

        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.0));
        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{1, 0, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.7f));
        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{0, 1, 0}, xpr::PlacementLoc{0, 0, 0})
              == doctest::Approx(0.6));
        CHECK(floorplan.distance_manhattan(xpr::PlacementLoc{0, 0, 0}, xpr::PlacementLoc{1, 1, 0})
              == doctest::Approx(0.6 + 0.7));
    }
}
