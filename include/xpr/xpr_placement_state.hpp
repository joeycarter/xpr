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

#include <xpr/xpr_block_loc_registry.hpp>

namespace xpr {

    class PlacementState {
    public:
        PlacementState() = default;

    public:
        inline const BlockLocRegistry& block_loc_registry() const { return block_loc_registry_; }
        inline BlockLocRegistry& mutable_block_loc_registry() { return block_loc_registry_; }

    private:
        BlockLocRegistry block_loc_registry_;
    };

}  // namespace xpr
