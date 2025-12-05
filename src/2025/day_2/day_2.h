// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#pragma once

#include "../common.h"
#include <string>
#include <vector>

// Range structure for number ranges
struct Range {
    size_t start;
    size_t end;  // exclusive end
    
    Range(size_t s, size_t e) : start(s), end(e) {}
    
    bool contains(size_t n) const {
        return n >= start && n < end;
    }
    
    size_t size() const {
        return end > start ? end - start : 0;
    }
};

// Number validator for part 1
class NumberValidator1 {
public:
    static bool is_valid(size_t n);
};

// Number validator for part 2
class NumberValidator2 {
public:
    static bool is_valid(size_t n);
    
private:
    static std::vector<size_t> find_divisors(size_t len);
    static bool has_repeating_pattern(const std::string& str, size_t divisor);
};

// Day 2 main function
void run_day_2(Answer& answer);
