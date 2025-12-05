// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#include "day_3.h"
#include <sstream>
#include <iostream>
#include <algorithm>

namespace {

const std::string PUZZLE_INPUT_KEY = "day_3";

// Parse a single battery character to a value
size_t parse_battery(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<size_t>(c - '0');
    }
    throw RisError("Invalid battery: " + std::string(1, c));
}

// Parse input into banks of batteries
std::vector<std::vector<size_t>> parse_banks(const std::string& input) {
    std::vector<std::vector<size_t>> banks;
    std::istringstream iss(input);
    std::string line;
    
    while (std::getline(iss, line)) {
        if (line.empty()) {
            continue;
        }
        
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        std::vector<size_t> bank;
        for (char c : line) {
            bank.push_back(parse_battery(c));
        }
        banks.push_back(bank);
    }
    
    return banks;
}

size_t run_part_1(const std::vector<std::vector<size_t>>& banks) {
    size_t sum = 0;
    
    for (const auto& bank : banks) {
        if (bank.size() < 2) {
            throw RisError("Bank must have at least 2 batteries");
        }
        
        // Go from right to left
        auto it = bank.rbegin();
        size_t battery_2 = *it++;
        size_t battery_1 = *it++;
        
        for (; it != bank.rend(); ++it) {
            size_t battery = *it;
            
            if (battery < battery_1) {
                continue;
            }
            
            if (battery_1 >= battery_2) {
                battery_2 = battery_1;
            }
            
            battery_1 = battery;
        }
        
        size_t joltage = battery_1 * 10 + battery_2;
        sum += joltage;
    }
    
    return sum;
}

size_t run_part_2(const std::vector<std::vector<size_t>>& banks) {
    size_t sum = 0;
    const size_t CAPACITY = 12;
    
    for (const auto& bank : banks) {
        if (bank.size() < CAPACITY) {
            throw RisError("Bank must have at least " + std::to_string(CAPACITY) + " batteries");
        }
        
        // Produce initial state of batteries (last 12 from right to left, then reversed)
        std::vector<size_t> batteries;
        batteries.reserve(CAPACITY);
        
        auto it = bank.rbegin();
        for (size_t i = 0; i < CAPACITY; ++i) {
            batteries.push_back(*it++);
        }
        std::reverse(batteries.begin(), batteries.end());
        
        // Process remaining batteries
        for (; it != bank.rend(); ++it) {
            size_t battery = *it;
            
            if (battery < batteries[0]) {
                // No ripple required, no higher joltage can be produced
                continue;
            }
            
            // Produce ripple
            std::vector<size_t> new_batteries;
            new_batteries.reserve(CAPACITY);
            new_batteries.push_back(battery);
            
            // Ripple effect
            for (size_t i = new_batteries.size(); i < CAPACITY; ++i) {
                size_t i1 = i - 1;
                size_t i2 = i;
                
                if (batteries[i1] >= batteries[i2]) {
                    new_batteries.push_back(batteries[i1]);
                } else {
                    break;
                }
            }
            
            // Fill with remaining batteries
            for (size_t i = new_batteries.size(); i < CAPACITY; ++i) {
                new_batteries.push_back(batteries[i]);
            }
            
            // Apply new state
            batteries = new_batteries;
        }
        
        // Calculate joltage
        size_t joltage = 0;
        size_t power = 1;
        for (auto it = batteries.rbegin(); it != batteries.rend(); ++it) {
            joltage += *it * power;
            power *= 10;
        }
        
        sum += joltage;
    }
    
    return sum;
}

} // anonymous namespace

void run_day_3(Answer& answer) {
    std::cout << "read input..." << std::endl;
    std::string input = read_puzzle_input(PUZZLE_INPUT_KEY);
    
    std::cout << "parse input..." << std::endl;
    std::vector<std::vector<size_t>> banks = parse_banks(input);
    
    std::cout << "run part 1..." << std::endl;
    size_t result1 = run_part_1(banks);
    answer.add("1: " + std::to_string(result1));
    
    std::cout << "run part 2..." << std::endl;
    size_t result2 = run_part_2(banks);
    answer.add("2: " + std::to_string(result2));
}

