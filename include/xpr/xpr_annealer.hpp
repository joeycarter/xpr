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

#include <xpr/xpr_move_generator.hpp>
#include <xpr/xpr_random.hpp>

namespace xpr {

    class PlacementState;
    class PlacementCosts;
    struct PlacementOptions;

    struct AnnealerStatistics {
    public:
        double av_cost;
        double av_bb_cost;
        double av_timing_cost;
        double sum_of_squares;
        int success_sum;
        float success_rate;
        double std_dev;

    public:
        AnnealerStatistics() { reset(); }

    public:
        ///@brief Clear all data fields.
        void reset();

        ///@brief Update stats when a single swap move has been accepted.
        void calc_iteration_stats(const PlacementCosts& costs, int move_lim);

        ///@brief Calculate placer success rate and cost std_dev for this iteration.
        void single_swap_update(const PlacementCosts& costs);
    };

    class AnnealingState {
    public:
        float t;
        float alpha;
        int num_temps;

        float rlim;
        float crit_exponent;
        int move_lim;
        int move_lim_max;

    private:
        float UPPER_RLIM;
        float FINAL_RLIM = 1.;
        float INVERSE_DELTA_RLIM;

    public:  // Constructors
        AnnealingState() = default;
        AnnealingState(float first_t, float first_rlim, int first_move_lim,
                       float first_crit_exponent);

    public:
        bool outer_loop_update(float success_rate, const PlacementCosts& costs,
                               const PlacementOptions& options);

    private:
        inline void update_rlim(float success_rate);
        inline void update_crit_exponent(const PlacementOptions& options);
    };

    class PlacementAnnealer {
    public:
        PlacementAnnealer(PlacementState& placement_state, PlacementCosts& costs,
                          RandomNumberGenerator& rng);

        void placement_inner_loop();
        bool outer_loop_update_state();

    private:
        void try_swap_(MoveGenerator& move_generator);

    private:
        PlacementState& placement_state_;
        PlacementCosts& costs_;
        RandomNumberGenerator& rng_;
    };

}  // namespace xpr
