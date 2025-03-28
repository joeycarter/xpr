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

#include <xpr/xpr_annealer.hpp>
#include <xpr/xpr_floorplan.hpp>
#include <xpr/xpr_netlist.hpp>
#include <xpr/xpr_placement_costs.hpp>
#include <xpr/xpr_placement_options.hpp>
#include <xpr/xpr_placement_state.hpp>
#include <xpr/xpr_random.hpp>

namespace xpr {

    class Placer {
    public:
        Placer(const Netlist& netlist, const FloorPlan& floorplan,
               const PlacementOptions& placer_options);

    public:
        void place();

    private:
        void init_placement();

    private:
        const Netlist& netlist_;
        const FloorPlan& floorplan_;
        const PlacementOptions& placer_options_;
        PlacementState placer_state_;
        PlacementCosts placer_costs_;
        RandomNumberGenerator rng_;
        PlacementAnnealer annealer_{placer_state_, placer_costs_, rng_};
    };

}  // namespace xpr
