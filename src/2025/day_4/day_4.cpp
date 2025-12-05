// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#include "day_4.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

namespace {

const std::string PUZZLE_INPUT_KEY = "day_4";

// Grid structure to represent the paper roll locations
class PaperGrid {
public:
    PaperGrid(const std::vector<std::string>& lines) : grid_(lines) {
        if (grid_.empty()) {
            throw RisError("Grid cannot be empty");
        }
        height_ = grid_.size();
        width_ = grid_[0].size();
        
        // Validate all rows have the same width
        for (size_t i = 0; i < grid_.size(); ++i) {
            if (grid_[i].length() != width_) {
                throw RisError("Grid rows must have consistent width");
            }
        }
    }
    
    bool is_roll(size_t row, size_t col) const {
        if (row >= height_ || col >= width_) {
            return false;
        }
        return grid_[row][col] == '@';
    }
    
    size_t count_adjacent_rolls(size_t row, size_t col) const {
        size_t count = 0;
        
        // Check all 8 adjacent positions
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) {
                    continue; // Skip the center position
                }
                
                int new_row = static_cast<int>(row) + dr;
                int new_col = static_cast<int>(col) + dc;
                
                if (new_row >= 0 && new_row < static_cast<int>(height_) &&
                    new_col >= 0 && new_col < static_cast<int>(width_)) {
                    if (is_roll(static_cast<size_t>(new_row), static_cast<size_t>(new_col))) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
    
    bool is_accessible(size_t row, size_t col) const {
        if (!is_roll(row, col)) {
            return false;
        }
        return count_adjacent_rolls(row, col) < 4;
    }
    
    size_t get_height() const { return height_; }
    size_t get_width() const { return width_; }

private:
    std::vector<std::string> grid_;
    size_t height_;
    size_t width_;
};

// Parse input into a grid
PaperGrid parse_grid(const std::string& input) {
    std::vector<std::string> lines;
    std::istringstream iss(input);
    std::string line;
    
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    return PaperGrid(lines);
}

size_t run_part_1(const PaperGrid& grid) {
    size_t accessible_count = 0;
    
    for (size_t row = 0; row < grid.get_height(); ++row) {
        for (size_t col = 0; col < grid.get_width(); ++col) {
            if (grid.is_accessible(row, col)) {
                accessible_count++;
            }
        }
    }
    
    return accessible_count;
}

size_t run_part_2(const PaperGrid& initial_grid) {
    // Create a mutable copy of the grid
    std::vector<std::string> grid_data;
    for (size_t row = 0; row < initial_grid.get_height(); ++row) {
        std::string line;
        for (size_t col = 0; col < initial_grid.get_width(); ++col) {
            line += initial_grid.is_roll(row, col) ? '@' : '.';
        }
        grid_data.push_back(line);
    }
    
    size_t total_removed = 0;
    bool changed = true;
    
    // Keep removing accessible rolls until no more can be removed
    while (changed) {
        changed = false;
        std::vector<std::pair<size_t, size_t>> to_remove;
        
        // Find all accessible rolls in current state
        for (size_t row = 0; row < grid_data.size(); ++row) {
            for (size_t col = 0; col < grid_data[row].length(); ++col) {
                if (grid_data[row][col] != '@') {
                    continue;
                }
                
                // Count adjacent rolls
                size_t adjacent_count = 0;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        
                        int new_row = static_cast<int>(row) + dr;
                        int new_col = static_cast<int>(col) + dc;
                        
                        if (new_row >= 0 && new_row < static_cast<int>(grid_data.size()) &&
                            new_col >= 0 && new_col < static_cast<int>(grid_data[new_row].length())) {
                            if (grid_data[static_cast<size_t>(new_row)][static_cast<size_t>(new_col)] == '@') {
                                adjacent_count++;
                            }
                        }
                    }
                }
                
                // If accessible (fewer than 4 adjacent), mark for removal
                if (adjacent_count < 4) {
                    to_remove.push_back({row, col});
                }
            }
        }
        
        // Remove all marked rolls
        for (const auto& pos : to_remove) {
            grid_data[pos.first][pos.second] = '.';
            total_removed++;
            changed = true;
        }
    }
    
    return total_removed;
}

} // anonymous namespace

void run_day_4(Answer& answer) {
    std::cout << "read input..." << std::endl;
    std::string input = read_puzzle_input(PUZZLE_INPUT_KEY);
    
    std::cout << "parse input..." << std::endl;
    PaperGrid grid = parse_grid(input);
    
    std::cout << "run part 1..." << std::endl;
    size_t result1 = run_part_1(grid);
    answer.add("1: " + std::to_string(result1));
    
    std::cout << "run part 2..." << std::endl;
    size_t result2 = run_part_2(grid);
    answer.add("2: " + std::to_string(result2));
}

