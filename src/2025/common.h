// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <iostream>

class RisError : public std::runtime_error {
public:
    RisError(const std::string& message) : std::runtime_error(message) {}
};

template<typename T>
using RisResult = std::optional<T>;

// macros for creating errors
#define ris_error_new(msg) RisError(msg)
#define ris_error_new_result(msg) std::nullopt

// Answer structure to store results
class Answer {
public:
    void add(const std::string& result) {
        results_.push_back(result);
    }
    
    const std::vector<std::string>& get_results() const {
        return results_;
    }
    
    void print() const {
        for (const auto& result : results_) {
            std::cout << result << std::endl;
        }
    }

private:
    std::vector<std::string> results_;
};

// read puzzle input
std::string read_puzzle_input(const std::string& key);

