// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#include "day_5.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

const std::string PUZZLE_INPUT_KEY = "day_5";

struct Range {
    size_t start;
    size_t end; // inclusive
};

Range parse_range(const std::string& line) {
    size_t dash_pos = line.find('-');
    if (dash_pos == std::string::npos) {
        throw RisError("Invalid range line: " + line);
    }

    size_t start = std::stoull(line.substr(0, dash_pos));
    size_t end = std::stoull(line.substr(dash_pos + 1));

    if (end < start) {
        throw RisError("Range end before start: " + line);
    }

    return Range{start, end};
}

struct InputData {
    std::vector<Range> ranges;
    std::vector<size_t> ids;
};

InputData parse_input(const std::string& input) {
    InputData data;
    std::istringstream iss(input);
    std::string line;
    bool reading_ranges = true;

    while (std::getline(iss, line)) {
        if (line.empty()) {
            reading_ranges = false;
            continue;
        }

        if (reading_ranges) {
            data.ranges.push_back(parse_range(line));
        } else {
            data.ids.push_back(std::stoull(line));
        }
    }

    return data;
}

std::vector<Range> merge_ranges(std::vector<Range> ranges) {
    if (ranges.empty()) {
        return {};
    }

    std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        if (a.start == b.start) {
            return a.end < b.end;
        }
        return a.start < b.start;
    });

    std::vector<Range> merged;
    merged.push_back(ranges.front());

    for (size_t i = 1; i < ranges.size(); ++i) {
        Range& current = merged.back();
        const Range& next = ranges[i];

        if (next.start <= current.end + 1) {
            current.end = std::max(current.end, next.end);
        } else {
            merged.push_back(next);
        }
    }

    return merged;
}

bool contains(const std::vector<Range>& merged_ranges, size_t value) {
    auto it = std::upper_bound(
        merged_ranges.begin(), merged_ranges.end(), value,
        [](size_t val, const Range& range) { return val < range.start; });

    if (it == merged_ranges.begin()) {
        return false;
    }

    --it;
    return value <= it->end;
}

size_t run_part_1(const std::vector<Range>& merged_ranges, const std::vector<size_t>& ids) {
    size_t fresh_count = 0;

    for (size_t id : ids) {
        if (contains(merged_ranges, id)) {
            ++fresh_count;
        }
    }

    return fresh_count;
}

size_t run_part_2(const std::vector<Range>& merged_ranges) {
    size_t total = 0;
    for (const auto& r : merged_ranges) {
        total += (r.end - r.start + 1);
    }
    return total;
}

} // anonymous namespace

void run_day_5(Answer& answer) {
    std::cout << "read input..." << std::endl;
    std::string input = read_puzzle_input(PUZZLE_INPUT_KEY);

    std::cout << "parse input..." << std::endl;
    InputData data = parse_input(input);
    std::vector<Range> merged_ranges = merge_ranges(data.ranges);

    std::cout << "run part 1..." << std::endl;
    size_t result1 = run_part_1(merged_ranges, data.ids);
    answer.add("1: " + std::to_string(result1));

    std::cout << "run part 2..." << std::endl;
    size_t result2 = run_part_2(merged_ranges);
    answer.add("2: " + std::to_string(result2));
}

