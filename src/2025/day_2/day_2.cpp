// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#include "day_2.h"
#include <sstream>
#include <iostream>

namespace {

const std::string PUZZLE_INPUT_KEY = "day_2";

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Parse a single range string "start-end"
Range parse_range(const std::string& range_str) {
    size_t dash_pos = range_str.find('-');
    if (dash_pos == std::string::npos) {
        throw RisError("Invalid range format: " + range_str);
    }
    
    std::string start_str = range_str.substr(0, dash_pos);
    std::string end_str = range_str.substr(dash_pos + 1);
    
    try {
        size_t start = std::stoull(start_str);
        size_t end = std::stoull(end_str) + 1;  // Make end exclusive
        return Range(start, end);
    } catch (const std::exception&) {
        throw RisError("Invalid number in range: " + range_str);
    }
}

// Parse all ranges from input string
std::vector<Range> parse_ranges(const std::string& input) {
    std::vector<Range> ranges;
    std::istringstream iss(input);
    std::string token;
    
    while (std::getline(iss, token, ',')) {
        std::string trimmed = trim(token);
        if (!trimmed.empty()) {
            ranges.push_back(parse_range(trimmed));
        }
    }
    
    return ranges;
}

size_t run_part_1(const std::vector<Range>& ranges) {
    size_t sum = 0;
    
    for (const auto& range : ranges) {
        for (size_t n = range.start; n < range.end; ++n) {
            if (!NumberValidator1::is_valid(n)) {
                sum += n;
            }
        }
    }
    
    return sum;
}

size_t run_part_2(const std::vector<Range>& ranges) {
    size_t sum = 0;
    
    for (const auto& range : ranges) {
        for (size_t n = range.start; n < range.end; ++n) {
            if (!NumberValidator2::is_valid(n)) {
                sum += n;
            }
        }
    }
    
    return sum;
}

} // anonymous namespace

bool NumberValidator1::is_valid(size_t n) {
    std::string n_str = std::to_string(n);
    size_t len = n_str.length();
    
    // If length is not even, number is valid
    if (len % 2 != 0) {
        return true;
    }
    
    // Split into two halves and compare
    size_t half_len = len / 2;
    std::string first_half = n_str.substr(0, half_len);
    std::string second_half = n_str.substr(half_len);
    
    // Valid if halves are different
    return first_half != second_half;
}

std::vector<size_t> NumberValidator2::find_divisors(size_t len) {
    std::vector<size_t> divisors;
    for (size_t i = 1; i < len; ++i) {
        if (len % i == 0) {
            divisors.push_back(i);
        }
    }
    return divisors;
}

bool NumberValidator2::has_repeating_pattern(const std::string& str, size_t divisor) {
    size_t elements = str.length() / divisor;
    if (elements < 2) {
        return false;
    }
    
    // Compare adjacent segments
    for (size_t i = 0; i < elements - 1; ++i) {
        size_t pos1 = i * divisor;
        size_t pos2 = (i + 1) * divisor;
        
        std::string segment1 = str.substr(pos1, divisor);
        std::string segment2 = str.substr(pos2, divisor);
        
        if (segment1 != segment2) {
            return false;
        }
    }
    
    return true;
}

bool NumberValidator2::is_valid(size_t n) {
    std::string n_str = std::to_string(n);
    size_t len = n_str.length();
    
    // Find all divisors of the length
    std::vector<size_t> divisors = find_divisors(len);
    
    // Check if any divisor creates a repeating pattern
    for (size_t divisor : divisors) {
        if (has_repeating_pattern(n_str, divisor)) {
            return false;  // Invalid if it has a repeating pattern
        }
    }
    
    return true;  // Valid if no repeating patterns found
}

void run_day_2(Answer& answer) {
    std::cout << "read input..." << std::endl;
    std::string input = read_puzzle_input(PUZZLE_INPUT_KEY);
    
    std::cout << "parse input..." << std::endl;
    std::vector<Range> ranges = parse_ranges(input);
    
    std::cout << "run part 1..." << std::endl;
    size_t result1 = run_part_1(ranges);
    answer.add("1: " + std::to_string(result1));
    
    std::cout << "run part 2..." << std::endl;
    size_t result2 = run_part_2(ranges);
    answer.add("2: " + std::to_string(result2));
}
