// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#include "day_1.h"
#include <sstream>
#include <iostream>

Rotation Rotation::from_string(const std::string& line) {
    if (line.empty()) {
        throw RisError("Empty line cannot be converted to Rotation");
    }
    
    char direction_char = std::tolower(line[0]);
    std::string clicks_str = line.substr(1);
    
    Direction direction;
    if (direction_char == 'l') {
        direction = Direction::Left;
    } else if (direction_char == 'r') {
        direction = Direction::Right;
    } else {
        throw RisError("Invalid direction: " + std::string(1, direction_char));
    }
    
    size_t clicks;
    try {
        clicks = std::stoull(clicks_str);
    } catch (const std::exception&) {
        throw RisError("Invalid clicks value: " + clicks_str);
    }
    
    return Rotation{direction, clicks};
}

namespace {

const std::string PUZZLE_INPUT_KEY = "day_1";

size_t run_part_1(const std::vector<Rotation>& rotations) {
    Dial<100> dial;
    size_t counter = 0;
    
    for (const auto& rotation : rotations) {
        dial.add(rotation);
        
        if (dial.position == 0) {
            counter++;
        }
    }
    
    return counter;
}

size_t run_part_2(const std::vector<Rotation>& rotations) {
    Dial<100> dial;
    size_t counter = 0;
    
    for (const auto& rotation : rotations) {
        // Apply rotations one click at a time
        for (size_t i = 0; i < rotation.clicks; ++i) {
            Rotation single_click{rotation.direction, 1};
            dial.add(single_click);
            
            if (dial.position == 0) {
                counter++;
            }
        }
    }
    
    return counter;
}
} // namespace

void run_day_1(Answer& answer) {
    std::cout << "read input..." << std::endl;
    std::string input = read_puzzle_input(PUZZLE_INPUT_KEY);
    
    std::cout << "parse input..." << std::endl;
    std::vector<Rotation> rotations;
    
    std::istringstream iss(input);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty()) {
            continue;
        }
        
        try {
            rotations.push_back(Rotation::from_string(line));
        } catch (const RisError& e) {
            std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            throw;
        }
    }
    
    std::cout << "run part 1..." << std::endl;
    size_t result1 = run_part_1(rotations);
    answer.add("1: " + std::to_string(result1));
    
    std::cout << "run part 2..." << std::endl;
    size_t result2 = run_part_2(rotations);
    answer.add("2: " + std::to_string(result2));
}

