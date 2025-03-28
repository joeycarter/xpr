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

#include <memory>
#include <xpr/xpr.hpp>
#include <xpr/xpr_placer.hpp>
#include <xpr/xpr_utils.hpp>

namespace xpr {

    Xpr::Xpr(const Netlist& netlist, const FloorPlan& floorplan,
             const PlacementOptions& placer_options) {
        placer_ = std::make_unique<Placer>(netlist, floorplan, placer_options);
    }

    void Xpr::run() {
        XPR_ASSERT(placer_ != nullptr, "The placer has not been initialized");
        placer_->place();
    }

}  // namespace xpr
