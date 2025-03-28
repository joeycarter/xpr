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

#include <random>

namespace xpr {

    class RandomNumberGenerator {
    public:
        // Constructor with optional seed.
        RandomNumberGenerator(unsigned int seed = std::random_device{}()) : gen_(seed) {}

        // Generate a random integer in the range [min, max].
        int generate_int(int min, int max);

        // Generate a random float in the range [min, max].
        float generate_float(float min, float max);

        // Generate a random double in the range [min, max].
        double generate_double(double min, double max);

        // Generate a random float between 0 and 1.
        float generate_float_unit();

        // Generate a random double between 0 and 1.
        double generate_double_unit();

        // Seed the random number generator.
        void seed(unsigned int seed);

    private:
        std::mt19937 gen_;
    };

}  // namespace xpr
