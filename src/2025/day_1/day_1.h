// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#pragma once

#include "../common.h"
#include <string>
#include <vector>
#include <cctype>

// Direction enum
enum class Direction {
    Left,
    Right
};

// Rotation structure
struct Rotation {
    Direction direction;
    size_t clicks;
    
    static Rotation from_string(const std::string& line);
};

// Dial template structure
template<size_t T>
class Dial {
public:
    size_t position;
    
    Dial() : position(50) {}
    
    void add(const Rotation& rotation) {
        size_t clicks_to_apply = rotation.clicks % T;
        
        switch (rotation.direction) {
            case Direction::Left:
                if (clicks_to_apply > position) {
                    position += T - clicks_to_apply;
                } else {
                    position -= clicks_to_apply;
                }
                break;
                
            case Direction::Right:
                position += clicks_to_apply;
                if (position >= T) {
                    position -= T;
                }
                break;
        }
    }
};

// Day 1 main function
void run_day_1(Answer& answer);

