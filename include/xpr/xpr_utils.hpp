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

#include <cstdlib>
#include <source_location>

#include <fmt/base.h>
#include <fmt/color.h>

// The do-while construct ensures that the macro behaves like a single statement, even when used in
// if or else blocks. It prevents unexpected behavior due to semicolon placement.
#define XPR_ASSERT_FMT(condition, format_str, ...)                                             \
    do {                                                                                       \
        if (!(condition)) {                                                                    \
            const std::source_location __loc__ = std::source_location::current();              \
            fmt::print(stderr, fmt::emphasis::bold | fg(fmt::color::red), "Internal Error: "); \
            fmt::print(stderr, "assertion '{}' failed: ", #condition);                         \
            fmt::print(stderr, "In {}: {}, line {}\n", __loc__.file_name(),                    \
                       __loc__.function_name(), __loc__.line());                               \
            fmt::print(stderr, fmt::emphasis::bold | fg(fmt::color::cyan), "  note: ");        \
            fmt::print(stderr, format_str, __VA_ARGS__);                                       \
            fmt::print("\n");                                                                  \
            std::abort();                                                                      \
        }                                                                                      \
    } while (0)

#define XPR_ASSERT(condition, msg) XPR_ASSERT_FMT(condition, msg, nullptr)
