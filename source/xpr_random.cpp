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

#include <xpr/xpr_random.hpp>

namespace xpr {

    // Generate a random integer in the range [min, max].
    int RandomNumberGenerator::generate_int(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen_);
    }

    // Generate a random float in the range [min, max].
    float RandomNumberGenerator::generate_float(float min, float max) {
        std::uniform_real_distribution<> dist(min, max);
        return dist(gen_);
    }

    // Generate a random double in the range [min, max].
    double RandomNumberGenerator::generate_double(double min, double max) {
        std::uniform_real_distribution<> dist(min, max);
        return dist(gen_);
    }

    // Generate a random float between 0 and 1.
    float RandomNumberGenerator::generate_float_unit() { return generate_float(0.0f, 1.0f); }

    // Generate a random double between 0 and 1.
    double RandomNumberGenerator::generate_double_unit() { return generate_double(0.0, 1.0); }

    // Seed the random number generator.
    void RandomNumberGenerator::seed(unsigned int seed) { gen_.seed(seed); }

}  // namespace xpr
