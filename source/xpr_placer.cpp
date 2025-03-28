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

#include <xpr/xpr_annealer.hpp>
#include <xpr/xpr_floorplan.hpp>
#include <xpr/xpr_placement_location.hpp>
#include <xpr/xpr_placement_options.hpp>
#include <xpr/xpr_placer.hpp>

namespace xpr {

    Placer::Placer(const Netlist& netlist, const FloorPlan& floorplan,
                   const PlacementOptions& placer_options)
        : netlist_(netlist), floorplan_(floorplan), placer_options_(placer_options) {
        // const int move_lim = static_cast<int>(placer_options_.anneal_schedule.inner_num *
        // pow(netlist.blocks().size(), 1.3333));
    }

    void Placer::place() {
        // Initialize placement
        init_placement();

        // Outer loop of the simulated annealing begins
        do {
            // do a complete inner loop iteration
            annealer_.placement_inner_loop();

            // Outer loop of the simulated annealing ends
        } while (annealer_.outer_loop_update_state());
    }

    void Placer::init_placement() {
        auto& block_loc_registry = placer_state_.mutable_block_loc_registry();

        block_loc_registry.clear();

        auto& block_locs = block_loc_registry.mutable_block_locs();

        // TODO: This is a super crude system, which places blocks by ID in ascending
        // floorplan-index order

        int flat_index = 0;

        for (const auto& block : netlist_.blocks()) {
            auto block_id = netlist_.get_block_index(block);

            auto [x, y, n] = floorplan_.unflatten_index(flat_index);
            block_locs[block_id] = PlacementLoc(x, y, n);

            flat_index++;
        }
    }

}  // namespace xpr
